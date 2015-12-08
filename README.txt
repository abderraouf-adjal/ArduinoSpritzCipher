SpritzCipher
============

Spritz library for Arduino.
A spongy RC4-like stream cipher. This library contains secure random bytes generator,
Flexible cryptographic hash function & message authentication code (MAC).

This library can be used to:
  * Hash data.
  * Data encryption.
  * Authenticated encryption.
  * Generate random numbers from seed.

Home page on GitHub: <https://github.com/abderraouf-adjal/ArduinoSpritzCipher>

Spritz paper: <https://people.csail.mit.edu/rivest/pubs/RS14.pdf>


Library content for user
========================

See <SpritzCipher.h> for the details.

* Types:
  spritz_ctx
    # The context/ctx (contain the state), holds indices and S-Box.

* Functions:
  void spritz_wipe_ctx(spritz_ctx *ctx)
    # Wipe spritz context data.
                ========================

  void spritz_setup(spritz_ctx *ctx,
                    const uint8_t *key, uint8_t keyLen)
    # Setup spritz state (spritz_ctx) with a key.

  void spritz_setupIV(spritz_ctx *ctx,
                      const uint8_t *key, uint8_t keyLen,
                      const uint8_t *nonce, uint8_t nonceLen)
    # Setup spritz state with a key and nonce (Salt).

  uint8_t spritz_rand_byte(spritz_ctx *ctx)
    # Generates a byte of keystream from spritz state (spritz_ctx).
                ========================

  void spritz_hash(uint8_t *digest, uint8_t digestLen,
                   const uint8_t *data, uint16_t dataLen)
    # Spritz cryptographic hash function.

  void spritz_mac(uint8_t *digest, uint8_t digestLen,
                  const uint8_t *msg, uint16_t msgLen,
                  const uint8_t *key, uint16_t keyLen)
    # Spritz Message Authentication Code (MAC) function.
                ========================

  void spritz_hash_setup(spritz_ctx *hash_ctx)
    # Setup spritz hash state.

  void spritz_hash_update(spritz_ctx *hash_ctx,
                          const uint8_t *data, uint16_t dataLen)
    # Add data chunk to hash.

  void spritz_hash_final(spritz_ctx *hash_ctx,
                         uint8_t *digest, uint8_t digestLen)
    # Output hash digest.
                ========================

  void spritz_mac_setup(spritz_ctx *mac_ctx,
                        const uint8_t *key, uint16_t keyLen)
    # Setup spritz MAC state.

  void spritz_mac_update(spritz_ctx *mac_ctx,
                         const uint8_t *msg, uint16_t msgLen)
    # Add message/data chunk to MAC.

  void spritz_mac_final(spritz_ctx *mac_ctx,
                        uint8_t *digest, uint8_t digestLen)
    # Output MAC digest.


Examples
========

* Generate random bytes (Spritz stream test):
  ./examples/SpritzStreamTest/SpritzStreamTest.ino

* Hash data:
  ./examples/SpritzHashTest/SpritzHashTest.ino

* Hash data chunk by chunk:
  ./examples/SpritzHashChunksTest/SpritzHashChunksTest.ino


Installation Guide
==================

<https://www.arduino.cc/en/Guide/Libraries>


Reporting bugs
==============

Create an issue on GitHub:
<https://github.com/abderraouf-adjal/ArduinoSpritzCipher/issues>


Keywords
========

spritz cipher implementation, spritz implementation, implementation of spritz
spritz stream cipher, spritz encryption, spritz algorithm.


Copyright
=========

Copyright (c) 2015 Abderraouf Adjal

License: The MIT License.
