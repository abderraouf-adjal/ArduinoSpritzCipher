/**
 * Spritz Cipher Stream Test
 *
 * This example code test SpritzCipher library stream output
 * using test vectors from "RS14.pdf" Page 30:
 * <https://people.csail.mit.edu/rivest/pubs/RS14.pdf>
 *
 * The circuit:  No external hardware needed.
 *
 * Created 25 Aug. 2015
 * by Abderraouf Adjal <abderraouf.adjal@gmail.com>
 *
 * This example code is in the public domain.
 */


#include <SpritzCipher.h>

/* Keys to input */
const unsigned char testKey1[3] = { 'A', 'B', 'C' };
const unsigned char testKey2[4] = { 's', 'p', 'a', 'm' };
const unsigned char testKey3[7] = { 'a', 'r', 'c', 'f', 'o', 'u', 'r' };

/* Test vectors */
/* Key 'ABC' stream test vectors */
const unsigned char testVector1[32] =
{ 0x77, 0x9a, 0x8e, 0x01, 0xf9, 0xe9, 0xcb, 0xc0,
  0x7f, 0xb9, 0x6b, 0x7e, 0xc1, 0x93, 0x6e, 0x24,
  0x2e, 0x54, 0xf1, 0x8b, 0x6c, 0x3c, 0x76, 0xcf,
  0x8f, 0xc8, 0x2f, 0x22, 0x2b, 0x20, 0xe4, 0xbb
};
/* Key 'spam' stream test vectors */
const unsigned char testVector2[32] =
{ 0xf0, 0x60, 0x9a, 0x1d, 0xf1, 0x43, 0xce, 0xbf,
  0x58, 0xdc, 0xff, 0x3d, 0x30, 0xb7, 0xc2, 0x59,
  0x9d, 0x2f, 0xb0, 0xdc, 0x2b, 0x7a, 0x12, 0xc4,
  0xe8, 0x92, 0x16, 0xcc, 0x5d, 0xe9, 0x29, 0x67
};
/* Key 'arcfour' stream test vectors */
const unsigned char testVector3[32] =
{ 0x1a, 0xfa, 0x8b, 0x5e, 0xe3, 0x37, 0xdb, 0xc7,
  0x22, 0x59, 0x7f, 0x0f, 0xdc, 0x3a, 0x42, 0xc7,
  0x75, 0x4b, 0xf1, 0x03, 0x6f, 0x54, 0xfb, 0x4a,
  0xeb, 0x03, 0x35, 0xd4, 0xa4, 0xe9, 0xa3, 0x6e
};

unsigned char buf[32]; /* Output buffer */

SpritzCipher sc;

spritz_t s_ctx;


void setup() {
  /* Initialize serial (4800 bps) and wait for port to open */
  Serial.begin(4800);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }
}

void loop() {
  /* Key: ABC */
  Serial.println("stream('ABC'):");
  sc.setup(&s_ctx, testKey1, sizeof(testKey1));
  for (unsigned int i = 0; i < sizeof(buf); i++) {
    buf[i] = sc.stream(&s_ctx);
    if (buf[i] < 0x10) {
      Serial.write('0');
    }
    Serial.print(buf[i], HEX);
  }
  Serial.println();
  /* Check the output */
  for (size_t i = 0; i < sizeof(buf); i++) {
    /* If the output is wrong */
    if (buf[i] != testVector1[i]) {
      Serial.println("** WARNING: Output_1 != Test_Vector **");
    }
  }

  /* Key: spam */
  Serial.println("stream('spam'):");
  sc.setup(&s_ctx, testKey2, sizeof(testKey2));
  for (unsigned int i = 0; i < sizeof(buf); i++) {
    buf[i] = sc.stream(&s_ctx);
    if (buf[i] < 0x10) {
      Serial.write('0');
    }
    Serial.print(buf[i], HEX);
  }
  Serial.println();
  /* Check the output */
  for (size_t i = 0; i < sizeof(buf); i++) {
    /* If the output is wrong */
    if (buf[i] != testVector2[i]) {
      Serial.println("** WARNING: Output_2 != Test_Vector **");
    }
  }

  /* Key: arcfour */
  Serial.println("stream('arcfour'):");
  sc.setup(&s_ctx, testKey3, sizeof(testKey3));
  for (unsigned int i = 0; i < sizeof(buf); i++) {
    buf[i] = sc.stream(&s_ctx);
    if (buf[i] < 0x10) {
      Serial.write('0');
    }
    Serial.print(buf[i], HEX);
  }
  Serial.println();
  /* Check the output */
  for (size_t i = 0; i < sizeof(buf); i++) {
    /* If the output is wrong */
    if (buf[i] != testVector3[i]) {
      Serial.println("** WARNING: Output_3 != Test_Vector **");
    }
  }


  delay(5000); /* Wait 5s */
}
