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

#define SPRITZ_HALF_N 128 /* SPRITZ_N/2 */
#define SAFE_TIMING_CRUSH


SpritzCipher::SpritzCipher() { }


void SpritzCipher::swap(byte *a, byte *b)
{
  byte t = *a;
  *a  = *b;
  *b  = t;
}


void SpritzCipher::stateInit(spritz_t *ctx)
{
  unsigned int i;
  ctx->i = ctx->j = ctx->k = ctx->z = ctx->a = 0;
  ctx->w = 1;
  for (i = 0; i < SPRITZ_N; i++) {
    ctx->s[i] = byte(i);
  }
}

void SpritzCipher::update(spritz_t *ctx)
{
  ctx->i = byte(ctx->i + ctx->w);
  ctx->j = byte(ctx->k + ctx->s[byte(ctx->j + ctx->s[ctx->i])]);
  ctx->k = byte(ctx->k + ctx->i + ctx->s[ctx->j]);
  swap(&ctx->s[ctx->i], &ctx->s[ctx->j]);
}

void SpritzCipher::whip(spritz_t *ctx)
{
  unsigned int i;
  for (i = 0; i < (SPRITZ_N * 2); i++) {
    update(ctx);
  }
  ctx->w = byte(ctx->w + 2);
}

void SpritzCipher::crush(spritz_t *ctx)
{
  byte i, j = byte(SPRITZ_N - 1); /* j=255 */
#ifdef SAFE_TIMING_CRUSH
  byte s_i, s_j;
  for (i = 0; i < SPRITZ_HALF_N; i++, j--) {
    if ((s_i = ctx->s[i]) > (s_j = ctx->s[j])) {
      ctx->s[i] = s_j;
      ctx->s[j] = s_i;
    }
    else {
      ctx->s[i] = s_i;
      ctx->s[j] = s_j;
    }
  }

#else /* SAFE_TIMING_CRUSH */
  for (i = 0; i < SPRITZ_HALF_N; i++, j--) {
    if (ctx->s[i] > ctx->s[j]) {
      swap(&ctx->s[i], &ctx->s[j]);
    }
  }
#endif
}

void SpritzCipher::shuffle(spritz_t *ctx)
{
  whip(ctx);
  crush(ctx);
  whip(ctx);
  crush(ctx);
  whip(ctx);
  ctx->a = 0;
}

void SpritzCipher::absorbNibble(spritz_t *ctx, const byte nibble)
{
  if (ctx->a == SPRITZ_HALF_N) {
    shuffle(ctx);
  }
  swap(&ctx->s[ctx->a], &ctx->s[byte(SPRITZ_HALF_N + nibble)]);
  ctx->a++;
}

void SpritzCipher::absorb(spritz_t *ctx, const byte byte)
{
  absorbNibble(ctx, byte % 16); /* Low */
  absorbNibble(ctx, byte / 16); /* High */
}

void SpritzCipher::absorbBytes(spritz_t *ctx, const byte *buf, unsigned int len)
{
  unsigned int i;
  for (i = 0; i < len; i++) {
    absorb(ctx, buf[i]);
  }
}

void SpritzCipher::absorbStop(spritz_t *ctx)
{
  if (ctx->a == SPRITZ_HALF_N) {
    shuffle(ctx);
  }
  ctx->a++;
}

byte SpritzCipher::output(spritz_t *ctx)
{
  ctx->z = ctx->s[byte(ctx->j + ctx->s[byte(ctx->i + ctx->s[byte(ctx->z + ctx->k)])])];
  return ctx->z;
}

byte SpritzCipher::drip(spritz_t *ctx)
{
  if (ctx->a) {
    shuffle(ctx);
  }
  update(ctx);
  return output(ctx);
}

/* squeeze() for hash() and mac() */
void SpritzCipher::squeeze(spritz_t *ctx, byte *out, byte len)
{
  byte i;
  if (ctx->a) {
    shuffle(ctx);
  }
  for (i = 0; i < len; i++) {
    out[i] = drip(ctx);
  }
}



void SpritzCipher::setup(spritz_t *ctx,
                         const byte *key, unsigned int keyLen)
{
  stateInit(ctx);
  absorbBytes(ctx, key, keyLen);
}

/* Use setupIV() after setup() to add NONCE */
void SpritzCipher::setupIV(spritz_t *ctx,
                           const byte *nonce, unsigned int nonceLen)
{
  absorbStop(ctx);
  absorbBytes(ctx, nonce, nonceLen);
}

byte SpritzCipher::stream(spritz_t *ctx)
{
  return drip(ctx);
}


void SpritzCipher::hash(byte *digest, byte digestLen,
                        const byte *data, unsigned int dataLen)
{
  spritz_t ctx;
  stateInit(&ctx);
  absorbBytes(&ctx, data, dataLen);
  absorbStop(&ctx);
  absorb(&ctx, digestLen);
  squeeze(&ctx, digest, digestLen);
}

void SpritzCipher::mac(byte *digest, byte digestLen,
                       const byte *msg, unsigned int msgLen,
                       const byte *key, unsigned int keyLen)
{
  spritz_t ctx;
  stateInit(&ctx);
  absorbBytes(&ctx, key, keyLen);
  absorbStop(&ctx);
  absorbBytes(&ctx, msg, msgLen);
  absorbStop(&ctx);
  absorb(&ctx, digestLen);
  squeeze(&ctx, digest, digestLen);
}
