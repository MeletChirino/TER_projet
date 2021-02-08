String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

/* pins for RGB Led */
int red_light_pin = 9;
int green_light_pin = 11;
int blue_light_pin = 10;

/* infrared receiver pin */
int ir_receiver = 2;

/* transition zone flag */
bool transition_zone = false;

/* position pins */
int low_position = 3;
int high_position = 4;
bool good = false;

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(13, OUTPUT);

  // initialize RGBPins
  pinMode(blue_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(red_light_pin, OUTPUT);

  // Initialize interrupt service routine
  pinMode(ir_receiver, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ir_receiver), change_zone, RISING);

  // initialize position detector pins
  pinMode(low_position, INPUT_PULLUP);
  pinMode(high_position, INPUT_PULLUP);

}

void loop() {

  bool low_position_grip;
  bool high_position_grip;
  bool low_position_change, high_position_change;
  if (!good)
    blink_red();

  while (!transition_zone) {
    good = false;
    low_position_grip = digitalRead(low_position);
    high_position_grip = digitalRead(high_position);

    Serial.print("Transition zone = "); Serial.println(transition_zone);

    if (low_position_grip && high_position_grip || (!low_position_grip && !high_position_grip))
      RGB_color_set("red");
    else
      RGB_color_set("blue");
  }

  while (transition_zone) {
    Serial.print("Transition zone = "); Serial.println(transition_zone);
    if (good)
      RGB_color_set("green");

    if (low_position_grip && !good) {
      low_position_change = digitalRead(low_position);
      high_position_change = digitalRead(high_position);

      if (high_position_change && !low_position_change) {
        good = true;
      } else {
        RGB_color_set("yellow");
      }
    }
    if (high_position_grip && !good) {
      low_position_change = digitalRead(low_position);
      high_position_change = digitalRead(high_position);
      if (!high_position_change && low_position_change) {
        good = true;
      } else {
        RGB_color_set("yellow");
      }

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
