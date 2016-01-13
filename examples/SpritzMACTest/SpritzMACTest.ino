/**
 * Spritz Cipher MAC Test
 *
 * This example code test SpritzCipher library MAC output.
 *
 * The circuit:  No external hardware needed.
 *
 * by Abderraouf Adjal.
 *
 * This example code is in the public domain.
 */


#include <SpritzCipher.h>


/* Data to input */
const byte testMsg[3] = { 'A', 'B', 'C' };
const byte testKey[3] = { 0x00, 0x01, 0x02 };

/* Test vectors */
/* MSG='ABC' KEY=0x00,0x01,0x02 MAC test vectors */
const byte MACtestVector[32] =
{ 0xbe, 0x8e, 0xdc, 0xf2, 0x76, 0xcf, 0x57, 0xb4,
  0x0e, 0xbc, 0x8e, 0x22, 0x43, 0x45, 0x7e, 0x3e,
  0xb7, 0xc6, 0x4d, 0x4e, 0x99, 0x1e, 0x93, 0x58,
  0xce, 0x81, 0xef, 0xb1, 0x6c, 0xce, 0xc7, 0xed
};


void testFunc(const byte ExpectedOutput[32], const byte *msg, byte msgLen, const byte *key, byte keyLen)
{
  byte macLen = 32; /* 256-bit */
  byte digest[macLen]; /* Output buffer */
  unsigned int i;

  spritz_mac(digest, macLen, msg, msgLen, key, keyLen);

  for (i = 0; i < sizeof(digest); i++) {
    if (digest[i] < 0x10) { /* To print "0F" not "F" */
      Serial.write('0');
    }
    Serial.print(digest[i], HEX);
  }

  /* Check the output */
  if (spritz_compare(digest, ExpectedOutput, sizeof(digest))) {
    /* If the output is wrong "Alert" */
    digitalWrite(LED_BUILTIN, HIGH); /* Turn pin LED_BUILTIN On (Most boards have this LED connected to digital pin 13) */
    Serial.println("\n** WARNING: Output != Test_Vector **");
  }
  Serial.println();
}

void setup() {
  /* Initialize serial and wait for port to open */
  Serial.begin(9600);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }

  /* initialize digital pin LED_BUILTIN (Most boards have this LED connected to digital pin 13) as an output */
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  Serial.println("[Spritz spritz_mac(MSG='ABC' KEY=0x00,0x01,0x02) test]\n");

  /* MSG='ABC' KEY=0x00,0x01,0x02 MAC test vectors */
  testFunc(MACtestVector, testMsg, sizeof(testMsg), testKey, sizeof(testKey));

  delay(5000); /* Wait 5s */
  Serial.println();
}
