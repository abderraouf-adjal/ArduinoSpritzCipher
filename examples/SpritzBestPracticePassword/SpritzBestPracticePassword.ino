/**
 * Generate a strong Alphanumeric passwords, and then print it
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


void setup() {
  /* Initialize serial and wait for port to open */
  Serial.begin(9600);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }
}


void loop() {
  uint8_t password_len = 28; /* ~160-bit of entropy password; ceil(160/log2(26*2+10)) */
  uint8_t buf[32];
  spritz_ctx the_ctx;
  /* One spritz_ctx, One buffer.
   * For both, hash function and the random numbers generator (Memory saving)
   */

  /* We did NOT use spritz_hash() cause it will have its own spritz_ctx,
   * And we like to save memory
   */
  /* Make a 256-bit hash of the entropy in "buf" using one function */
  spritz_hash_setup(&the_ctx); /* Initialize */
  spritz_hash_update(&the_ctx, entropy, (uint16_t)(sizeof(entropy))); /* Add data */
  spritz_hash_final(&the_ctx, buf, (uint8_t)(sizeof(buf))); /* Output the final hash */

  spritz_state_memzero(&the_ctx); /* wipe "the_ctx" data by replacing it with zeros (0x00) */
  spritz_memzero(entropy, (uint16_t)(sizeof(entropy))); /* wipe "entropy" data by replacing it with zeros (0x00) */

  /* Initialize/Seed the RNG with the hash of entropy */
  spritz_setup(&the_ctx, buf, (uint8_t)(sizeof(buf)));

  spritz_memzero(buf, (uint16_t)(sizeof(buf))); /* wipe "buf" data by replacing it with zeros (0x00) */


  Serial.println("\n[Make strong Alphanumeric passwords]\n");

  while (1)
  {
    /* Fill the buffer with random uniformly distributed alphanumeric characters */
    for (uint8_t i = 0; i < password_len; i++) {
      /* Like: buf[i] = charactersTable[random() % number_Of_elements_In_charactersTable] */
      buf[i] = alphanumeric_table[spritz_random32_uniform(&the_ctx, (uint32_t)(sizeof(alphanumeric_table)))];
    }

    /* Print the password */
    Serial.write(buf, password_len);
    Serial.println();

    delay(1000); /* Wait 1s */
  }
}
