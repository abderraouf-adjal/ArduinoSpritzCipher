SpritzCipher
============

Spritz library for Arduino.
A spongy RC4-like stream cipher. This library contains cryptographically secure
pseudo-random bytes generator, Hash & MAC functions with configurable output length.

This library can be used to:
  * Encrypt data.
  * Generate random numbers.
  * Hash & authenticate data.

Home page: <https://github.com/abderraouf-adjal/ArduinoSpritzCipher>

Spritz paper: <https://people.csail.mit.edu/rivest/pubs/RS14.pdf>


Library content for user
========================

* Types
  spritz_t - Contain the state.

* Functions
  setup()   - To setup spritz state (spritz_t).
  setupIV() - Usable after setup() to add NONCE (Salt).
  spritz_rand_byte() - Return random byte (can be used to make a key) from spritz state (spritz_t).

  hash() - Cryptographic hash function.
  mac()  - Message Authentication Code (MAC) function.


Functions
=========

void setup(spritz_t *ctx,
           const uint8_t *key, uint8_t keyLen);
void setupIV(spritz_t *ctx,
             const uint8_t *nonce, uint8_t nonceLen);
uint8_t spritz_rand_byte(spritz_t *ctx);

void hash(uint8_t *digest, uint8_t digestLen,
          const uint8_t *data, unsigned int dataLen);
void mac(uint8_t *digest, uint8_t digestLen,
         const uint8_t *msg, unsigned int msgLen,
         const uint8_t *key, uint8_t keyLen);


Examples
========

* Hash data:
  ./examples/SpritzCipherHashTest/SpritzCipherHashTest.ino

* Generate random bytes:
  ./examples/SpritzCipherStreamTest/SpritzCipherStreamTest.ino


Installation Guide
==================

<https://www.arduino.cc/en/Guide/Libraries>


Reporting bugs
==============

Create an issue on GitHub:
<https://github.com/abderraouf-adjal/ArduinoSpritzCipher/issues>


Copyright
=========

Copyright (c) 2015 Abderraouf Adjal
License: The MIT License.
