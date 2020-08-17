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
 * SPRITZ_TIMING_SAFE_CRUSH, SPRITZ_WIPE_TRACES, SPRITZ_WIPE_TRACES_PARANOID,
 * SPRITZ_USE_LIBC.
 * For detailed information, read the documentation.
 */
#include <SpritzCipher.h>
#include <ESP8266WiFi.h>



/* Table of alphabetic (uppercase and lowercase) and numeric characters */
const char alphanumeric_table[62] =
{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

#define PASSWORD_LEN 28 /* ~160-bit of entropy password; ceil(160/log2(26*2+10)) */
/* One spritz_ctx (One mem buffer) to save some memory.
 * For both, hash function and the random numbers generator.
 */
spritz_ctx the_ctx;

void setup() {
  volatile uint32_t hw_rng; /* The RNG seed */
  uint8_t buf[32];

  /* Initialize serial and wait for port to open */
  Serial.begin(115200);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }

  /* We did NOT use spritz_hash() cause it will have its own spritz_ctx,
   * And we like to save memory
   */
  /* To make a 256-bit hash of the entropy */
  spritz_hash_setup(&the_ctx); /* Initialize */
  
  /* Insert 64*4=256 bytes of entropy in hash function */
  for (uint16_t i = 0; i < 64; i++) {
    delay(1);
    hw_rng = *(volatile uint32_t *)0x3FF20E44;
    spritz_hash_update(&the_ctx, (const uint8_t *)&hw_rng, (uint16_t)(sizeof(hw_rng))); /* Add 4 bytes of entropy */
  }

  spritz_hash_final(&the_ctx, buf, (uint8_t)(sizeof(buf))); /* Output the final hash */
  spritz_memzero((uint8_t *)&hw_rng, (uint16_t)(sizeof(hw_rng)));

  /* Initialize/Seed the RNG with the hash of entropy */
  spritz_setup(&the_ctx, buf, (uint8_t)(sizeof(buf))); /* wipe "the_ctx" data by replacing it with zeros (0x00) */
  spritz_memzero(buf, (uint16_t)(sizeof(buf))); /* wipe "buf" data by replacing it with zeros (0x00) */

  Serial.println(F("\n\n[Make strong Alphanumeric passwords]\n\n"));
}


void loop() {
  /* Print random uniformly distributed alphanumeric characters.
   * Better than: rand_char = charactersTable[random() % number_Of_elements_In_charactersTable]
   */
  for (uint8_t i = 0; i < PASSWORD_LEN; i++) {
    Serial.print((char)alphanumeric_table[spritz_random32_uniform(&the_ctx, (uint32_t)(sizeof(alphanumeric_table)))]);
  }
  Serial.println();

  delay(1000); /* Wait 1s */
}
