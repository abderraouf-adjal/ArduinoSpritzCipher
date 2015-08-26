SpritzCipher
============

Spritz Library for Arduino.
A spongy RC4-like stream cipher, Hash and MAC function.

On Github: <https://github.com/abderraouf-adjal/ArduinoSpritzCipher>


Content
=======
* Types
spritz_t - Contain the state.

* Functions
setup()   - To setup spritz state.
setupIV() - Usable after setup() to add Nonce.
stream()  - Return random byte that can be used as a key.
hash()    - Hash function.
mac()     - Message Authentication Code (MAC) function.


Functions
=========
void setup(spritz_t *ctx,
           const unsigned char *key, unsigned int keyLen);
void setupIV(spritz_t *ctx,
             const unsigned char *nonce, unsigned int nonceLen);
unsigned char stream(spritz_t *ctx);

void hash(unsigned char *digest, unsigned char digestLen,
          const unsigned char *data, unsigned int dataLen);
void mac(unsigned char *digest, unsigned char digestLen,
         const unsigned char *msg, unsigned int msgLen,
         const unsigned char *key, unsigned int keyLen);


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

create an issue on GitHub:
<https://github.com/abderraouf-adjal/ArduinoSpritzCipher/issues>


Copyright
=========

Copyright (c) 2015 Abderraouf Adjal

License: The MIT License.
