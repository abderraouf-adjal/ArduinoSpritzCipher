/**
 * Spritz Cipher MAC Test
 *
 * This example code test SpritzCipher library encryption/decryption function.
 * Encrypt and decrypt in same buffer for less RAM usage.
 *
 * The circuit:  No external hardware needed.
 *
 * by Abderraouf Adjal.
 *
 * This example code is in the public domain.
 */

/* ArduinoSpritzCipher documentation: <README.md> */


/* ArduinoSpritzCipher is configurable in <SpritzCipher.h> with:
 * SPRITZ_TIMING_SAFE_CRUSH, SPRITZ_WIPE_TRACES, SPRITZ_WIPE_TRACES_PARANOID,
 * SPRITZ_USE_LIBC.
 * For detailed information, read the documentation.
 */
#include <SpritzCipher.h>


/* Data to input */
byte testMsg[3] = { 'A', 'B', 'C' }; /* Encrypt and decrypt in same buffer. */
const byte testMsg_original[3] = { 'A', 'B', 'C' };
const byte testKey[3] = { 0x00, 0x01, 0x02 };


void testFunc(byte *msg, byte msgLen, const byte *key, byte keyLen)
{
  spritz_ctx s_ctx;
  unsigned int i;

  /* Print MSG */
  for (i = 0; i < msgLen; i++) {
    Serial.write(msg[i]);
  }
  Serial.println();

  /* Print KEY */
  for (i = 0; i < keyLen; i++) {
    if (key[i] < 0x10) { /* To print "0F" not "F" */
      Serial.write('0');
    }
    Serial.print(key[i], HEX);
  }
  Serial.println();

  spritz_setup(&s_ctx, key, keyLen);
  spritz_crypt_inplace(&s_ctx, msg, msgLen); /* Encrypt in same buffer. */
  /* You can also use: spritz_crypt(&s_ctx, msg, msgLen, msg); */

  /* Print Ciphertext */
  for (i = 0; i < msgLen; i++) {
    if (msg[i] < 0x10) { /* To print "0F" not "F" */
      Serial.write('0');
    }
    Serial.print(msg[i], HEX);
  }
  Serial.println();

  spritz_setup(&s_ctx, key, keyLen);
  spritz_crypt_inplace(&s_ctx, msg, msgLen); /* Decrypt in same buffer. */
  /* You can also use: spritz_crypt(&s_ctx, msg, msgLen, msg); */

  /* Print MSG after decryption */
  for (i = 0; i < msgLen; i++) {
    Serial.write(msg[i]);
  }
  Serial.println();

  /* Check the output */
  if (spritz_compare(msg, testMsg_original, msgLen)) {
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
  Serial.println("[Spritz library encryption/decryption function test]\n");

  /* MSG='ABC' KEY=0x00,0x01,0x02 */
  testFunc(testMsg, sizeof(testMsg), testKey, sizeof(testKey));

  delay(5000); /* Wait 5s */
  Serial.println();
}
