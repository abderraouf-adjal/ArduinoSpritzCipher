/**
 * ArduinoSpritzCipher library benchmark
 *
 * This example code test SpritzCipher library performance.
 *
 * The circuit:  No external hardware needed.
 *
 * by Abderraouf Adjal.
 *
 * This example code is in the public domain.
 */

/** Output of Arduino Uno ATmega328P 16 MHz:
 * 
 * # Benchmark of spritz_setup() with 256-bit key:
 * 10209.22 us.
 * 97.95 time per second for spritz_setup() with 256-bit key.
 * 
 * # Benchmark of spritz_setup_withIV() with 256-bit key and 256-bit nonce:
 * 20283.28 us.
 * 49.30 time per second for spritz_setup_withIV() with 256-bit key and 256-bit nonce.
 * 
 * # Benchmark of spritz_random8():
 * 9.84 us.
 * 101587.31 spritz_random8() per second.
 * 
 * # Benchmark of 256-bit hash with 32-byte input using setup,update,final method:
 * 10543.34 us.
 * 94.85 time per second for 256-bit hash with 32-byte input using setup,update,final method.
 * 
 * # Benchmark of 256-bit MAC with 32-byte msg and 256-bit key using setup,update,final method:
 * 20619.81 us.
 * 48.50 time per second for 256-bit MAC with 32-byte msg and 256-bit key using setup,update,final method.
 */

#include <SpritzCipher.h>


/* Data samples */
/* Key 'ABC' stream test vectors as a data sample 1 */
const byte testData1[32] =
{ 0x77, 0x9a, 0x8e, 0x01, 0xf9, 0xe9, 0xcb, 0xc0,
  0x7f, 0xb9, 0x6b, 0x7e, 0xc1, 0x93, 0x6e, 0x24,
  0x2e, 0x54, 0xf1, 0x8b, 0x6c, 0x3c, 0x76, 0xcf,
  0x8f, 0xc8, 0x2f, 0x22, 0x2b, 0x20, 0xe4, 0xbb
};
/* An output buffer for hash and MAC function */
uint8_t digest_buf_32[32];


void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_setup_128_time_with_testData1(spritz_ctx *ctx)
{
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
  spritz_setup(ctx, testData1, sizeof(testData1)); spritz_setup(ctx, testData1, sizeof(testData1));
}
float benchmark_spritz_setup(spritz_ctx *ctx)
{
    unsigned long start;
    float elapsed;
    start = micros();
    spritz_setup_128_time_with_testData1(ctx);
    elapsed = micros() - start;
    return (elapsed / 128.0);
}

void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_setup_withIV_128_time_with_testData1(spritz_ctx *ctx)
{
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
  spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1)); spritz_setup_withIV(ctx, testData1, sizeof(testData1), testData1, sizeof(testData1));
}
float benchmark_spritz_setup_withIV(spritz_ctx *ctx)
{
    unsigned long start;
    float elapsed;
    start = micros();
    spritz_setup_withIV_128_time_with_testData1(ctx);
    elapsed = micros() - start;
    return (elapsed / 128.0);
}

void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_random8_128_time(spritz_ctx *ctx)
{
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
  spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx); spritz_random8(ctx);
}
float benchmark_spritz_random8(spritz_ctx *ctx)
{
    unsigned long start;
    float elapsed;
    start = micros();
    spritz_random8_128_time(ctx);
    elapsed = micros() - start;
    return (elapsed / 128.0);
}

void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_hash32_128_time_32byte_input(spritz_ctx *ctx)
{
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_hash_setup(ctx); spritz_hash_update(ctx, testData1, sizeof(testData1)); spritz_hash_final(ctx, digest_buf_32, sizeof(digest_buf_32));
}
float benchmark_spritz_hash32_32byte_input(spritz_ctx *ctx)
{
    unsigned long start;
    float elapsed;
    start = micros();
    spritz_hash32_128_time_32byte_input(ctx);
    elapsed = micros() - start;
    return (elapsed / 128.0);
}

void
/* Disable optimization for this function if compiler is GCC */
#if defined(__GNUC__) && !defined(__clang__)
__attribute__ ((optimize("O0")))
/* Disable optimization for this function if compiler is Clang */
#elif defined(__clang__)
__attribute__ ((optnone))
#endif
spritz_mac32_128_time_32byte_msg_32byte_key(spritz_ctx *ctx)
{
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
  spritz_mac_setup(ctx, testData1, sizeof(testData1)); spritz_mac_update(ctx, testData1, sizeof(testData1)); spritz_mac_final(ctx, digest_buf_32, sizeof(digest_buf_32));
}
float benchmark_spritz_mac32_32byte_input(spritz_ctx *ctx)
{
    unsigned long start;
    float elapsed;
    start = micros();
    spritz_mac32_128_time_32byte_msg_32byte_key(ctx);
    elapsed = micros() - start;
    return (elapsed / 128.0);
}

void setup() {
  /* Initialize serial and wait for port to open */
  Serial.begin(9600);
  while (!Serial) {
    ; /* Wait for serial port to connect. Needed for Leonardo only */
  }
}

void loop() {
  float elapsed1, elapsed2, elapsed3, elapsed4, elapsed5;
  spritz_ctx ctx;
  
  Serial.println("\nBenchmarking...");
  
  elapsed1 = benchmark_spritz_setup(&ctx);
  elapsed2 = benchmark_spritz_setup_withIV(&ctx);
  elapsed3 = benchmark_spritz_random8(&ctx);
  elapsed4 = benchmark_spritz_hash32_32byte_input(&ctx);
  elapsed5 = benchmark_spritz_mac32_32byte_input(&ctx);
  
  /* Benchmark of spritz_setup() with 256-bit key */
  Serial.println("\n# Benchmark of spritz_setup() with 256-bit key:");
  Serial.print(elapsed1); Serial.println(" us.");
  Serial.print(1000000.0 / elapsed1); Serial.println(" time per second for spritz_setup() with 256-bit key.");
  
  /* Benchmark of spritz_setup_withIV() with 256-bit key and 256-bit nonce */
  Serial.println("\n# Benchmark of spritz_setup_withIV() with 256-bit key and 256-bit nonce:");
  Serial.print(elapsed2); Serial.println(" us.");
  Serial.print(1000000.0 / elapsed2); Serial.println(" time per second for spritz_setup_withIV() with 256-bit key and 256-bit nonce.");
  
  /* Benchmark of spritz_random8() */
  Serial.println("\n# Benchmark of spritz_random8():");
  Serial.print(elapsed3); Serial.println(" us.");
  Serial.print(1000000.0 / elapsed3); Serial.println(" spritz_random8() per second.");
  
  /* Benchmark of 256-bit hash with 32-byte input using setup,update,final method */
  Serial.println("\n# Benchmark of 256-bit hash with 32-byte input using setup,update,final method:");
  Serial.print(elapsed4); Serial.println(" us.");
  Serial.print(1000000.0 / elapsed4); Serial.println(" time per second for 256-bit hash with 32-byte input using setup,update,final method.");
  
  /* Benchmark of 256-bit MAC with 32-byte msg and 256-bit key using setup,update,final method */
  Serial.println("\n# Benchmark of 256-bit MAC with 32-byte msg and 256-bit key using setup,update,final method:");
  Serial.print(elapsed5); Serial.println(" us.");
  Serial.print(1000000.0 / elapsed5); Serial.println(" time per second for 256-bit MAC with 32-byte msg and 256-bit key using setup,update,final method.");

  delay(5000); /* Wait 5s */
  Serial.println();
}
