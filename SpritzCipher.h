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


#ifndef _SPRITZCIPHER_H
#define _SPRITZCIPHER_H


#include <stdint.h> /* For uint8_t */


/** \def SAFE_TIMING_CRUSH
 * do safe timing swap in crush(), Because of the compiler optimization this may be not useful
 */
#define SAFE_TIMING_CRUSH

/** \def WIPE_AFTER_USAGE
 * wipe sensitive buffers and variables in functions when they are no longer needed
 */
#define WIPE_AFTER_USAGE

#define SPRITZ_N 256


/** \typedef spritz_ctx
 * \brief the context (contain the state), holds indices and S-Box.
 */
typedef struct
{
  uint8_t s[SPRITZ_N], i, j, k, z, a, w;
} spritz_ctx;


class SpritzCipher
{
  public:
    SpritzCipher();

    /** \fn void wipe_spritz_ctx(spritz_ctx *ctx)
     * \brief Wipe spritz context (spritz_ctx) data
     * \param ctx the context
     */
    void
    wipe_spritz_ctx(spritz_ctx *ctx);


    /** \fn void setup(spritz_ctx *ctx, const uint8_t *key, uint8_t keyLen)
     * \brief setup spritz state (spritz_ctx) with a key
     * \param ctx the context
     * \param key the key
     * \param keyLen length of the key in bytes
     */
    void
    setup(spritz_ctx *ctx,
          const uint8_t *key, uint8_t keyLen);

    /** \fn void setupIV(spritz_ctx *ctx, const uint8_t *key, uint8_t keyLen, const uint8_t *nonce, uint8_t nonceLen)
     * \brief setup spritz state (spritz_ctx) with a key and nonce (Salt)
     * \param ctx the context
     * \param key the key
     * \param keyLen length of the key in bytes
     * \param nonce the nonce (salt)
     * \param nonceLen length of the nonce in bytes
     */
    void
    setupIV(spritz_ctx *ctx,
            const uint8_t *key, uint8_t keyLen,
            const uint8_t *nonce, uint8_t nonceLen);

    /** \fn uint8_t spritz_rand_byte(spritz_ctx *ctx)
     * \brief generates a byte of keystream from spritz state (spritz_ctx)
     * \param ctx the context
     * \return byte of keystream
     */
    uint8_t
    spritz_rand_byte(spritz_ctx *ctx);



    /** \fn void hash_setup(spritz_ctx *hash_ctx)
     * \brief Setup spritz hash state (spritz_ctx)
     * \param hash_ctx the hash context (ctx)
     */
    void
    hash_setup(spritz_ctx *hash_ctx);

    /** \fn void hash_update(spritz_ctx *hash_ctx, const uint8_t *data, unsigned int dataLen)
     * \brief Add data chunk to hash
     * \param hash_ctx the hash context (ctx)
     * \param data the data chunk to hash
     * \param dataLen length of the data in bytes
     */
    void
    hash_update(spritz_ctx *hash_ctx,
                const uint8_t *data, unsigned int dataLen);

    /** \fn void hash_final(spritz_ctx *hash_ctx, uint8_t *digest, uint8_t digestLen)
     * \brief Output hash digest
     * \param hash_ctx the hash context (ctx)
     * \param digest the digest (Hash) output
     * \param digestLen length of the digest in bytes
     */
    void
    hash_final(spritz_ctx *hash_ctx,
               uint8_t *digest, uint8_t digestLen);

    /** \fn void hash(uint8_t *digest, uint8_t digestLen, const uint8_t *data, unsigned int dataLen)
     * \brief cryptographic hash function
     * \param digest the digest (Hash) output
     * \param digestLen length of the digest in bytes
     * \param data the data to hash
     * \param dataLen length of the data in bytes
     */
    void
    hash(uint8_t *digest, uint8_t digestLen,
         const uint8_t *data, unsigned int dataLen);



    /** \fn void mac_setup(spritz_ctx *mac_ctx, const uint8_t *key, unsigned int keyLen)
     * \brief Setup spritz MAC state (spritz_ctx)
     * \param mac_ctx the MAC context (ctx)
     * \param key the secret key
     * \param keyLen length of the key in bytes
     */
    void
    mac_setup(spritz_ctx *mac_ctx,
                            const uint8_t *key, unsigned int keyLen);

    /** \fn void mac_update(spritz_ctx *mac_ctx, const uint8_t *msg, unsigned int msgLen)
     * \brief Add message/data chunk to MAC
     * \param hash_ctx the hash context (ctx)
     * \param msg the message chunk to be authenticated
     * \param msgLen length of the message in bytes
     */
    void
    mac_update(spritz_ctx *mac_ctx,
                             const uint8_t *msg, unsigned int msgLen);

    /** \fn void mac_final(spritz_ctx *mac_ctx, uint8_t *digest, uint8_t digestLen)
     * \brief Output MAC digest
     * \param mac_ctx the MAC context (ctx)
     * \param digest MAC digest output.
     * \param digestLen length of the digest in bytes
     */
    void
    mac_final(spritz_ctx *mac_ctx,
                            uint8_t *digest, uint8_t digestLen);

    /** \fn void mac(uint8_t *digest, uint8_t digestLen, const uint8_t *msg, unsigned int msgLen, const uint8_t *key, unsigned int keyLen)
     * \brief message authentication code (MAC) function
     * \param digest MAC digest output.
     * \param digestLen length of the digest in bytes
     * \param msg the message to be authenticated
     * \param msgLen length of the message in bytes
     * \param key the secret key
     * \param keyLen length of the key in bytes
     */
    void
    mac(uint8_t *digest, uint8_t digestLen,
        const uint8_t *msg, unsigned int msgLen,
        const uint8_t *key, unsigned int keyLen);


  private:
    void stateInit(spritz_ctx *ctx);
    void update(spritz_ctx *ctx);
    void whip(spritz_ctx *ctx);
    void crush(spritz_ctx *ctx);
    void shuffle(spritz_ctx *ctx);
    void absorbNibble(spritz_ctx *ctx, const uint8_t nibble);
    void absorb(spritz_ctx *ctx, const uint8_t octet);
    void absorbBytes(spritz_ctx *ctx, const uint8_t *buf, unsigned int len);
    void absorbStop(spritz_ctx *ctx);
    uint8_t output(spritz_ctx *ctx);
    uint8_t drip(spritz_ctx *ctx);
    void squeeze(spritz_ctx *ctx, uint8_t *out, uint8_t len);
};


#endif /* SpritzCipher.h */
