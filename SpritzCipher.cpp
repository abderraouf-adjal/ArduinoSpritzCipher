/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Abderraouf Adjal
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "SpritzCipher.h"


#define SPRITZ_N_MINUS_1 255 /* SPRITZ_N - 1 */
#define SPRITZ_N_HALF 128 /* SPRITZ_N / 2 */


static void
swap(uint8_t *a, uint8_t *b)
{
  uint8_t t = *a;
  *a = *b;
  *b = t;
}


static void
stateInit(spritz_ctx *ctx)
{
  uint8_t i;
  ctx->i = ctx->j = ctx->k = ctx->z = ctx->a = 0;
  ctx->w = 1;
  for (i = 0; i < SPRITZ_N_MINUS_1; i++) {
    ctx->s[i] = i;
  }
  ctx->s[255] = 255;
}

static void
update(spritz_ctx *ctx)
{
  ctx->i = (uint8_t)(ctx->i + ctx->w);
  ctx->j = (uint8_t)(ctx->k + ctx->s[(uint8_t)(ctx->j + ctx->s[ctx->i])]);
  ctx->k = (uint8_t)(ctx->k + ctx->i + ctx->s[ctx->j]);
  swap(&ctx->s[ctx->i], &ctx->s[ctx->j]);
}

static void
whip(spritz_ctx *ctx)
{
  uint8_t i;
  for (i = 0; i < SPRITZ_N_HALF; i++) {
    update(ctx);
    update(ctx);
    update(ctx);
    update(ctx);
  }
  ctx->w = (uint8_t)(ctx->w + 2);
}

static void
crush(spritz_ctx *ctx)
{
  uint8_t i, j;
#ifdef SAFE_TIMING_CRUSH
  uint8_t s_i, s_j;
#endif

  for (i = 0, j = SPRITZ_N_MINUS_1; i < SPRITZ_N_HALF; i++, j--) {
#ifdef SAFE_TIMING_CRUSH
    s_i = ctx->s[i];
    s_j = ctx->s[j];
    if (s_i > s_j) {
      ctx->s[i] = s_j;
      ctx->s[j] = s_i;
    }
    else {
      ctx->s[i] = s_i;
      ctx->s[j] = s_j;
    }
#else /* SAFE_TIMING_CRUSH */
    if (ctx->s[i] > ctx->s[j]) {
      swap(&ctx->s[i], &ctx->s[j]);
    }
#endif
  }
}

static void
shuffle(spritz_ctx *ctx)
{
  whip(ctx);
  crush(ctx);
  whip(ctx);
  crush(ctx);
  whip(ctx);
  ctx->a = 0;
}

/* Tip: nibble=4bit; octet=2*nibble=8bit; byte=octet in modern computers */
static void
absorbNibble(spritz_ctx *ctx, const uint8_t nibble)
{
  if (ctx->a == SPRITZ_N_HALF) {
    shuffle(ctx);
  }
  swap(&ctx->s[ctx->a], &ctx->s[SPRITZ_N_HALF + nibble]);
  ctx->a++;
}
static void
absorb(spritz_ctx *ctx, const uint8_t octet)
{
  absorbNibble(ctx, octet % 16); /* Low */
  absorbNibble(ctx, octet / 16); /* High */
}
static void
absorbBytes(spritz_ctx *ctx, const uint8_t *buf, unsigned int len)
{
  unsigned int i;
  for (i = 0; i < len; i++) {
    absorb(ctx, buf[i]);
  }
}

static void
absorbStop(spritz_ctx *ctx)
{
  if (ctx->a == SPRITZ_N_HALF) {
    shuffle(ctx);
  }
  ctx->a++;
}

static uint8_t
output(spritz_ctx *ctx)
{
  ctx->z = ctx->s[(uint8_t)(ctx->j + ctx->s[(uint8_t)(ctx->i + ctx->s[(uint8_t)(ctx->z + ctx->k)])])];
  return ctx->z;
}
static uint8_t
drip(spritz_ctx *ctx)
{
  if (ctx->a) {
    shuffle(ctx);
  }
  update(ctx);
  return output(ctx);
}

