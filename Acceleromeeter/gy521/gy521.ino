#include <Wire.h>
#include "Gy521.h"

Gy521 gy = Gy521();
int16_t *Ac, *Gy;


void setup(){
  Serial.begin(9600);
  gy.init();
  Ac = (int16_t*)malloc(3*sizeof(int16_t));
  Gy = (int16_t*)malloc(3*sizeof(int16_t));

}
void loop(){
  gy.read_data();

  Ac = gy.accelerometer_data();
  Serial.print("Accelerometer: ");
  Serial.print("X = "); Serial.print(Ac[0]);
  Serial.print(" | Y = "); Serial.print(Ac[1]);
  Serial.print(" | Z = "); Serial.println(Ac[2]); 

  Gy = gy.gyroscope_data();
  Serial.print("Gyroscope: ");\
  Serial.print("X = "); Serial.print(Gy[0]);
  Serial.print(" | Y = "); Serial.print(Gy[1]);
  Serial.print(" | Z = "); Serial.println(Gy[2]);
  Serial.println(" ");
  delay(333);
}
