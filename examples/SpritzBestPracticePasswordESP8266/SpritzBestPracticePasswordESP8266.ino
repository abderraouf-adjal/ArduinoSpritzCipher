/**
 * Generate a strong Alphanumeric passwords, and then print it.
 * The initial entropy source will be from hardware RNG in ESP8266 SoC.
 *
 * This code show what the library can do (show off the API).
 * An embedded entropy/seed for the RNG is used.
 *
 * The circuit:  ESP8266 SoC.
 *
 * by Abderraouf Adjal.
 *
 * This example code is in the public domain.
 */

/* ArduinoSpritzCipher documentation: <README.md> */


/* ArduinoSpritzCipher is configurable in <SpritzCipher.h> with:
 * SPRITZ_TIMING_SAFE_CRUSH, SPRITZ_WIPE_TRACES, SPRITZ_WIPE_TRACES_PARANOID.
 * For detailed information, read the documentation.
 */
#include <SpritzCipher.h>
#include <ESP8266WiFi.h>

/* The RNG seed */
volatile uint32_t hw_rng;
uint8_t entropy_buf[256]; /* You can also use malloc() & free(). */

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
  /* One spritz_ctx (One mem buffer) to save some memory.
   * For both, hash function and the random numbers generator.
   */

  for (size_t i = 0; i < (sizeof(entropy_buf)/4); i += 4) {
    delay(1);
    hw_rng = *(volatile uint32_t *)0x3FF20E44;
    entropy_buf[i]   = ((uint8_t *) &hw_rng)[0];
    entropy_buf[i+2] = ((uint8_t *) &hw_rng)[1];
    entropy_buf[i+3] = ((uint8_t *) &hw_rng)[2];
    entropy_buf[i+4] = ((uint8_t *) &hw_rng)[3];
  }
  

  /* We did NOT use spritz_hash() cause it will have its own spritz_ctx,
   * And we like to save memory
   */
  /* Make a 256-bit hash of the entropy in "buf" using one function */
  spritz_hash_setup(&the_ctx); /* Initialize */
  spritz_hash_update(&the_ctx, entropy_buf, (uint16_t)(sizeof(entropy_buf))); /* Add data */
  spritz_hash_final(&the_ctx, buf, (uint8_t)(sizeof(buf))); /* Output the final hash */

  spritz_state_memzero(&the_ctx); /* wipe "the_ctx" data by replacing it with zeros (0x00) */
  spritz_memzero(entropy_buf, (uint16_t)(sizeof(entropy_buf))); /* wipe "entropy" data by replacing it with zeros (0x00) */
  spritz_memzero((uint8_t *)hw_rng, (uint16_t)(sizeof(hw_rng)));

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
