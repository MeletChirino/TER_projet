#include <Wire.h>
#include "Gy521.h"
#include <avr/pgmspace.h>

Gy521 gy = Gy521();

int data_size = 100;

void setup() {
  Serial.begin(115200);
  //Serial.println(F("Serial Ready"));
  gy.init();
  //Serial.println(F("Gy ready"));

  //Serial.println(F("Memory ready"));

  pinMode(7, OUTPUT);

}
void loop() {
  int16_t **data;

  data = (int16_t**)malloc(data_size * sizeof(int16_t*));
  for (int i = 0; i < data_size; i++)
    data[i] = (int16_t*)malloc(3 * sizeof(int16_t));

  int i;
  for (i = 0; i < data_size; i++) {
    digitalWrite(7, HIGH);
    gy.read_data(data[i]);

    digitalWrite(7, LOW);
    delay(333);

  }
  digitalWrite(7, LOW); i = 0;
  for (i = 0; i < data_size; i++) {
    Serial.print(F("Accelerometer: "));
    Serial.print(F("X = ")); Serial.print(data[i][0]);
    Serial.print(F(" | Y = ")); Serial.print(data[i][1]);
    Serial.print(F(" | Z = ")); Serial.print(data[i][2]);
    Serial.print(F(" | i = ")); Serial.println(i);

  }
  while(1){};

}
