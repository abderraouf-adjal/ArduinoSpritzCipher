# Spritz Library For Arduino

> Spritz - a spongy RC4-like stream cipher and hash function.

This library contains a cryptographic pseudo-random number generator,
cryptographic hash and message authentication code (MAC) functions,
can perform symmetric-key authenticated data encryption, and general-purpose
functions for timing-safe comparison and wiping data from memory.

This C Spritz library can be used to:
  - Hash and authenticate data.
  - Perform symmetric-key authenticated data encryption.
  - Generate random numbers and strings from entropy/seed.

[This library's GitHub repository](https://github.com/abderraouf-adjal/ArduinoSpritzCipher).

[This library's Bitbucket repository](https://bitbucket.org/abderraouf-adjal/arduinospritzcipher) (Backup).

**Spritz paper:** https://people.csail.mit.edu/rivest/pubs/RS14.pdf


## Library Content

#### Read the source code for details.

### Types

**spritz_ctx** - The context/ctx (contains the state). The state consists of byte registers
{i, j, k, z, w, a}, And an array {s} containing a permutation of {0, 1, ... , SPRITZ_N-1}.

**uint8_t**  - unsigned integer type with width of 8-bit, MIN=0;MAX=255.

**uint16_t** - unsigned integer type with width of 16-bit, MIN=0;MAX=65,535.

**uint32_t** - unsigned integer type with width of 32-bit, MIN=0;MAX=4,294,967,295.


### Functions

```c
uint8_t spritz_compare(const uint8_t *data_a, const uint8_t *data_b,
                       uint16_t len)
```

Timing-safe comparison for `data_a` and `data_b` equality.
This function can be used to compare the password's hash safely.

Return equality result.
Zero (0x00) if `data_a` equals `data_b` OR if `len` is zero,
Non-zero value if they are NOT equal.

```c
void spritz_memzero(uint8_t *buf, uint16_t len)
```

Wipe `buf` data by replacing it with `len` zeros (0x00).

```c
void spritz_state_memzero(spritz_ctx *ctx)
```

Wipe `spritz_ctx`'s data by replacing its data with zeros (0x00).

If `SPRITZ_WIPE_TRACES_PARANOID` is defined, This function will
wipe the *sensitive* temporary variables in `spritz_ctx`.

```c
void spritz_setup(spritz_ctx *ctx,
                  const uint8_t *key, uint8_t keyLen)
```

Setup the spritz state `spritz_ctx` with a `key` of length `keyLen`.

```c
void spritz_setup_withIV(spritz_ctx *ctx,
                         const uint8_t *key, uint8_t keyLen,
                         const uint8_t *nonce, uint8_t nonceLen)
```

Setup the spritz state `spritz_ctx` with a `key` and `nonce`/Salt/IV.

```c
uint8_t spritz_random8(spritz_ctx *ctx)
```

Generates a random byte (8-bit) from the spritz state `spritz_ctx`.

```c
uint32_t spritz_random32(spritz_ctx *ctx)
```

Generates a random 32-bit (4 bytes) from the spritz state `spritz_ctx`.

```c
uint32_t spritz_random32_uniform(spritz_ctx *ctx, uint32_t upper_bound)
```

Calculate an uniformly distributed random number less than `upper_bound` avoiding *modulo bias*.
Uniformity is achieved by generating new random numbers until the one
returned is outside the range [0, 2\*\*32 % `upper_bound`).
This guarantees the selected random number will be inside
[2\*\*32 % `upper_bound`, 2\*\*32) which maps back to [0, `upper_bound`)
after reduction modulo `upper_bound`.

```c
void spritz_add_entropy(spritz_ctx *ctx,
                        const uint8_t *entropy, uint16_t len)
```

Add `entropy` to the spritz state `spritz_ctx` using the internal function `absorb()`.

```c
void spritz_crypt(spritz_ctx *ctx,
                  const uint8_t *data, uint16_t dataLen,
                  uint8_t *dataOut)
```

Encrypt or decrypt `data` chunk by XOR-ing it with the spritz keystream.

```c
void spritz_hash(uint8_t *digest, uint8_t digestLen,
                 const uint8_t *data, uint16_t dataLen)
```

Spritz cryptographic hash function.

```c
void spritz_mac(uint8_t *digest, uint8_t digestLen,
                const uint8_t *msg, uint16_t msgLen,
                const uint8_t *key, uint16_t keyLen)
```

Spritz Message Authentication Code (MAC) function.

```c
void spritz_hash_setup(spritz_ctx *hash_ctx)
```

Setup the spritz hash state.

```c
void spritz_hash_update(spritz_ctx *hash_ctx,
                        const uint8_t *data, uint16_t dataLen)
```

Add a message/data chunk `data` to hash.

```c
void spritz_hash_final(spritz_ctx *hash_ctx,
                       uint8_t *digest, uint8_t digestLen)
```

Output the hash digest.

```c
void spritz_mac_setup(spritz_ctx *mac_ctx,
                      const uint8_t *key, uint16_t keyLen)
```

Setup the spritz Message Authentication Code (MAC) state.

```c
void spritz_mac_update(spritz_ctx *mac_ctx,
                       const uint8_t *msg, uint16_t msgLen)
```

Add a message/data chunk to Message Authentication Code (MAC).

```c
void spritz_mac_final(spritz_ctx *mac_ctx,
                      uint8_t *digest, uint8_t digestLen)
```

Output the Message Authentication Code (MAC) digest.


##### Notes:
`spritz_random8()`, `spritz_random32()`, `spritz_random32_uniform()`, `spritz_add_entropy()`, `spritz_crypt()`.
Are usable only after calling `spritz_setup()` or `spritz_setup_withIV()`.

Functions `spritz_random*()` requires `spritz_setup()` or `spritz_setup_withIV()` initialized with an entropy (random data), 128-bit of entropy at least.
Arduino Uno's ATmega328P and many microcontrollers and microprocessors does not have a real source of entropy,
you may need an external source of entropy such as external hardware to get it, or at least a prestored random data updated with `spritz_random*()`.

To generate a random number in a range [k, m) use `k + spritz_random32_uniform(ctx, m)`,
Not `k + (spritz_random8(ctx) % m)` or `k + (spritz_random32(ctx) % m)`.

Use `spritz_state_memzero()` after `spritz_hash_final()` or `spritz_mac_final()`
if you need to wipe the used `spritz_ctx`'s data.


### Constants
**SPRITZ_TIMING_SAFE_CRUSH**

If defined, The equal time `crush()` will be used.

`SPRITZ_TIMING_SAFE_CRUSH` is defined by default.

**SPRITZ_WIPE_TRACES**

If defined, Sensitive data like `spritz_ctx` will be wiped, when they are
no longer needed, in the functions: `spritz_hash()`, `spritz_mac()`.

`SPRITZ_WIPE_TRACES` is defined by default.

**SPRITZ_WIPE_TRACES_PARANOID**

If defined, The library functions internal variables will be wiped if they
contain a bit or more of spritz state, such as temporary variables in a swap
function or user data. Variables that contain data length will not be wiped.

If defined, Then `SPRITZ_WIPE_TRACES` and `SPRITZ_TIMING_SAFE_CRUSH`, will be defined automatically.

`SPRITZ_WIPE_TRACES_PARANOID` is **NOT** defined by default.

**SPRITZ_N** = `256` - Present the value of N in this spritz implementation, *Do NOT change `SPRITZ_N` value*.

**SPRITZ_LIBRARY_VERSION_STRING** = `"1.0.3"` - Present the version of this
spritz library (MAJOR . MINOR . PATCH) using Semantic Versioning.

**SPRITZ_LIBRARY_VERSION_MAJOR** = `1` - The MAJOR version of the library.

**SPRITZ_LIBRARY_VERSION_MINOR** = `0` - The MINOR version of the library.

**SPRITZ_LIBRARY_VERSION_PATCH** = `3` - The PATCH version of the library.


## Examples

* [SpritzBestPractice](examples/SpritzBestPractice/SpritzBestPractice.ino):
Hash 32 KB of a Spritz stream (pseudo-random number generator output) then print the result.
An embedded entropy/seed for the pseudo-random number generator is used.

* [SpritzBestPracticePassword](examples/SpritzBestPracticePassword/SpritzBestPracticePassword.ino):
Generate a strong Alphanumeric passwords, and then print it.
An embedded entropy/seed for the pseudo-random number generator is used.

* [SpritzCryptTest](examples/SpritzCryptTest/SpritzCryptTest.ino):
Test the library encryption/decryption function.

* [SpritzStreamTest](examples/SpritzStreamTest/SpritzStreamTest.ino):
Generate random bytes (Spritz stream) test.

* [SpritzHashTest](examples/SpritzHashTest/SpritzHashTest.ino):
Hash function test.

* [SpritzMACTest](examples/SpritzMACTest/SpritzMACTest.ino):
Message authentication code (MAC) function test.


## Installation Guide

[Arduino IDE](https://www.arduino.cc/en/Main/Software) -
[Additional libraries installation guide](https://www.arduino.cc/en/Guide/Libraries).

Compiling this library using *GCC* or *Clang* will give more security for functions that should be compiled with *zero optimization* (`-O0`) like `spritz_compare()`.


## Reporting bugs

[Create an issue on GitHub](https://github.com/abderraouf-adjal/ArduinoSpritzCipher/issues).


## Copyright and License

> Copyright (c) 2015-2017 Abderraouf Adjal

- The source-code: The MIT License.

- Documentation (e.g. this file content): Licensed under the [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0).

- Examples: Public domain.
