#include <math.h>

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
bool send_data = false;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(13, OUTPUT);
}
void loop() { 
  if (inputString == "ok?\n") Serial.println("ok");
  if (inputString == "start\n") {
    //Serial.println("toogle transmisison");
    if (send_data) send_data = 0;
    else send_data = 1;
    //Serial.println("send_data != send_data");
  }
  
  if (send_data) capture_data();
  
  if (stringComplete) {
    //Serial.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  delay(1);
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  //Serial.write("ok\n");
  //serial_blink(5, 300);
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
