/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015-2016 Abderraouf Adjal
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
spritz_ctx_s_swap(spritz_ctx *ctx, uint8_t index_a, uint8_t index_b)
{
  uint8_t t = ctx->s[index_a];

  ctx->s[index_a] = ctx->s[index_b];
  ctx->s[index_b] = t;
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
  ctx->j = (uint8_t)(ctx->s[(uint8_t)(ctx->s[ctx->i] + ctx->j)] + ctx->k);
  ctx->k = (uint8_t)(ctx->s[ctx->j] + ctx->k + ctx->i);
  spritz_ctx_s_swap(ctx, ctx->i, ctx->j);
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

#if defined(SAFE_TIMING_CRUSH)
static void
/* SAFE_TIMING_CRUSH and GCC compiler, disable optimization for this function */
# if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* SAFE_TIMING_CRUSH and Clang compiler, disable optimization for this function */
# elif defined(__clang__)
__attribute__ ((optnone))
# endif
crush(spritz_ctx *ctx)
{
  uint8_t i, j, s_i, s_j;

  for (i = 0, j = SPRITZ_N_MINUS_1; i < SPRITZ_N_HALF; i++, j--) {
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
  }
}
#else /* SAFE_TIMING_CRUSH */
/* non equal time crush() */
static void
crush(spritz_ctx *ctx)
{
  uint8_t i, j;

  for (i = 0, j = SPRITZ_N_MINUS_1; i < SPRITZ_N_HALF; i++, j--) {
    if (ctx->s[i] > ctx->s[j]) {
      spritz_ctx_s_swap(ctx, i, j);
    }
  }
}
#endif

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
  spritz_ctx_s_swap(ctx, ctx->a, (uint8_t)(SPRITZ_N_HALF + nibble));
  ctx->a++;
}
static void
absorb(spritz_ctx *ctx, const uint8_t octet)
{
  absorbNibble(ctx, octet % 16); /* Low */
  absorbNibble(ctx, octet / 16); /* High */
}
static void
absorbBytes(spritz_ctx *ctx, const uint8_t *buf, uint16_t len)
{
  uint16_t i;

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
  ctx->z = ctx->s[(uint8_t)(ctx->s[(uint8_t)(ctx->s[(uint8_t)(ctx->z + ctx->k)] + ctx->i)] + ctx->j)];
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


/* |====================|| User Functions ||====================| */

/* Timing-safe comparison for "data_a" and "data_b" equality.
 * This function can be used to compare passwords hash safely.
 * Return zero (0x00) if "data_a" equal "data_b" or "len" is zero,
 * non-zero value if they are not equal.
 */
uint8_t
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_compare(const uint8_t *data_a, const uint8_t *data_b, uint16_t len)
{
  uint8_t d;
  uint16_t i;

  for (i = 0, d = 0; i < len; i++) {
    d |= data_a[i] ^ data_b[i];
  }

  return d;
}

/* Wipe "buf" data by replacing it with zeros (0x00). */
void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_memzero(uint8_t *buf, uint16_t len)
{
  uint16_t i;
  for (i = 0; i < len; i++) {
    buf[i] = 0;
  }
}


/* Setup spritz state (spritz_ctx) with a key */
void
spritz_setup(spritz_ctx *ctx,
             const uint8_t *key, uint8_t keyLen)
{
  stateInit(ctx);
  absorbBytes(ctx, key, keyLen);
  if (ctx->a) {
    shuffle(ctx);
  }
}

/* Setup spritz state (spritz_ctx) with a key and nonce/Salt/IV */
void
spritz_setupWithIV(spritz_ctx *ctx,
                   const uint8_t *key, uint8_t keyLen,
                   const uint8_t *nonce, uint8_t nonceLen)
{
  stateInit(ctx);
  absorbBytes(ctx, key, keyLen);
  absorbStop(ctx);
  absorbBytes(ctx, nonce, nonceLen);
  if (ctx->a) {
    shuffle(ctx);
  }
}

/* Generates a byte of keystream from spritz state (spritz_ctx).
 * Can be used to make a random key.
 * spritz_random_byte() usable after spritz_setup() or spritz_setupWithIV().
 */
uint8_t
spritz_random_byte(spritz_ctx *ctx)
{
  return drip(ctx);
}

/* Add entropy to spritz state (spritz_ctx) using absorb().
 * spritz_add_entropy() usable after spritz_setup() or spritz_setupWithIV().
 */
void
spritz_add_entropy(spritz_ctx *ctx,
            const uint8_t *entropy, uint16_t len)
{
  absorbBytes(ctx, entropy, len);
}

/* Encrypt or decrypt data chunk by XOR-ing it with spritz keystream.
 * spritz_crypt() usable after spritz_setup() or spritz_setupWithIV().
 */
void
spritz_crypt(spritz_ctx *ctx,
             const uint8_t *data, uint16_t dataLen,
             uint8_t *dataOut)
{
  uint16_t i;

  for (i = 0; i < dataLen; i++) {
    dataOut[i] = data[i] ^ spritz_random_byte(ctx);
  }
}

/* Wipe spritz context data by replacing "ctx" data with zeros (0x00) */
void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_ctx_memzero(spritz_ctx *ctx)
{
  uint8_t i;

  ctx->i = ctx->j = ctx->k = ctx->z = ctx->a = ctx->w = 0;
  for (i = 0; i < SPRITZ_N_MINUS_1; i++) {
    ctx->s[i] = 0;
  }
  ctx->s[255] = 0;
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
                   const uint8_t *data, uint16_t dataLen)
{
  absorbBytes(hash_ctx, data, dataLen);
}

/* Output hash digest */
void
spritz_hash_final(spritz_ctx *hash_ctx,
                  uint8_t *digest, uint8_t digestLen)
{
  uint8_t i;

  absorbStop(hash_ctx);
  absorb(hash_ctx, digestLen);
  /* squeeze() */
  if (hash_ctx->a) {
    shuffle(hash_ctx);
  }
  for (i = 0; i < digestLen; i++) {
    digest[i] = drip(hash_ctx);
  }
#ifdef WIPE_AFTER_USAGE
  spritz_ctx_memzero(hash_ctx);
#endif
}

/* Cryptographic hash function */
void
spritz_hash(uint8_t *digest, uint8_t digestLen,
            const uint8_t *data, uint16_t dataLen)
{
  spritz_ctx hash_ctx;

  spritz_hash_setup(&hash_ctx); /* stateInit() */
  spritz_hash_update(&hash_ctx, data, dataLen); /* absorbBytes() */
  spritz_hash_final(&hash_ctx, digest, digestLen);
}


/* Setup spritz MAC state (spritz_ctx) */
void
spritz_mac_setup(spritz_ctx *mac_ctx,
                 const uint8_t *key, uint16_t keyLen)
{
  spritz_hash_setup(mac_ctx); /* stateInit() */
  spritz_hash_update(mac_ctx, key, keyLen); /* absorbBytes() */
  absorbStop(mac_ctx);
}

/* Add message/data chunk to MAC */
void
spritz_mac_update(spritz_ctx *mac_ctx,
                  const uint8_t *msg, uint16_t msgLen)
{
  spritz_hash_update(mac_ctx, msg, msgLen); /* absorbBytes() */
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
           const uint8_t *msg, uint16_t msgLen,
           const uint8_t *key, uint16_t keyLen)
{
  spritz_ctx mac_ctx;

  spritz_mac_setup(&mac_ctx, key, keyLen);
  spritz_mac_update(&mac_ctx, msg, msgLen); /* absorbBytes() */
  spritz_mac_final(&mac_ctx, digest, digestLen);
}
