/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
int red_light_pin = 9;
int green_light_pin = 10;
int blue_light_pin = 11;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(9, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  RGB_color_set("blue");
  delay(1000);
  RGB_color_set("yellow");
  delay(1000);
  RGB_color_set("green");
  delay(1000);
}

void RGB_color_set(String color)
{
  if (color == "red")
    RGB_color(255, 0, 0); // Red
  else if (color == "green")
    RGB_color(0, 255, 0); // Green
  else if (color == "blue")
    RGB_color(0, 0, 255); // Blue
  else if (color == "rasoberry")
    RGB_color(255, 255, 125); // Raspberry
  else if (color == "cyan")
    RGB_color(0, 255, 255); // Cyan
  else if (color == "magenta")
    RGB_color(255, 0, 255); // Magenta
  else if (color == "yellow")
    RGB_color(255, 255, 0); // Yellow
  else if (color == "white")
    RGB_color(255, 255, 255); // White
}

void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
{
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
