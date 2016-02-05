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
 * if defined, equal time crush() will be used.
 * this may not be useful in some compilers with optimization (except GCC and Clang)
 */
#define SPRITZ_TIMING_SAFE_CRUSH

/** \def SPRITZ_WIPE_TRACES
 * if defined, Sensitive data (like spritz_ctx) when they are
 * no longer needed in functions such as hash and mac will be wiped
 * functions that SPRITZ_WIPE_TRACES is involved with:
 * {spritz_hash, spritz_mac}
 */
#define SPRITZ_WIPE_TRACES

/** \def SPRITZ_WIPE_TRACES_PARANOID
 * if defined, library functions internal variables will be wiped if it contains a bit or more
 * of spritz state such as temporary variables in a swap function or an user data
 * be wiped when they are no longer needed. Variables that contain data length will not be wiped.
 * if defined, SPRITZ_WIPE_TRACES and SPRITZ_TIMING_SAFE_CRUSH will be defined automatically
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
#define SPRITZ_LIBRARY_VERSION_STRING "0.9.1"
#define SPRITZ_LIBRARY_VERSION_MAJOR 0
#define SPRITZ_LIBRARY_VERSION_MINOR 9
#define SPRITZ_LIBRARY_VERSION_PATCH 1


/** \typedef spritz_ctx
 * \brief the context (contain the state), holds indices and S-Box.
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
 * \brief Timing-safe equality comparison for "data_a" and "data_b"
 * \param data_a data A to compare with B
 * \param data_b data B to compare with A
 * \param len length of the array in bytes
 * \return equality result, zero (0x00) if "data_a" equal "data_b" or "len" is zero, non-zero value if they are not equal
 */
uint8_t
spritz_compare(const uint8_t *data_a, const uint8_t *data_b, uint16_t len);

/** \fn void spritz_memzero(uint8_t *buf, uint16_t len)
 * \brief wipe "buf" data by replacing it with zeros (0x00)
 * \param buf data to replace it with zeros (0x00)
 * \param len length of array in bytes
 */
void
spritz_memzero(uint8_t *buf, uint16_t len);

/** \fn void spritz_state_memzero(spritz_ctx *ctx)
 * \brief wipe spritz_ctx data by replacing its data with zeros (0x00)
 * \param ctx the context
 */
void
spritz_state_memzero(spritz_ctx *ctx);


/** \fn void spritz_setup(spritz_ctx *ctx, const uint8_t *key, uint8_t keyLen)
 * \brief setup spritz state (spritz_ctx) with a key
 * \param ctx the context
 * \param key the key
 * \param keyLen length of the key in bytes
 */
void
spritz_setup(spritz_ctx *ctx,
             const uint8_t *key, uint8_t keyLen);

/** \fn void spritz_setup_withIV(spritz_ctx *ctx, const uint8_t *key, uint8_t keyLen, const uint8_t *nonce, uint8_t nonceLen)
 * \brief setup spritz state (spritz_ctx) with a key and nonce/Salt/IV
 * \param ctx the context
 * \param key the key
 * \param keyLen length of the key in bytes
 * \param nonce the nonce (salt)
 * \param nonceLen length of the nonce in bytes
 */
void
spritz_setup_withIV(spritz_ctx *ctx,
                   const uint8_t *key, uint8_t keyLen,
                   const uint8_t *nonce, uint8_t nonceLen);

/** \fn uint8_t spritz_random_byte(spritz_ctx *ctx)
 * \brief generates a random byte of keystream from spritz state (spritz_ctx). Usable after spritz_setup() or spritz_setup_withIV()
 * \param ctx the context
 * \return byte of keystream
 */
uint8_t
spritz_random_byte(spritz_ctx *ctx);

/** \fn uint32_t spritz_random_u32(spritz_ctx *ctx)
 * \brief generates a random 32-bit (4 bytes) of keystream from spritz state (spritz_ctx). Usable after spritz_setup() or spritz_setup_withIV()
 * \param ctx the context
 * \return 32-bit (4 bytes) of keystream
 */
uint32_t
spritz_random_u32(spritz_ctx *ctx);

/** \fn uint32_t spritz_random_uniform(spritz_ctx *ctx, uint32_t upper_bound)
 * \brief calculate a uniformly distributed random number less than upper_bound avoiding modulo bias. Usable after spritz_setup() or spritz_setup_withIV()
 * \param ctx the context
 * \param upper_bound The roof, (upper_bound - 1) is the largest random number that can be returned
 * \return random number less than upper_bound, 0 if upper_bound<2
 */
uint32_t
spritz_random_uniform(spritz_ctx *ctx, uint32_t upper_bound);

