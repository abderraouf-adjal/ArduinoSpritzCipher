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


#include <stdint.h> /* For uint8_t & uint16_t */


/** \def SPRITZ_TIMING_SAFE_CRUSH
 * if defined, the equal time crush() will be used.
 * this may not be useful in some compilers with optimization (except GCC and Clang)
 */
#define SPRITZ_TIMING_SAFE_CRUSH

/** \def SPRITZ_WIPE_TRACES
 * if defined, sensitive data (like spritz_ctx) when they are
 * no longer needed in functions such as hash and mac will be wiped
 * functions that SPRITZ_WIPE_TRACES is involved with:
 * {spritz_hash, spritz_mac}
 */
#define SPRITZ_WIPE_TRACES

/** \def SPRITZ_WIPE_TRACES_PARANOID
 * if defined, the library functions internal variables will be wiped if it contains a bit or more
 * of spritz state such as temporary variables in a swap function or an user data
 * be wiped when they are no longer needed. Variables that contain data length will not be wiped.
 * if defined, then SPRITZ_WIPE_TRACES and SPRITZ_TIMING_SAFE_CRUSH will be assumed and defined automatically.
 */
#define SPRITZ_WIPE_TRACES_PARANOID

#ifdef SPRITZ_WIPE_TRACES_PARANOID
# ifndef SPRITZ_TIMING_SAFE_CRUSH
#  define SPRITZ_TIMING_SAFE_CRUSH
# endif
# ifndef SPRITZ_WIPE_TRACES
#  define SPRITZ_WIPE_TRACES
# endif
#endif

/** \def SPRITZ_N
 * present the value of N in this spritz implementation, do not change SPRITZ_N value
 */
#define SPRITZ_N 256

/* Semantic Versioning of this library */
#define SPRITZ_LIBRARY_VERSION_STRING "0.9.3"
#define SPRITZ_LIBRARY_VERSION_MAJOR 0
#define SPRITZ_LIBRARY_VERSION_MINOR 9
#define SPRITZ_LIBRARY_VERSION_PATCH 3


/** \typedef spritz_ctx
 * \brief the context (contains the state), holds indices and s-box.
 */
typedef struct
{
  uint8_t s[SPRITZ_N], i, j, k, z, a, w;
#ifdef SPRITZ_WIPE_TRACES_PARANOID
  /* tmp1: spritz_state_s_swap(), safe timing crush();
   * tmp2: safe timing crush() */
  uint8_t tmp1, tmp2;
#endif
} spritz_ctx;

/** \fn uint8_t spritz_compare(const uint8_t *data_a, const uint8_t *data_b, uint16_t len)
 * \brief timing-safe equality comparison for `data_a` and `data_b`. this function can be used to compare the password's hash safely.
 * \param data_a data a to compare with b
 * \param data_b data b to compare with a
 * \param len length of the array in bytes
 * \return equality result, return zero (0x00) if `data_a` equals `data_b` or if `len` is zero, and a non-zero value if they are not equal.
 */
uint8_t
spritz_compare(const uint8_t *data_a, const uint8_t *data_b, uint16_t len);

/** \fn void spritz_memzero(uint8_t *buf, uint16_t len)
 * \brief wipe `buf` data by replacing it with zeros (0x00)
 * \param buf data to replace it with zeros (0x00)
 * \param len length of array in bytes
 */
void
spritz_memzero(uint8_t *buf, uint16_t len);

/** \fn void spritz_state_memzero(spritz_ctx *ctx)
 * \brief wipe `spritz_ctx`'s data by replacing its data with zeros (0x00)
 * \param ctx the context
 */
void
spritz_state_memzero(spritz_ctx *ctx);


/** \fn void spritz_setup(spritz_ctx *ctx, const uint8_t *key, uint8_t keylen)
 * \brief setup the spritz state `spritz_ctx` with a key
 * \param ctx the context
 * \param key the key
 * \param keylen length of the key in bytes
 */
void
spritz_setup(spritz_ctx *ctx,
             const uint8_t *key, uint8_t keyLen);

/** \fn void spritz_setup_withiv(spritz_ctx *ctx, const uint8_t *key, uint8_t keylen, const uint8_t *nonce, uint8_t noncelen)
 * \brief setup the spritz state `spritz_ctx` with a key and nonce/salt/iv
 * \param ctx the context
 * \param key the key
 * \param keylen length of the key in bytes
 * \param nonce the nonce (salt)
 * \param noncelen length of the nonce in bytes
 */
void
spritz_setup_withIV(spritz_ctx *ctx,
                    const uint8_t *key, uint8_t keyLen,
                    const uint8_t *nonce, uint8_t nonceLen);

/** \fn uint8_t spritz_random_byte(spritz_ctx *ctx)
 * \brief generates a random byte from the spritz state `spritz_ctx`. usable after spritz_setup() or spritz_setup_withiv()
 * \param ctx the context
 * \return byte of keystream
 */
uint8_t
spritz_random_byte(spritz_ctx *ctx);

/** \fn uint32_t spritz_random_u32(spritz_ctx *ctx)
 * \brief generates a random 32-bit (4 bytes) from the spritz state `spritz_ctx`. usable after spritz_setup() or spritz_setup_withiv()
 * \param ctx the context
 * \return 32-bit (4 bytes) of keystream
 */
