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


#ifndef SPRITZCIPHER_H
#define SPRITZCIPHER_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h> /* uint8_t, uint16_t, uint32_t */


/** SPRITZ_TIMING_SAFE_CRUSH
 * If defined, the equal time crush() will be used.
 * This may NOT be useful in some compilers with optimization (except GCC and Clang).
 */
#define SPRITZ_TIMING_SAFE_CRUSH

/** SPRITZ_WIPE_TRACES
 * If defined, sensitive data (like spritz_ctx) when they are
 * no longer needed in functions such as hash and mac will be wiped.
 * Functions that SPRITZ_WIPE_TRACES is involved with: spritz_hash(), spritz_mac().
 */
#define SPRITZ_WIPE_TRACES

/** SPRITZ_WIPE_TRACES_PARANOID
 * If defined, the library functions internal variables will be wiped if it contains
 * a bit or more of spritz state such as temporary variables in a swap function
 * or an user data be wiped when they are no longer needed.
 * Variables that contain data length will not be wiped.
 *
 * If defined, Then SPRITZ_WIPE_TRACES and SPRITZ_TIMING_SAFE_CRUSH
 * will be defined automatically.
 */
/* #define SPRITZ_WIPE_TRACES_PARANOID */

#ifdef SPRITZ_WIPE_TRACES_PARANOID
# ifndef SPRITZ_TIMING_SAFE_CRUSH
#  define SPRITZ_TIMING_SAFE_CRUSH
# endif
# ifndef SPRITZ_WIPE_TRACES
#  define SPRITZ_WIPE_TRACES
# endif
#endif

/** SPRITZ_N
 * Present the value of N in this spritz implementation, DO NOT change SPRITZ_N value.
 */
#define SPRITZ_N 256

/* `Semantic Versioning` of this library */
#define SPRITZ_LIBRARY_VERSION_STRING "1.0.3"
#define SPRITZ_LIBRARY_VERSION_MAJOR 1
#define SPRITZ_LIBRARY_VERSION_MINOR 0
#define SPRITZ_LIBRARY_VERSION_PATCH 3


/** spritz_ctx
 * The context (contains the state), Holds indices and s-box.
 */
typedef struct
{
  uint8_t s[SPRITZ_N], i, j, k, z, a, w;
#ifdef SPRITZ_WIPE_TRACES_PARANOID
  /* `tmp1` for: spritz_state_s_swap(), safe timing crush().
   * `tmp2` for: The safe timing crush().
   */
  uint8_t tmp1, tmp2;
#endif
} spritz_ctx;

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
spritz_compare(const uint8_t *data_a, const uint8_t *data_b, uint16_t len);

/** spritz_memzero()
 * Wipe `buf` data by replacing it with zeros (0x00).
 *
 * Parameter buf: Data to replace it with zeros (0x00).
 * Parameter len: Length of array in bytes.
 */
void
spritz_memzero(uint8_t *buf, uint16_t len);

/** spritz_state_memzero()
 * Wipe `spritz_ctx`'s data by replacing its data with zeros (0x00).
 *
 * Parameter ctx: The context.
 */
void
spritz_state_memzero(spritz_ctx *ctx);


/** spritz_setup()
 * Setup the spritz state `spritz_ctx` with a key.
 *
 * Parameter ctx:    The context.
 * Parameter key:    The key.
 * Parameter keylen: Length of the key in bytes.
 */
void
spritz_setup(spritz_ctx *ctx,
             const uint8_t *key, uint8_t keyLen);

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
                    const uint8_t *nonce, uint8_t nonceLen);

/** spritz_random8()
 * Generates a random byte from the spritz state `spritz_ctx`.
 * Usable only after calling spritz_setup() or spritz_setup_withiv().
 *
 * Parameter ctx: The context.
 *
 * Return: Byte of keystream.
 */
uint8_t
spritz_random8(spritz_ctx *ctx);

/** spritz_random32()
 * Generates a random 32-bit (4 bytes) from the spritz state `spritz_ctx`.
 * Usable only after calling spritz_setup() or spritz_setup_withiv().
 *
 * Parameter ctx: The context.
 *
 * Return: 32-bit (4 bytes) of keystream.
 */
uint32_t
spritz_random32(spritz_ctx *ctx);

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
spritz_random32_uniform(spritz_ctx *ctx, uint32_t upper_bound);

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
                   const uint8_t *entropy, uint16_t len);

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
             uint8_t *dataOut);


/** spritz_hash_setup()
 * Setup the spritz hash state `spritz_ctx`.
 *
 * Parameter hash_ctx: The hash context (ctx).
 */
void
spritz_hash_setup(spritz_ctx *hash_ctx);

/** spritz_hash_update()
 * Add a message/data chunk `data` to hash.
 *
 * Parameter hash_ctx: The hash context (ctx).
 * Parameter data:     The data chunk to hash.
 * Parameter datalen:  Length of the data in bytes.
 */
void
spritz_hash_update(spritz_ctx *hash_ctx,
                   const uint8_t *data, uint16_t dataLen);

/** spritz_hash_final()
 * Output the hash digest.
 *
 * Parameter hash_ctx:  The hash context (ctx).
 * Parameter digest:    The digest (hash) output.
 * Parameter digestlen: Length of the digest in bytes.
 */
void
spritz_hash_final(spritz_ctx *hash_ctx,
                  uint8_t *digest, uint8_t digestLen);

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
            const uint8_t *data, uint16_t dataLen);


/** spritz_mac_setup()
 * Setup the spritz message authentication code (MAC) state `spritz_ctx`.
 *
 * Parameter mac_ctx: The message authentication code (MAC) context (ctx).
 * Parameter key:     The secret key.
 * Parameter keylen:  Length of the key in bytes.
 */
void
spritz_mac_setup(spritz_ctx *mac_ctx,
                 const uint8_t *key, uint16_t keyLen);

/** spritz_mac_update()
 * Add a message/data chunk to message authentication code (MAC).
 *
 * Parameter hash_ctx: The hash context (ctx).
 * Parameter msg:      The message chunk to be authenticated.
 * Parameter msglen:   Length of the message in bytes.
 */
void
spritz_mac_update(spritz_ctx *mac_ctx,
                  const uint8_t *msg, uint16_t msgLen);

/** spritz_mac_final()
 * Output the message authentication code (MAC) digest.
 *
 * Parameter mac_ctx:   The message authentication code (MAC) context (ctx).
 * Parameter digest:    Message authentication code (MAC) digest output.
 * Parameter digestlen: Length of the digest in bytes.
 */
void
spritz_mac_final(spritz_ctx *mac_ctx,
                 uint8_t *digest, uint8_t digestLen);

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
           const uint8_t *key, uint16_t keyLen);


#ifdef __cplusplus
}
#endif

#endif /* SpritzCipher.h */
