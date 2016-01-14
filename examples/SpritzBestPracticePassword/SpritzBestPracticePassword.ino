/**
 * Make strong Alphanumeric passwords then print it
 *
 * This code show what can ArduinoSpritzCipher library do (ShowOff API).
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
uint8_t entropy[64] =
{ '3', '1', '4', '1', '5', '9', '2', '6',
  '5', '3', '5', '8', '9', '7', '9', '3',
  '2', '3', '8', '4', '6', '2', '6', '4',
  '3', '3', '8', '3', '2', '7', '9', '5',
  '0', '2', '8', '8', '4', '1', '9', '7',
  '1', '6', '9', '3', '9', '9', '3', '7',
  '5', '1', '0', '5', '8', '2', '0', '9',
  '7', '4', '9', '4', '4', '5', '9', '2'
};

/* Table of alphabetic (uppercase and lowercase) and numeric characters */
const uint8_t alphanumeric_table[62] =
{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};


spritz_ctx rng_ctx; /* For the random bytes generator */


void setup() {
  /* Initialize serial and wait for port to open */
  Serial.begin(9600);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }

  uint8_t buf[64];

  /* Make a 512-bit hash of the entropy in "buf" using one function */
  spritz_hash(buf, (uint8_t)(sizeof(buf)), entropy, (uint8_t)(sizeof(entropy)));
  /* Initialize/Seed the RNG with the hash of entropy */
  spritz_setup(&rng_ctx, buf, (uint8_t)(sizeof(buf)));

  /* wipe "entropy" data by replacing it with zeros (0x00) */
  spritz_memzero(entropy, (uint16_t)(sizeof(entropy)));
  /* wipe "buf" data by replacing it with zeros (0x00) */
  spritz_memzero(buf, (uint16_t)(sizeof(buf)));

  Serial.println("\n[Make strong Alphanumeric passwords]\n");
}


void loop() {
  uint8_t password_len = 28; /* ~160-bit of entropy password; ceil(160/log2(26*2+10)) */
  uint8_t password[password_len];

  /* Fill the buffer with random uniformly distributed random alphanumeric characters */
  for (uint8_t i = 0; i < password_len; i++) {
    password[i] = alphanumeric_table[spritz_random_uniform(&rng_ctx, (uint32_t)(sizeof(alphanumeric_table)))];
  }

  /* Print the password */
  Serial.write(password, password_len);

  /* wipe "password" data by replacing it with zeros (0x00) */
  spritz_memzero(password, (uint16_t)(sizeof(password)));
  Serial.println();

  delay(1000); /* Wait 1s */
}
