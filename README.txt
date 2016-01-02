Spritz library for Arduino
==========================

Spritz:
  A spongy RC4-like stream cipher. This library contains
  secure random bytes generator, Flexible cryptographic hash function
  and message authentication code (MAC).

This C spritz library can be used to:
  * Hash data.
  * Data encryption.
  * Authenticated encryption.
  * Generate random numbers from seed.

Spritz paper: <https://people.csail.mit.edu/rivest/pubs/RS14.pdf>
This library on GitHub: <https://github.com/abderraouf-adjal/ArduinoSpritzCipher>


Library content for user
========================

See the source code and ".h" files for the details.

# Constants:
============
SAFE_TIMING_CRUSH
  If defined, Equal time crush() will be used.

WIPE_AFTER_USAGE
  If defined, Sensitive data (like spritz_ctx) will be wiped when they are
  no longer needed in the functions:
   {spritz_hash, spritz_mac, spritz_hash_final, spritz_mac_final}.

SPRITZ_N 256
  Present the value of N in this spritz implementation.

SPRITZ_LIBRARY_VERSION_STRING "0.4.0"
  Present the version of this spritz library (MAJOR . MINOR . PATCH)
  using Semantic Versioning <semver.org>.
SPRITZ_LIBRARY_VERSION_MAJOR 0
  Present the MAJOR version.
SPRITZ_LIBRARY_VERSION_MINOR 4
  Present the MINOR version.
SPRITZ_LIBRARY_VERSION_PATCH 1
  Present the PATCH version.

# Types:
========
spritz_ctx
  The context/ctx (contain the state), The state consists of byte registers
  {i, j, k, z, w, a}, And an array {s} containing a permutation
  of {0, 1, ... , SPRITZ_N-1}.

# Functions:
============
uint8_t spritz_is_equal(const uint8_t *data_a, const uint8_t *data_b, uint16_t len)
  Timing-safe comparison for "data_a" and "data_b" equality.
  This function can be used to compare passwords hash safely.
  Return zero (0x00) if "data_a" equal "data_b", non-zero value if they are not.
                ------------------------

void spritz_setup(spritz_ctx *ctx,
                  const uint8_t *key, uint8_t keyLen)
  Setup spritz state (spritz_ctx) with a key.

void spritz_setupWithIV(spritz_ctx *ctx,
                        const uint8_t *key, uint8_t keyLen,
                        const uint8_t *nonce, uint8_t nonceLen)
  Setup spritz state (spritz_ctx) with a key and nonce/Salt/IV.

uint8_t spritz_random_byte(spritz_ctx *ctx)
  Generates a byte of keystream from spritz state (spritz_ctx).
  Can be used to make a random key.
  spritz_random_byte() usable after spritz_setup() or spritz_setupWithIV().

void spritz_add_entropy(spritz_ctx *ctx,
                        const uint8_t *entropy, uint16_t len)
  Add entropy to spritz state (spritz_ctx) using absorb().
  spritz_add_entropy() usable after spritz_setup() or spritz_setupWithIV().

void spritz_crypt(spritz_ctx *ctx,
                  const uint8_t *data, uint16_t dataLen,
                  uint8_t *dataOut)
  Encrypt or decrypt data chunk by XOR-ing it with spritz keystream.
  spritz_crypt() usable after spritz_setup() or spritz_setupWithIV().

void spritz_wipe(spritz_ctx *ctx)
  Wipe spritz context data (spritz_ctx).
                ------------------------

void spritz_hash(uint8_t *digest, uint8_t digestLen,
                 const uint8_t *data, uint16_t dataLen)
  Spritz cryptographic hash function.

void spritz_mac(uint8_t *digest, uint8_t digestLen,
                const uint8_t *msg, uint16_t msgLen,
                const uint8_t *key, uint16_t keyLen)
  Spritz Message Authentication Code (MAC) function.
                ------------------------

void spritz_hash_setup(spritz_ctx *hash_ctx)
  Setup spritz hash state.

void spritz_hash_update(spritz_ctx *hash_ctx,
                        const uint8_t *data, uint16_t dataLen)
  Add data chunk to hash.

void spritz_hash_final(spritz_ctx *hash_ctx,
                       uint8_t *digest, uint8_t digestLen)
  Output hash digest.
                ------------------------

void spritz_mac_setup(spritz_ctx *mac_ctx,
                      const uint8_t *key, uint16_t keyLen)
  Setup spritz MAC state.

void spritz_mac_update(spritz_ctx *mac_ctx,
                       const uint8_t *msg, uint16_t msgLen)
  Add message/data chunk to MAC.

void spritz_mac_final(spritz_ctx *mac_ctx,
                      uint8_t *digest, uint8_t digestLen)
  Output MAC digest.


Examples
========

* Generate random bytes (Spritz stream test):
  ./examples/SpritzStreamTest/SpritzStreamTest.ino

* Test the library encryption/decryption function:
  ./examples/SpritzCryptTest/SpritzCryptTest.ino

* Hash data:
  ./examples/SpritzHashTest/SpritzHashTest.ino

* Hash data chunk by chunk:
  ./examples/SpritzHashChunksTest/SpritzHashChunksTest.ino

* MAC test:
  ./examples/SpritzMACTest/SpritzMACTest.ino


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
