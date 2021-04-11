//----------------- IR receiver config -----------------
#include "IrReceiver.h"
/* infrared receiver pin */
int ir_capture_pin = 14;
IrReceiver ir_receiver(ir_capture_pin);
//----------------- IR receiver config -----------------

//----------------- Grip sensor config -----------------
#include "GripSensor.h"
/* position pins */
GripSensor ldr_sensor(7, 8);
//----------------- Grip sensor config -----------------

//----------------- Buzzer config -----------------
#include "Buzzer.h"
/* buzzer config */
Buzzer buzz(6);//this is pin number of buzzer
//----------------- Buzzer config -----------------

//----------------- RGB Led config -----------------
#include "RGBLed.h"
/* pins for RGB Led */
RGBLed led_rgb(
  11,//red
  9,//green
  10,//blue
  buzz.buzzer_pin
);
//----------------- RGB Led config -----------------

//----------------- Race stats -----------------
/*
  A simple matrix that holds some stats of the race:
  t1 -> time to arrive to transition zone
  t2 -> time inside transmission zone before the relay
  t3 -> time inside transmission zone after relay
  relay_state -> it says whether this relay was good or not
  [t1, t2, t3, relay_state]
  it can hold up to 6 relays in this version, can be upgraded if needed
*/
float relay_stats[4][6];

//this variable saves if any grip errorr is made
float grip_errors[40];
/* transition zone flag */
bool transition_zone = false;
//----------------- Race stats -----------------

//----------------- Serial parameters -----------------
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
//----------------- Serial parameters -----------------



void setup() {
  // initialize serial:
  Serial.begin(115200);

  // reserve 200 bytes for the inputString:
  inputString.reserve(200);

  //initialize buzzer
  buzz.init();

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
    buzz.stop();
    //while not in transition zone
    ldr_sensor.read_grip();
    ldr_sensor.print_status(transition_zone);

    if (ldr_sensor.grip_ok())
      led_rgb.set_red();
    else
      led_rgb.set_blue();

    if (ir_receiver.get_status()) {
      transition_zone = true;
      buzz.melody_time = millis();
      delay(200);
    }
  }

  while (transition_zone) {
    //while in transition zone
    ldr_sensor.print_status(transition_zone);

    if (ldr_sensor.good_relay()) {

      led_rgb.set_green();
      buzz.victory();
    } else {
      buzz.transition_zone();
      led_rgb.set_yellow();
    }
    if (ir_receiver.get_status()) {
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
void buzzer_beep(int delay_, int tone_) {
  analogWrite(6, tone_);
  delay(delay_);
  digitalWrite(6, 0);

}
