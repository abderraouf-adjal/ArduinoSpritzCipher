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


#include "SpritzCipher.h" /* Data types and constants */


#define SPRITZ_N_MINUS_1 255 /* SPRITZ_N - 1 */
#define SPRITZ_N_HALF 128 /* SPRITZ_N / 2 */


static void
spritz_state_s_swap(spritz_ctx *ctx, uint8_t index_a, uint8_t index_b)
{
#ifdef SPRITZ_WIPE_TRACES_PARANOID
  ctx->tmp1       = ctx->s[index_a];
  ctx->s[index_a] = ctx->s[index_b];
  ctx->s[index_b] = ctx->tmp1;
#else
  uint8_t tmp     = ctx->s[index_a];
  ctx->s[index_a] = ctx->s[index_b];
  ctx->s[index_b] = tmp;
#endif /* SPRITZ_WIPE_TRACES_PARANOID */
}


static void
spritz_state_init(spritz_ctx *ctx)
{
  uint8_t i = 0;

  /* Loop for SPRITZ_N=256 */
  do {
    ctx->s[i] = i;
  } while (++i);

  ctx->i = 0;
  ctx->j = 0;
  ctx->k = 0;
  ctx->z = 0;
  ctx->a = 0;
  ctx->w = 1;
}

static void
update(spritz_ctx *ctx)
{
  ctx->i = (uint8_t)(ctx->i + ctx->w);
  ctx->j = (uint8_t)(ctx->s[(uint8_t)(ctx->s[ctx->i] + ctx->j)] + ctx->k);
  ctx->k = (uint8_t)(ctx->s[ctx->j] + ctx->k + ctx->i);
  spritz_state_s_swap(ctx, ctx->i, ctx->j);
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

#ifdef SPRITZ_TIMING_SAFE_CRUSH
static void
/* SPRITZ_TIMING_SAFE_CRUSH and GCC, disable optimization for this function */
# if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* SPRITZ_TIMING_SAFE_CRUSH and Clang, disable optimization for this function */
# elif defined(__clang__)
__attribute__ ((optnone))
# endif
crush(spritz_ctx *ctx)
{
  uint8_t i = 0, j = SPRITZ_N_MINUS_1;
# ifdef SPRITZ_WIPE_TRACES_PARANOID
  for (; i < SPRITZ_N_HALF; i++, j--) {
    ctx->tmp1 = ctx->s[i]; /* s_i=ctx->s[i] */
    ctx->tmp2 = ctx->s[j]; /* s_j=ctx->s[j] */
    if (ctx->tmp1 > ctx->tmp2) { /* if(s_i>s_j) */
      ctx->s[i] = ctx->tmp2; /* ctx->s[i]=s_j */
      ctx->s[j] = ctx->tmp1; /* ctx->s[j]=s_i */
    }
    else {
      ctx->s[i] = ctx->tmp1; /* ctx->s[i]=s_i */
      ctx->s[j] = ctx->tmp2; /* ctx->s[j]=s_j */
    }
  }
# else
  uint8_t s_i, s_j;
  for (; i < SPRITZ_N_HALF; i++, j--) {
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
# endif /* SPRITZ_WIPE_TRACES_PARANOID */
}
#else /* SPRITZ_TIMING_SAFE_CRUSH */
/* non equal/safe time crush() */
static void
crush(spritz_ctx *ctx)
{
  uint8_t i = 0, j = SPRITZ_N_MINUS_1;
  for (; i < SPRITZ_N_HALF; i++, j--) {
    if (ctx->s[i] > ctx->s[j]) {
      spritz_state_s_swap(ctx, i, j);
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

/* Note: Nibble=4-bit; Octet=2*Nibble=8-bit; Byte=Octet (in modern/most computers) */
static void
absorbNibble(spritz_ctx *ctx, const uint8_t nibble)
{
  if (ctx->a == SPRITZ_N_HALF) {
    shuffle(ctx);
  }
  spritz_state_s_swap(ctx, ctx->a, (uint8_t)(SPRITZ_N_HALF + nibble));
  ctx->a++;
}
static void
absorb(spritz_ctx *ctx, const uint8_t octet)
{
  absorbNibble(ctx, octet % 16); /* With the Right/Low nibble */
  absorbNibble(ctx, octet / 16); /* With the Left/High nibble */
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
  ctx->z = ctx->s[(ctx->s[(ctx->s[(ctx->z + ctx->k) % SPRITZ_N] + ctx->i) % SPRITZ_N] + ctx->j) % SPRITZ_N];
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

/** spritz_compare()
 * Timing-safe equality comparison for `data_a` and `data_b`.
 * This function can be used to compare the password's hash safely.
 *
 * Parameter data_a: Data a to be compare with b.
 * Parameter data_b: Data b to be compare with a.
 * Parameter len:    Length of the array in bytes.
 *
 * Return: Equality result.
 *         Zero (0x00) if `data_a` equals `data_b` OR if `len` is zero,
 *         Non-zero value if they are NOT equal.
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
  uint8_t d = 0;
  uint16_t i;

  for (i = 0; i < len; i++) {
    d |= data_a[i] ^ data_b[i];
  }

#ifdef SPRITZ_WIPE_TRACES_PARANOID
  /* It may be possible to use `d=!!d;` for performnce,
   * But audit the assembly code first.
   */
  d |= d >> 1; /* |_|_|_|_|_|_|S|D| `D |= S` */
  d |= d >> 2; /* |_|_|_|_|_|S|_|D| */
  d |= d >> 3; /* |_|_|_|_|S|_|_|D| */
  d |= d >> 4; /* |_|_|_|S|_|_|_|D| */
  d |= d >> 5; /* |_|_|S|_|_|_|_|D| */
  d |= d >> 6; /* |_|S|_|_|_|_|_|D| */
  d |= d >> 7; /* |S|_|_|_|_|_|_|D| */
  d &= 1;      /* |0|0|0|0|0|0|0|D| Zero all bits except LSB */
#endif

  return d;
}

/** spritz_memzero()
 * Wipe `buf` data by replacing it with zeros (0x00).
 *
 * Parameter buf: Data to replace it with zeros (0x00).
 * Parameter len: Length of array in bytes.
 */
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

/** spritz_state_memzero()
 * Wipe `spritz_ctx`'s data by replacing its data with zeros (0x00).
 *
 * Parameter ctx: The context.
 */
void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_state_memzero(spritz_ctx *ctx)
{
  uint8_t i = 0;

  /* Loop for SPRITZ_N=256 */
  do {
    ctx->s[i] = 0;
  } while (++i);

  ctx->i = 0;
  ctx->j = 0;
  ctx->k = 0;
  ctx->z = 0;
  ctx->a = 0;
  ctx->w = 0;

#ifdef SPRITZ_WIPE_TRACES_PARANOID
  ctx->tmp1 = 0;
  ctx->tmp2 = 0;
#endif
}


/** spritz_setup()
 * Setup the spritz state `spritz_ctx` with a key.
 *
 * Parameter ctx:    The context.
 * Parameter key:    The key.
 * Parameter keylen: Length of the key in bytes.
 */
void
spritz_setup(spritz_ctx *ctx,
             const uint8_t *key, uint8_t keyLen)
{
  spritz_state_init(ctx);
  absorbBytes(ctx, key, keyLen);
  if (ctx->a) {
    shuffle(ctx);
  }
}

/** spritz_setup_withiv()
 * Setup the spritz state `spritz_ctx` with a key and nonce/salt/iv.
 *
 * Parameter ctx:      The context.
 * Parameter key:      The key.
 * Parameter keylen:   Length of the key in bytes.
 * Parameter nonce:    The nonce (salt).
 * Parameter noncelen: Length of the nonce in bytes.
 */
void
spritz_setup_withIV(spritz_ctx *ctx,
                    const uint8_t *key, uint8_t keyLen,
                    const uint8_t *nonce, uint8_t nonceLen)
{
  spritz_state_init(ctx);
  absorbBytes(ctx, key, keyLen);
  absorbStop(ctx);
  absorbBytes(ctx, nonce, nonceLen);
  if (ctx->a) {
    shuffle(ctx);
  }
}

/** spritz_random8()
 * Generates a random byte from the spritz state `spritz_ctx`.
 * Usable only after calling spritz_setup() or spritz_setup_withiv().
 *
 * Parameter ctx: The context.
 *
 * Return: Byte of keystream.
 */
uint8_t
spritz_random8(spritz_ctx *ctx)
{
  return drip(ctx);
}

/** spritz_random32()
 * Generates a random 32-bit (4 bytes) from the spritz state `spritz_ctx`.
 * Usable only after calling spritz_setup() or spritz_setup_withiv().
 *
 * Parameter ctx: The context.
 *
 * Return: 32-bit (4 bytes) of keystream.
 */
uint32_t
spritz_random32(spritz_ctx *ctx)
{
  return (uint32_t)(
      ((uint32_t)(spritz_random8(ctx)) <<  0)
    | ((uint32_t)(spritz_random8(ctx)) <<  8)
    | ((uint32_t)(spritz_random8(ctx)) << 16)
    | ((uint32_t)(spritz_random8(ctx)) << 24));
}

/** spritz_random32_uniform()
 * Calculate an uniformly distributed random number less than `upper_bound` avoiding modulo bias.
 *
 * Uniformity is achieved by generating new random numbers until the one
 * returned is outside the range [0, 2**32 % upper_bound).
 * This guarantees the selected random number will be inside
 * [2**32 % upper_bound, 2**32) which maps back to [0, upper_bound)
 * after reduction modulo upper_bound.
 * spritz_random32_uniform() derives from OpenBSD's arc4random_uniform()
 *
 * Usable only after calling spritz_setup() or spritz_setup_withiv().
 *
 * Parameter ctx:         The context.
 * Parameter upper_bound: The roof, `upper_bound - 1` is the largest number that can be returned.
 *
 * Return: Random number less than upper_bound, 0 if upper_bound<2.
 */
uint32_t
spritz_random32_uniform(spritz_ctx *ctx, uint32_t upper_bound)
{
  uint32_t r, min;

  if (upper_bound < 2)
  {
    return 0;
  }

  /* 2**32 % x == (2**32 - x) % x */
  min = (uint32_t)(-upper_bound % upper_bound);

  /* This could theoretically loop forever but each retry has
   * p > 0.5 (worst case, usually far better) of selecting a
   * number inside the range we need, so it should rarely need
   * to re-roll.
   */
  for (;;) {
    r = spritz_random32(ctx);
    if (r >= min)
    {
      return (uint32_t)(r % upper_bound);
    }
  }
}

/** spritz_add_entropy()
 * Add entropy to the spritz state `spritz_ctx` using absorb().
 * Usable only after calling spritz_setup() or spritz_setup_withiv().
 *
 * Parameter ctx:     The context.
 * Parameter entropy: The entropy array.
 * Parameter len:     Length of the entropy array in bytes.
 */
void
spritz_add_entropy(spritz_ctx *ctx,
            const uint8_t *entropy, uint16_t len)
{
  absorbBytes(ctx, entropy, len);
}

/** spritz_crypt()
 * Encrypt or decrypt data chunk by XOR-ing it with the spritz keystream.
 * Usable only after calling spritz_setup() or spritz_setup_withiv().
 *
 * Parameter ctx:     The context.
 * Parameter data:    The data to encrypt or decrypt.
 * Parameter datalen: Length of the data in bytes.
 * Parameter dataout: The output.
 */
void
spritz_crypt(spritz_ctx *ctx,
             const uint8_t *data, uint16_t dataLen,
             uint8_t *dataOut)
{
  uint16_t i;

  for (i = 0; i < dataLen; i++) {
    dataOut[i] = data[i] ^ drip(ctx);
  }
}


/** spritz_hash_setup()
 * Setup the spritz hash state `spritz_ctx`.
 *
 * Parameter hash_ctx: The hash context (ctx).
 */
void
spritz_hash_setup(spritz_ctx *hash_ctx)
{
  spritz_state_init(hash_ctx);
}

/** spritz_hash_update()
 * Add a message/data chunk `data` to hash.
 *
 * Parameter hash_ctx: The hash context (ctx).
 * Parameter data:     The data chunk to hash.
 * Parameter datalen:  Length of the data in bytes.
 */
void
spritz_hash_update(spritz_ctx *hash_ctx,
                   const uint8_t *data, uint16_t dataLen)
{
  absorbBytes(hash_ctx, data, dataLen);
}

/** spritz_hash_final()
 * Output the hash digest.
 *
 * Parameter hash_ctx:  The hash context (ctx).
 * Parameter digest:    The digest (hash) output.
 * Parameter digestlen: Length of the digest in bytes.
 */
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
}

/** spritz_hash()
 * Cryptographic hash function.
 *
 * Parameter digest:    The digest (hash) output.
 * Parameter digestlen: Length of the digest in bytes.
 * Parameter data:      The data to hash.
 * Parameter datalen:   Length of the data in bytes.
 */
void
spritz_hash(uint8_t *digest, uint8_t digestLen,
            const uint8_t *data, uint16_t dataLen)
{
  spritz_ctx hash_ctx;

  spritz_hash_setup(&hash_ctx); /* spritz_state_init() */
  spritz_hash_update(&hash_ctx, data, dataLen); /* absorbBytes() */
  spritz_hash_final(&hash_ctx, digest, digestLen);

  /* `hash_ctx` data will be replaced with 0x00 if SPRITZ_WIPE_TRACES is defined */
#ifdef SPRITZ_WIPE_TRACES
  spritz_state_memzero(&hash_ctx);
#endif
}


/** spritz_mac_setup()
 * Setup the spritz message authentication code (MAC) state `spritz_ctx`.
 *
 * Parameter mac_ctx: The message authentication code (MAC) context (ctx).
 * Parameter key:     The secret key.
 * Parameter keylen:  Length of the key in bytes.
 */
void
spritz_mac_setup(spritz_ctx *mac_ctx,
                 const uint8_t *key, uint16_t keyLen)
{
  spritz_hash_setup(mac_ctx); /* spritz_state_init() */
  spritz_hash_update(mac_ctx, key, keyLen); /* absorbBytes() */
  absorbStop(mac_ctx);
}

/** spritz_mac_update()
 * Add a message/data chunk to message authentication code (MAC).
 *
 * Parameter hash_ctx: The hash context (ctx).
 * Parameter msg:      The message chunk to be authenticated.
 * Parameter msglen:   Length of the message in bytes.
 */
void
spritz_mac_update(spritz_ctx *mac_ctx,
                  const uint8_t *msg, uint16_t msgLen)
{
  spritz_hash_update(mac_ctx, msg, msgLen); /* absorbBytes() */
}

/** spritz_mac_final()
 * Output the message authentication code (MAC) digest.
 *
 * Parameter mac_ctx:   The message authentication code (MAC) context (ctx).
 * Parameter digest:    Message authentication code (MAC) digest output.
 * Parameter digestlen: Length of the digest in bytes.
 */
void
spritz_mac_final(spritz_ctx *mac_ctx,
                 uint8_t *digest, uint8_t digestLen)
{
  spritz_hash_final(mac_ctx, digest, digestLen);
}

/** spritz_mac()
 * Message Authentication Code (MAC) function.
 *
 * Parameter digest:    Message authentication code (MAC) digest output.
 * Parameter digestlen: Length of the digest in bytes.
 * Parameter msg:       The message to be authenticated.
 * Parameter msglen:    Length of the message in bytes.
 * Parameter key:       The secret key.
 * Parameter keylen:    Length of the key in bytes.
 */
void
spritz_mac(uint8_t *digest, uint8_t digestLen,
           const uint8_t *msg, uint16_t msgLen,
           const uint8_t *key, uint16_t keyLen)
{
  spritz_ctx mac_ctx;

  spritz_mac_setup(&mac_ctx, key, keyLen);
  spritz_mac_update(&mac_ctx, msg, msgLen); /* absorbBytes() */
  spritz_mac_final(&mac_ctx, digest, digestLen);

  /* `mac_ctx` data will be replaced with 0x00 if SPRITZ_WIPE_TRACES is defined */
#ifdef SPRITZ_WIPE_TRACES
  spritz_state_memzero(&mac_ctx);
#endif
}
