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
 *
 */

#include "SpritzCipher.h"


SpritzCipher::SpritzCipher() { }


#define SPRITZ_HALF_N 128 /* SPRITZ_N/2 */
#define SAFE_TIMING_CRUSH

/******************************************************************************/
void SpritzCipher::swap(unsigned char *a, unsigned char *b)
{
  unsigned char t = *a;
  *a  = *b;
  *b  = t;
}

/******************************************************************************/
void SpritzCipher::stateInit(spritz_t *ctx)
{
  unsigned int i;

  ctx->i = ctx->j = ctx->k = ctx->z = ctx->a = 0;
  ctx->w = 1;

  for (i = 0; i < SPRITZ_N; i++) {
    ctx->s[i] = (unsigned char)i;
  }
}

void SpritzCipher::update(spritz_t *ctx)
{
  ctx->i = (unsigned char)(ctx->i + ctx->w);
  ctx->j = (unsigned char)(ctx->k + ctx->s[(unsigned char)(ctx->j + ctx->s[ctx->i])]);
  ctx->k = (unsigned char)(ctx->k + ctx->i + ctx->s[ctx->j]);
  swap(&ctx->s[ctx->i], &ctx->s[ctx->j]);
}

void SpritzCipher::whip(spritz_t *ctx)
{
  unsigned int i;

  for (i = 0; i < (SPRITZ_N * 2); i++) {
    update(ctx);
  }
  ctx->w = (unsigned char)(ctx->w + 2);
}

void SpritzCipher::crush(spritz_t *ctx)
{
  unsigned char j = (unsigned char)(SPRITZ_N - 1); /* j=255 */
  unsigned int i;

#ifdef SAFE_TIMING_CRUSH
  unsigned char s_i, s_j;
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

void SpritzCipher::absorbNibble(spritz_t *ctx, const unsigned char nibble)
{
  if (ctx->a == SPRITZ_HALF_N) {
    shuffle(ctx);
  }
  swap(&ctx->s[ctx->a], &ctx->s[(unsigned char)(SPRITZ_HALF_N + nibble)]);
  ctx->a++;
}

void SpritzCipher::absorb(spritz_t *ctx, const unsigned char byte)
{
  absorbNibble(ctx, byte % 16); /* Low */
  absorbNibble(ctx, byte / 16); /* High */
}

void SpritzCipher::absorbBytes(spritz_t *ctx, const unsigned char *buf, unsigned int len)
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

unsigned char SpritzCipher::output(spritz_t *ctx)
{
  ctx->z = ctx->s[(unsigned char)(ctx->j + ctx->s[(unsigned char)(ctx->i + ctx->s[(unsigned char)(ctx->z + ctx->k)])])];
  return ctx->z;
}

unsigned char SpritzCipher::drip(spritz_t *ctx)
{
  if (ctx->a) {
    shuffle(ctx);
  }
  update(ctx);

  return output(ctx);
}

/* squeeze() used in Hash and MAC functions */
void SpritzCipher::squeeze(spritz_t *ctx, unsigned char *out, unsigned int len)
{
  unsigned int i;

  if (ctx->a) {
    shuffle(ctx);
  }
  for (i = 0; i < len; i++) {
    out[i] = drip(ctx);
  }
}

/******************************************************************************/
void SpritzCipher::setup(spritz_t *ctx,
                         const unsigned char *key, unsigned int keyLen)
{
  stateInit(ctx);
  absorbBytes(ctx, key, keyLen);
}

/* Use setupIV() after setup() to add NONCE */
void SpritzCipher::setupIV(spritz_t *ctx,
                           const unsigned char *nonce, unsigned int nonceLen)
{
  absorbStop(ctx);
  absorbBytes(ctx, nonce, nonceLen);
}

unsigned char SpritzCipher::stream(spritz_t *ctx)
{
  return drip(ctx);
}


void SpritzCipher::hash(unsigned char *digest, unsigned char digestLen,
                        const unsigned char *data, unsigned int dataLen)
{
  spritz_t ctx;

  stateInit(&ctx);
  absorbBytes(&ctx, data, dataLen);
  absorbStop(&ctx);
  absorb(&ctx, digestLen);
  squeeze(&ctx, digest, (unsigned int)digestLen);
}

void SpritzCipher::mac(unsigned char *digest, unsigned char digestLen,
                       const unsigned char *msg, unsigned int msgLen,
                       const unsigned char *key, unsigned int keyLen)
{
  spritz_t ctx;

  stateInit(&ctx);
  absorbBytes(&ctx, key, keyLen);
  absorbStop(&ctx);
  absorbBytes(&ctx, msg, msgLen);
  absorbStop(&ctx);
  absorb(&ctx, digestLen);
  squeeze(&ctx, digest, (unsigned int)digestLen);
}
