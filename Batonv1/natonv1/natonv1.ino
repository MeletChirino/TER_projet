#include "RGBLed.h"
#include "IrReceiver.h"
#include "GripSensor.h"

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
GripSensor ldr_sensor(7,14);

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete


void setup() {
  // initialize serial:
  Serial.begin(115200);
  
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  // initialize RGBPins
  led_rgb.init();
  led_rgb.test();

  // Initialize interrupt service routine
  ir_receiver.init();


  // initialize position detector pins
  ldr_sensor.init();
}

void loop() {

  while (!transition_zone) { 
    //while not in transition zone
    ldr_sensor.read_grip();
    ldr_sensor.print_status(transition_zone);  

    if (ldr_sensor.grip_ok())
      led_rgb.set_red();
    else
      led_rgb.set_blue();

    if(ir_receiver.get_status()){
      transition_zone = true;
      delay(200);
      }   
  }

  while (transition_zone) {
    //while in transition zone
    ldr_sensor.print_status(transition_zone);  
    
    if (ldr_sensor.good_relay())
      led_rgb.set_green();
    else
      led_rgb.set_yellow();

    if(ir_receiver.get_status()){
      ldr_sensor.reset_relay(led_rgb);
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
