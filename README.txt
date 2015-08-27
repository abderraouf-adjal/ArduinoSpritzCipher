SpritzCipher
============

Spritz library for Arduino.
A spongy RC4-like stream cipher, Hash and MAC function.

Home page: <https://github.com/abderraouf-adjal/ArduinoSpritzCipher>

Spritz paper: <https://people.csail.mit.edu/rivest/pubs/RS14.pdf>


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
           const byte *key, unsigned int keyLen);
void setupIV(spritz_t *ctx,
             const byte *nonce, unsigned int nonceLen);
byte stream(spritz_t *ctx);

void hash(byte *digest, byte digestLen,
          const byte *data, unsigned int dataLen);
void mac(byte *digest, byte digestLen,
         const byte *msg, unsigned int msgLen,
         const byte *key, unsigned int keyLen);


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
