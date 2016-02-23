/**
 * Hash 32 KB of a Spritz stream (random bytes generator output)
 * then print the result.
 *
 * This code show what the library can do (show off the API).
 * An embedded entropy/seed for the RNG is used.
 *
 * The circuit:  No external hardware needed.
 *
 * by Abderraouf Adjal.
 *
 * This example code is in the public domain.
 */


#include <SpritzCipher.h>


/* The RNG seed (64 digits of Pi) */
const uint8_t entropy[64] =
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
{ 0x11, 0xfe, 0x5e, 0xf8, 0x91, 0xa3, 0xcf, 0xb9,
  0x54, 0x07, 0x54, 0x8e, 0xa0, 0x5e, 0x0b, 0xeb,
  0xaf, 0x94, 0xf2, 0x7a, 0x46, 0xfa, 0xbb, 0xad,
  0x21, 0xf7, 0x57, 0x4e, 0xee, 0x66, 0xab, 0xd9
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
  uint8_t buf[32];

  uint8_t i;
  uint16_t j;
  uint16_t LOOP_ROUNDS = 1024; /* 32 KB: (1024 * 32) / sizeof(buf) */


  Serial.println("\n[Hash 32 KB of Spritz random bytes generator output]\n");

  /* Make a 256-bit hash of the entropy in "buf" using one function */
  spritz_hash(buf, (uint8_t)(sizeof(buf)), entropy, (uint8_t)(sizeof(entropy)));
  /* Initialize/Seed the RNG with the hash of entropy */
  spritz_setup(&rng_ctx, buf, (uint8_t)(sizeof(buf)));

  /* The data will be generated in small chunks,
   * So we can not use "one function API" */
  spritz_hash_setup(&hash_ctx);

  for (j = 0; j < LOOP_ROUNDS; j++) {
    /* Fill buf with Spritz random bytes generator output */
    for (i = 0; i < (uint8_t)(sizeof(buf)); i++) {
      buf[i] = spritz_random8(&rng_ctx);
    }
    /* Add buf data to hash_ctx */
    spritz_hash_update(&hash_ctx, buf, (uint16_t)(sizeof(buf)));
  }

  /* Output the final hash */
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
  if (spritz_compare(digest, ExpectedHash, (uint16_t)(sizeof(digest)))) {
    /* If the output is wrong "Alert" */
    Serial.println("\n** WARNING: hash != expected hash **");
  }

  /* wipe "hash_ctx" data by replacing it with zeros (0x00) */
  spritz_state_memzero(&hash_ctx);

  /* wipe "digest" data by replacing it with zeros (0x00) */
  spritz_memzero(digest, (uint16_t)(sizeof(digest)));

  /* Keys, RNG seed & buffer should be wiped in realworld.
   * In this example we should not wipe "entropy"
   * cause it is embedded in the code */
  spritz_state_memzero(&rng_ctx);
  spritz_memzero(buf, (uint16_t)(sizeof(buf)));
}