uint32_t
spritz_random_u32(spritz_ctx *ctx);

/** \fn uint32_t spritz_random_uniform(spritz_ctx *ctx, uint32_t upper_bound)
 * \brief calculate a uniformly distributed random number less than upper_bound avoiding modulo bias. usable after spritz_setup() or spritz_setup_withiv()
 * \param ctx the context
 * \param upper_bound the roof, (upper_bound - 1) is the largest random number that can be returned
 * \return random number less than upper_bound, 0 if upper_bound<2
 */
uint32_t
spritz_random_uniform(spritz_ctx *ctx, uint32_t upper_bound);

/** \fn void spritz_add_entropy(spritz_ctx *ctx, const uint8_t *entropy, uint16_t len)
 * \brief add entropy to the spritz state `spritz_ctx` using absorb(). usable after spritz_setup() or spritz_setup_withiv().
 * \param ctx the context
 * \param entropy the entropy array
 * \param len length of the entropy array in bytes
 */
void
spritz_add_entropy(spritz_ctx *ctx,
                   const uint8_t *entropy, uint16_t len);

/** \fn void spritz_crypt(spritz_ctx *ctx, uint16_t datalen, const uint8_t *data, uint8_t *dataout)
 * \brief encrypt or decrypt data chunk by xor-ing it with the spritz keystream. usable after spritz_setup() or spritz_setup_withiv()
 * \param ctx the context
 * \param data the data to encrypt or decrypt
 * \param datalen length of the data in bytes
 * \param dataout the output
 */
void
spritz_crypt(spritz_ctx *ctx,
             const uint8_t *data, uint16_t dataLen,
             uint8_t *dataOut);


/** \fn void spritz_hash_setup(spritz_ctx *hash_ctx)
 * \brief setup the spritz hash state `spritz_ctx`
 * \param hash_ctx the hash context (ctx)
 */
void
spritz_hash_setup(spritz_ctx *hash_ctx);

/** \fn void spritz_hash_update(spritz_ctx *hash_ctx, const uint8_t *data, uint16_t datalen)
 * \brief add a message/data chunk `data` to hash.
 * \param hash_ctx the hash context (ctx)
 * \param data the data chunk to hash
 * \param datalen length of the data in bytes
 */
void
spritz_hash_update(spritz_ctx *hash_ctx,
                   const uint8_t *data, uint16_t dataLen);

/** \fn void spritz_hash_final(spritz_ctx *hash_ctx, uint8_t *digest, uint8_t digestlen)
 * \brief output the hash digest
 * \param hash_ctx the hash context (ctx)
 * \param digest the digest (hash) output
 * \param digestlen length of the digest in bytes
 */
void
spritz_hash_final(spritz_ctx *hash_ctx,
                  uint8_t *digest, uint8_t digestLen);

/** \fn void spritz_hash(uint8_t *digest, uint8_t digestlen, const uint8_t *data, uint16_t datalen)
 * \brief cryptographic hash function
 * \param digest the digest (hash) output
 * \param digestlen length of the digest in bytes
 * \param data the data to hash
 * \param datalen length of the data in bytes
 */
void
spritz_hash(uint8_t *digest, uint8_t digestLen,
            const uint8_t *data, uint16_t dataLen);


/** \fn void spritz_mac_setup(spritz_ctx *mac_ctx, const uint8_t *key, uint16_t keylen)
 * \brief setup the spritz message authentication code (mac) state `spritz_ctx`
 * \param mac_ctx the message authentication code (mac) context (ctx)
 * \param key the secret key
 * \param keylen length of the key in bytes
 */
void
spritz_mac_setup(spritz_ctx *mac_ctx,
                 const uint8_t *key, uint16_t keyLen);

/** \fn void spritz_mac_update(spritz_ctx *mac_ctx, const uint8_t *msg, uint16_t msglen)
 * \brief add a message/data chunk to message authentication code (mac)
 * \param hash_ctx the hash context (ctx)
 * \param msg the message chunk to be authenticated
 * \param msglen length of the message in bytes
 */
void
spritz_mac_update(spritz_ctx *mac_ctx,
                  const uint8_t *msg, uint16_t msgLen);

/** \fn void spritz_mac_final(spritz_ctx *mac_ctx, uint8_t *digest, uint8_t digestlen)
 * \brief output the message authentication code (mac) digest
 * \param mac_ctx the message authentication code (mac) context (ctx)
 * \param digest message authentication code (mac) digest output.
 * \param digestlen length of the digest in bytes
 */
void
spritz_mac_final(spritz_ctx *mac_ctx,
                 uint8_t *digest, uint8_t digestLen);

/** \fn void spritz_mac(uint8_t *digest, uint8_t digestlen, const uint8_t *msg, uint16_t msglen, const uint8_t *key, uint16_t keylen)
 * \brief message authentication code (mac) function
 * \param digest message authentication code (mac) digest output.
 * \param digestlen length of the digest in bytes
 * \param msg the message to be authenticated
 * \param msglen length of the message in bytes
 * \param key the secret key
 * \param keylen length of the key in bytes
 */
void
spritz_mac(uint8_t *digest, uint8_t digestLen,
           const uint8_t *msg, uint16_t msgLen,
           const uint8_t *key, uint16_t keyLen);


#ifdef __cplusplus
}
#endif

#endif /* SpritzCipher.h */
