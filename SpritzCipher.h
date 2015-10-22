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

#include <Arduino.h>

#define SPRITZ_N 256


typedef struct
{
  byte s[SPRITZ_N], i, j, k, z, a, w;
} spritz_t;


class SpritzCipher
{
  public:
    SpritzCipher();

    /* Setup spritz state (spritz_t) */
    void setup(spritz_t *ctx,
               const byte *key, unsigned int keyLen);

    /* Use setupIV() *after* setup() to add NONCE (Salt) */
    void setupIV(spritz_t *ctx,
                 const byte *nonce, unsigned int nonceLen);

    /* Return random byte that can be used as a key */
    byte stream(spritz_t *ctx);

    /**
     * Cryptographic hash function
     * 
     * - digest: Hash output.
     * - digestLen: Set hash output size, Value (>=) 32 is recommended.
     * 
     * - data: Data to hash.
     * - dataLen: Data size.
     */
    void hash(byte *digest, byte digestLen,
              const byte *data, unsigned int dataLen);
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
    void mac(byte *digest, byte digestLen,
             const byte *msg, unsigned int msgLen,
             const byte *key, unsigned int keyLen);


  private:
    void swap(byte *a, byte *b);
    void stateInit(spritz_t *ctx);
    void update(spritz_t *ctx);
    void whip(spritz_t *ctx);
    void crush(spritz_t *ctx);
    void shuffle(spritz_t *ctx);
    void absorbNibble(spritz_t *ctx, const byte nibble);
    void absorb(spritz_t *ctx, const byte octet);
    void absorbBytes(spritz_t *ctx, const byte *buf, unsigned int len);
    void absorbStop(spritz_t *ctx);
    byte output(spritz_t *ctx);
    byte drip(spritz_t *ctx);
    void squeeze(spritz_t *ctx, byte *out, byte len);
};


#endif /* SpritzCipher.h */
