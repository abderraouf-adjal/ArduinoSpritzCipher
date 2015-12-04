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
    The context/ctx (contain the state), holds indices and S-Box.

* Functions:
  spritz_wipe_ctx(spritz_ctx ctx):
    Wipe spritz context data.

  spritz_setup(spritz_ctx ctx, key, keyLen)
    Setup spritz state (spritz_ctx) with a key.
  spritz_setupIV(spritz_ctx ctx, key, keyLen, nonce, nonceLen)
    Setup spritz state with a key and nonce (Salt).
  spritz_rand_byte(spritz_ctx ctx)
    Generates a byte of keystream from spritz state (spritz_ctx).


  spritz_hash(digest, digestLen, data, dataLen)
    Spritz cryptographic hash function.
  spritz_mac(digest, digestLen, msg, msgLen, key, keyLen)
    Spritz Message Authentication Code (MAC) function.


  spritz_hash_setup(spritz_ctx hash_ctx)
    Setup spritz hash state.
  spritz_hash_update(spritz_ctx hash_ctx, data, dataLen)
    Add data chunk to hash.
  spritz_hash_final(spritz_ctx hash_ctx, digest, digestLen)
    Output hash digest.

  spritz_mac_setup(spritz_ctx mac_ctx, key, keyLen)
    Setup spritz MAC state.
  spritz_mac_update(spritz_ctx mac_ctx, msg, msgLen)
    Add message/data chunk to MAC.
  spritz_mac_final(spritz_ctx mac_ctx, digest, digestLen)
    Output MAC digest.


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


Copyright
=========

Copyright (c) 2015 Abderraouf Adjal
License: The MIT License.
