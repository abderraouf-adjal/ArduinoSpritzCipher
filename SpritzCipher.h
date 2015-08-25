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

#ifndef _SPRITZCIPHER_H
#define _SPRITZCIPHER_H


#define SPRITZ_N 256

typedef struct
{
  unsigned char s[SPRITZ_N];
  unsigned char i, j, k, z, a, w;
} spritz_t;

class SpritzCipher
{
  public:
    SpritzCipher();

    void setup(spritz_t *ctx,
               const unsigned char *key, unsigned int keylen);
    void setupIV(spritz_t *ctx,
                 const unsigned char *nonce, unsigned int noncelen);
    unsigned char stream(spritz_t *ctx);

    void hash(unsigned char *digest, unsigned char digestlen,
              const unsigned char *data, unsigned int datalen);
    void mac(unsigned char *digest, unsigned char digestlen,
             const unsigned char *msg, unsigned int msglen,
             const unsigned char *key, unsigned int keylen);

  private:
    void swap(unsigned char *a, unsigned char *b);
    void stateInit(spritz_t *ctx);
    void update(spritz_t *ctx);
    void whip(spritz_t *ctx);
    void crush(spritz_t *ctx);
    void shuffle(spritz_t *ctx);
    void absorbNibble(spritz_t *ctx, const unsigned char nibble);
    void absorb(spritz_t *ctx, const unsigned char byte);
    void absorbBytes(spritz_t *ctx, const unsigned char *buf, unsigned int len);
    void absorbStop(spritz_t *ctx);
    unsigned char output(spritz_t *ctx);
    unsigned char drip(spritz_t *ctx);
    void squeeze(spritz_t *ctx, unsigned char *out, unsigned int len);
};


#endif /* SpritzCipher.h */
