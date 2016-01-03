/**
 * Hash 32 KB of Spritz stream (random bytes generator output)
 * then print the result.
 *
 * This code show what can ArduinoSpritzCipher library do (ShowOff API).
 * An embedded seed for the RNG is used.
 *
 * The circuit:  No external hardware needed.
 *
 * by Abderraouf Adjal.
 *
 * This example code is in the public domain.
 */


#include <SpritzCipher.h>


/* The RNG seed (64 digits of Pi) */
const uint8_t seed[64] =
{ '3', '1', '4', '1', '5', '9', '2', '6',
  '5', '3', '5', '8', '9', '7', '9', '3',
  '2', '3', '8', '4', '6', '2', '6', '4',
  '3', '3', '8', '3', '2', '7', '9', '5',

  '0', '2', '8', '8', '4', '1', '9', '7',
  '1', '6', '9', '3', '9', '9', '3', '7',
  '5', '1', '0', '5', '8', '2', '0', '9',
  '7', '4', '9', '4', '4', '5', '9', '2'
};

/* The expected result, Same as Github user @jedisct1 implementation */
const uint8_t ExpectedHash[32] =
{ 0xef, 0xc4, 0x5b, 0xd6, 0xf9, 0xd9, 0xe7, 0x78,
  0x83, 0xa5, 0x54, 0x60, 0x65, 0xde, 0xa2, 0x7f,
  0x4a, 0x02, 0xa3, 0x3d, 0x35, 0x5b, 0xcd, 0x07,
  0x48, 0xa9, 0xa1, 0xb3, 0x54, 0xfc, 0x50, 0x3a
};

void setup() {
  /* Initialize serial and wait for port to open */
  Serial.begin(9600);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }
}

void loop() {
  spritz_ctx hash_ctx; /* For the hash */
  spritz_ctx rng_ctx; /* For the random bytes generator */

  uint8_t digest[32]; /* Hash result, 256-bit */
  uint8_t rng_buf[32]; /* Random bytes generator output buffer */

  uint8_t i;
  uint16_t j;
  uint16_t LOOP_ROUNDS = 1024; /* 32 KB: (1024 * 32) / sizeof(rng_buf) */


  Serial.println("\n[Hash 32 KB of Spritz random bytes generator output]\n");


  spritz_hash_setup(&hash_ctx);
  spritz_setup(&rng_ctx, seed, (uint8_t)(sizeof(seed)));

  for (j = 0; j < LOOP_ROUNDS; j++) {
    /* Fill rng_buf with Spritz random bytes generator output */
    for (i = 0; i < (uint8_t)(sizeof(rng_buf)); i++) {
      rng_buf[i] = spritz_random_byte(&rng_ctx);
    }
    /* Add rng_buf data to hash_ctx */
    spritz_hash_update(&hash_ctx, rng_buf, (uint16_t)(sizeof(rng_buf)));
  }

  spritz_hash_final(&hash_ctx, digest, (uint8_t)(sizeof(digest)));

  /* Print the hash in HEX */
  for (i = 0; i < (uint8_t)(sizeof(digest)); i++) {
    if (digest[i] < 0x10) { /* To print "0F", not "F" */
      Serial.write('0');
    }
    Serial.print(digest[i], HEX);
  }
  Serial.println();

  /* Check the output */
  if (spritz_is_equal(digest, ExpectedHash, (uint16_t)(sizeof(digest)))) {
    /* If the output is wrong "Alert" */
    Serial.println("\n** WARNING: hash != expected hash **");
  }

/* If spritz_hash_final() will not wipe hash_ctx data */
#ifdef WIPE_AFTER_USAGE
  spritz_wipe(&hash_ctx);
#endif

  spritz_wipe(&rng_ctx);


  //delay(5000); /* Wait 5s */
}
