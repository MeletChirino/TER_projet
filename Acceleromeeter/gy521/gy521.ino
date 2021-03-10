#include <Wire.h>
#include "Gy521.h"

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool send_data = false;
bool full = false;

Gy521 gy = Gy521();

int data_size = 100;

void setup() {
  Serial.begin(115200);
  inputString.reserve(200);
  //Serial.println(F("Serial Ready"));
  gy.init();
  //Serial.println(F("Gy ready"));

  //Serial.println(F("Memory ready"));

  pinMode(7, OUTPUT);

}
void loop() {
  int data[data_size];
  double times[data_size];
  bool dame = false;
  if (!full) {
    for (int i = 0; i < data_size; i++) {
      digitalWrite(7, HIGH);
      gy.read_data();
      data[i] = gy.Ac[0];
      times[i] = millis();

      digitalWrite(7, LOW);
      delay(333);

    }
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7,LOW);
    //Serial.println(F(" loop"));
    full = true;
  }
  if (send_data) {
    for (int i = 0; i < data_size; i++) {

      Serial.print(data[i]);
      Serial.print("/");
      Serial.println(times[i]);
    }
    send_data = 0;
  }

  if (inputString == "ok?\n") Serial.println("ok");
  if (inputString == "start\n") {
    //Serial.println("toogle transmisison");
    if (send_data) send_data = 0;
    else send_data = 1;
    //Serial.println("send_data != send_data");
  }
  if (stringComplete) {
    //Serial.print("STR COMPLETE\n");
    //Serial.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  delay(1);

}

void serialEvent() {
  //Serial.write("SE:\n");
  //serial_blink(6, 300);
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    //Serial.println(inputString);
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void serial_blink(int times, int delay_) {
  for (int i = 0; i < times; i++) {
    digitalWrite(7, HIGH);
    delay(delay_);
    digitalWrite(7, LOW);
    delay(delay_);
  }
}
