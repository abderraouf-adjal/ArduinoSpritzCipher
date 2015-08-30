/**
 * Spritz Cipher Benchmark
 *
 * This example code test SpritzCipher library speed
 *
 * The circuit:  No external hardware needed.
 *
 * Created 25 Aug. 2015
 * by Abderraouf Adjal <abderraouf.adjal@gmail.com>
 *
 * This example code is in the public domain.
 */


#include <SpritzCipher.h>


SpritzCipher sc;
spritz_t s_ctx;


const unsigned char data[32] =
{ '3', '.', '1', '4', '1', '5', '9', '2',
  '6', '5', '3', '5', '8', '9', '7', '9',
  '3', '2', '3', '8', '4', '6', '2', '6',
  '4', '3', '3', '8', '3', '2', '7', '9'
};

unsigned char buf[32];


void setup() {
  Serial.begin(9600);
  while (!Serial);

  
}


void loop() {
  register unsigned int i;
  register unsigned char j;
  unsigned long m, n;
  float d;
  
  Serial.println(F("\n[Spritz Library Benchmark]\n"));
  delay(100);
  
  Serial.print(F("setup() benchmark:\n"));
  delay(100);
  m = millis();
  for (i = 0; i < 64; i++)
  {
    for (j = 0; j < 64; j++)
    {
      sc.setup(&s_ctx, data, sizeof(data));
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  Serial.print(d * 1000.0, 3);
  Serial.println(F(" uS"));
  
  delay(500);
  Serial.print(F("stream() benchmark:\n"));
  delay(100);
  m = millis();
  for (i = 0; i < 4096; i++)
  {
    for (j = 0; j < 32; j++)
    {
      buf[j] = sc.stream(&s_ctx);
    }
  }
  n = millis();
  d = ((float)n - (float)m) / ((float)i * (float)j);
  Serial.print(d * 1000.0, 3);
  Serial.println(F(" uS"));
  
  delay(500);
  Serial.print(F("hash() benchmark:\n"));
  delay(100);
  m = millis();
  for (i = 0; i < 512; i++)
  {
    sc.hash(buf, 32, data, 32);
  }
  n = millis();
  d = ((float)n - (float)m) / (float)i;
  Serial.print(d * 1000.0, 3);
  Serial.println(F(" uS"));
}
