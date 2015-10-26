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

#define SPRITZ_N 256

typedef struct
{
  uint8_t s[SPRITZ_N], i, j, k, z, a, w;
} spritz_t;


class SpritzCipher
{
  public:
    SpritzCipher();

    /* Setup spritz state (spritz_t) */
    void
    setup(spritz_t *ctx,
          const uint8_t *key, uint8_t keyLen);

    /* Use setupIV() *after* setup() to add NONCE (Salt) */
    void
    setupIV(spritz_t *ctx,
            const uint8_t *nonce, uint8_t nonceLen);

    /* Return random byte (can be used to make a key) from spritz state (spritz_t) */
    uint8_t
    spritz_rand_byte(spritz_t *ctx);

    /**
     * Cryptographic hash function
     * 
     * - digest: Hash output.
     * - digestLen: Set hash output size, Value (>=) 32 is recommended.
     * 
     * - data: Data to hash.
     * - dataLen: Data size.
     */
    void
    hash(uint8_t *digest, uint8_t digestLen,
         const uint8_t *data, unsigned int dataLen);

    /**
     * Message Authentication Code (MAC) function
     * 
     * - digest: MAC output.
     * - digestLen: Set MAC output size, Value (>=) 32 is recommended.
     * 
     * - msg: Message to be authenticated.
     * - msgLen: Message size.
     * 
     * - key: The secret key.
     * - keyLen: The secret key size.
     */
    void
    mac(uint8_t *digest, uint8_t digestLen,
        const uint8_t *msg, unsigned int msgLen,
        const uint8_t *key, uint8_t keyLen);

  private:
    void stateInit(spritz_t *ctx);
    void update(spritz_t *ctx);
    void whip(spritz_t *ctx);
    void crush(spritz_t *ctx);
    void shuffle(spritz_t *ctx);
    void absorbNibble(spritz_t *ctx, const uint8_t nibble);
    void absorb(spritz_t *ctx, const uint8_t octet);
    void absorbStop(spritz_t *ctx);
    uint8_t output(spritz_t *ctx);
    uint8_t drip(spritz_t *ctx);
    void squeeze(spritz_t *ctx, uint8_t *out, uint8_t len);
};


#endif /* SpritzCipher.h */