/** \fn void spritz_add_entropy(spritz_ctx *ctx, const uint8_t *entropy, uint16_t len)
 * \brief Add entropy to spritz state (spritz_ctx) using absorb(). Usable after spritz_setup() or spritz_setup_withIV().
 * \param ctx the context
 * \param entropy the entropy array
 * \param len length of the entropy array in bytes
 */
void
spritz_add_entropy(spritz_ctx *ctx,
                   const uint8_t *entropy, uint16_t len);

/** \fn void spritz_crypt(spritz_ctx *ctx, uint16_t dataLen, const uint8_t *data, uint8_t *dataOut)
 * \brief encrypt or decrypt data chunk by XOR-ing it with spritz keystream. Usable after spritz_setup() or spritz_setup_withIV()
 * \param ctx the context
 * \param data the data to encrypt or decrypt
 * \param dataLen length of the data in bytes
 * \param dataOut the output
 */
void
spritz_crypt(spritz_ctx *ctx,
             const uint8_t *data, uint16_t dataLen,
             uint8_t *dataOut);


/** \fn void spritz_hash_setup(spritz_ctx *hash_ctx)
 * \brief Setup spritz hash state (spritz_ctx)
 * \param hash_ctx the hash context (ctx)
 */
void
spritz_hash_setup(spritz_ctx *hash_ctx);

/** \fn void spritz_hash_update(spritz_ctx *hash_ctx, const uint8_t *data, uint16_t dataLen)
 * \brief Add data chunk to hash
 * \param hash_ctx the hash context (ctx)
 * \param data the data chunk to hash
 * \param dataLen length of the data in bytes
 */
void
spritz_hash_update(spritz_ctx *hash_ctx,
                   const uint8_t *data, uint16_t dataLen);

/** \fn void spritz_hash_final(spritz_ctx *hash_ctx, uint8_t *digest, uint8_t digestLen)
 * \brief Output hash digest
 * \param hash_ctx the hash context (ctx)
 * \param digest the digest (Hash) output
 * \param digestLen length of the digest in bytes
 */
void
spritz_hash_final(spritz_ctx *hash_ctx,
                  uint8_t *digest, uint8_t digestLen);

/** \fn void spritz_hash(uint8_t *digest, uint8_t digestLen, const uint8_t *data, uint16_t dataLen)
 * \brief cryptographic hash function
 * \param digest the digest (Hash) output
 * \param digestLen length of the digest in bytes
 * \param data the data to hash
 * \param dataLen length of the data in bytes
 */
void
spritz_hash(uint8_t *digest, uint8_t digestLen,
            const uint8_t *data, uint16_t dataLen);


/** \fn void spritz_mac_setup(spritz_ctx *mac_ctx, const uint8_t *key, uint16_t keyLen)
 * \brief Setup spritz MAC state (spritz_ctx)
 * \param mac_ctx the MAC context (ctx)
 * \param key the secret key
 * \param keyLen length of the key in bytes
 */
void
spritz_mac_setup(spritz_ctx *mac_ctx,
                 const uint8_t *key, uint16_t keyLen);

/** \fn void spritz_mac_update(spritz_ctx *mac_ctx, const uint8_t *msg, uint16_t msgLen)
 * \brief Add message/data chunk to MAC
 * \param hash_ctx the hash context (ctx)
 * \param msg the message chunk to be authenticated
 * \param msgLen length of the message in bytes
 */
void
spritz_mac_update(spritz_ctx *mac_ctx,
                  const uint8_t *msg, uint16_t msgLen);

/** \fn void spritz_mac_final(spritz_ctx *mac_ctx, uint8_t *digest, uint8_t digestLen)
 * \brief Output MAC digest
 * \param mac_ctx the MAC context (ctx)
 * \param digest MAC digest output.
 * \param digestLen length of the digest in bytes
 */
void
spritz_mac_final(spritz_ctx *mac_ctx,
                 uint8_t *digest, uint8_t digestLen);

/** \fn void spritz_mac(uint8_t *digest, uint8_t digestLen, const uint8_t *msg, uint16_t msgLen, const uint8_t *key, uint16_t keyLen)
 * \brief message authentication code (MAC) function
 * \param digest MAC digest output.
 * \param digestLen length of the digest in bytes
 * \param msg the message to be authenticated
 * \param msgLen length of the message in bytes
 * \param key the secret key
 * \param keyLen length of the key in bytes
 */
void
spritz_mac(uint8_t *digest, uint8_t digestLen,
           const uint8_t *msg, uint16_t msgLen,
           const uint8_t *key, uint16_t keyLen);


#ifdef __cplusplus
}
#endif

#endif /* SpritzCipher.h */