/* squeeze() for hash and mac */
static void
squeeze(spritz_ctx *ctx, uint8_t *out, uint8_t len)
{
  uint8_t i;
  if (ctx->a) {
    shuffle(ctx);
  }
  for (i = 0; i < len; i++) {
    out[i] = drip(ctx);
  }
}


/* |====================|| User Functions ||====================| */

/* Wipe spritz context (spritz_ctx) data */
void
spritz_wipe_ctx(spritz_ctx *ctx)
{
  uint8_t i, d;

  start:
  ctx->i = ctx->j = ctx->k = ctx->z = ctx->a = ctx->w = 0;
  d = ctx->i | ctx->j | ctx->k | ctx->z | ctx->a | ctx->w;
  for (i = 0; i < SPRITZ_N_MINUS_1; i++) {
    ctx->s[i] = 0;
    d |= ctx->s[i];
  }
  ctx->s[255] = 0;
  d |= ctx->s[255];
  if (d) {
    goto start;
  }
}


/* Setup spritz state (spritz_ctx) with a key */
void
spritz_setup(spritz_ctx *ctx,
                    const uint8_t *key, uint8_t keyLen)
{
  stateInit(ctx);
  absorbBytes(ctx, key, keyLen);
}

/* Setup spritz state (spritz_ctx) with a key and nonce (Salt) */
void
spritz_setupIV(spritz_ctx *ctx,
                      const uint8_t *key, uint8_t keyLen,
                      const uint8_t *nonce, uint8_t nonceLen)
{
  spritz_setup(ctx, key, keyLen);
  absorbStop(ctx);
  absorbBytes(ctx, nonce, nonceLen);
}

/* Generates a byte of keystream from spritz state (spritz_ctx) */
uint8_t
spritz_rand_byte(spritz_ctx *ctx)
{
  return drip(ctx);
}


/* Setup spritz hash state (spritz_ctx) */
void
spritz_hash_setup(spritz_ctx *hash_ctx)
{
  stateInit(hash_ctx);
}

/* Add data chunk to hash */
void
spritz_hash_update(spritz_ctx *hash_ctx,
                   const uint8_t *data, unsigned int dataLen)
{
  absorbBytes(hash_ctx, data, dataLen);
}

/* Output hash digest */
void
spritz_hash_final(spritz_ctx *hash_ctx,
                  uint8_t *digest, uint8_t digestLen)
{
  absorbStop(hash_ctx);
  absorb(hash_ctx, digestLen);
  squeeze(hash_ctx, digest, digestLen);
#ifdef WIPE_AFTER_USAGE
  spritz_wipe_ctx(hash_ctx);
#endif
}

/* Cryptographic hash function */
void
spritz_hash(uint8_t *digest, uint8_t digestLen,
            const uint8_t *data, unsigned int dataLen)
{
  spritz_ctx hash_ctx;
  spritz_hash_setup(&hash_ctx);
  spritz_hash_update(&hash_ctx, data, dataLen);
  spritz_hash_final(&hash_ctx, digest, digestLen);
}


/* Setup spritz MAC state (spritz_ctx) */
void
spritz_mac_setup(spritz_ctx *mac_ctx,
                 const uint8_t *key, unsigned int keyLen)
{
  stateInit(mac_ctx); /* Like spritz_hash_update() */
  absorbBytes(mac_ctx, key, keyLen);
  absorbStop(mac_ctx);
}

/* Add message/data chunk to MAC */
void
spritz_mac_update(spritz_ctx *mac_ctx,
                  const uint8_t *msg, unsigned int msgLen)
{
  absorbBytes(mac_ctx, msg, msgLen); /* Like spritz_hash_update() */
}

/* Output MAC digest */
void
spritz_mac_final(spritz_ctx *mac_ctx,
                 uint8_t *digest, uint8_t digestLen)
{
  spritz_hash_final(mac_ctx, digest, digestLen);
}

/* Message Authentication Code (MAC) function */
void
spritz_mac(uint8_t *digest, uint8_t digestLen,
           const uint8_t *msg, unsigned int msgLen,
           const uint8_t *key, unsigned int keyLen)
{
  spritz_ctx mac_ctx;
  spritz_mac_setup(&mac_ctx, key, keyLen);
  spritz_mac_update(&mac_ctx, msg, msgLen);
  spritz_mac_final(&mac_ctx, digest, digestLen);
}
