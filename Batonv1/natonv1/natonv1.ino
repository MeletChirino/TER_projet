#include "RGBLed.h"
#include "IrReceiver.h"

/* pins for RGB Led */
int red_light_pin = 11;
int green_light_pin = 9;
int blue_light_pin = 10;

RGBLed led_rgb(
  red_light_pin,
  green_light_pin, 
  blue_light_pin
  );
  
/* infrared receiver pin */
int ir_capture_pin = 2;
IrReceiver ir_receiver(ir_capture_pin);

/* transition zone flag */
bool transition_zone = false;

/* position pins */
int low_position = 7;
int high_position = 14;
bool good = false;

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void setup() {
  // initialize serial:
  Serial.begin(115200);
  
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  // initialize RGBPins
  led_rgb.init();

  // Initialize interrupt service routine
  ir_receiver.init();


  // initialize position detector pins
  pinMode(low_position, INPUT_PULLUP);
  pinMode(high_position, INPUT_PULLUP);

}

void loop() {

  bool low_position_grip;
  bool high_position_grip;
  bool low_position_change, high_position_change;
  if (!good)
    led_rgb.blink_red(4);

  while (!transition_zone) { 
    good = false;
    low_position_grip = digitalRead(low_position);
    high_position_grip = digitalRead(high_position);

    Serial.print("Transition zone = "); Serial.println(transition_zone);
    Serial.print("low_position_grip  = "); Serial.println(low_position_grip);
    Serial.print("high_position_grip  = "); Serial.println(high_position_grip);
  

    if (low_position_grip && high_position_grip || (!low_position_grip && !high_position_grip))
      led_rgb.set_red();
    else
      led_rgb.set_blue();

    if(ir_receiver.get_status()){
      transition_zone = true;
      delay(200);
      }
      
  }

  while (transition_zone) {
    Serial.print("Transition zone = "); Serial.println(transition_zone);
    if (good)
      led_rgb.set_green();

    if (low_position_grip && !good) {
      low_position_change = digitalRead(low_position);
      high_position_change = digitalRead(high_position);

      if (high_position_change && !low_position_change) {
        good = true;
      } else {
        led_rgb.set_yellow();
      }
    }
    if (high_position_grip && !good) {
      low_position_change = digitalRead(low_position);
      high_position_change = digitalRead(high_position);
      if (!high_position_change && low_position_change) {
        good = true;
      } else {
        led_rgb.set_yellow();
      }
    }
    if(ir_receiver.get_status()){
      transition_zone = false;
      delay(200);
      }
  }


  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
  //Serial.println(millis());
}

void change_zone() {
  transition_zone = !transition_zone;
  Serial.println("interrupt");
  delay(300);
}



/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent() {
  Serial.println("Serial Event!!\n");
  serial_blink(4, 300);
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
void serial_blink(int times, int delay_) {
  for (int i = 0; i < times; i++) {
    digitalWrite(13, HIGH);
    delay(delay_);
    digitalWrite(13, LOW);
    delay(delay_);
  }
}
