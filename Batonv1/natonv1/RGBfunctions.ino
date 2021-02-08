/* funcitons for RGB LED  */
void RGB_color_set(String color)
{
  /* turn extact color on */
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

void blink_red() {
  int delay_ = 200;
  for (int i = 0; i < 4; i++)
  {
    RGB_color_set("red");
    delay(delay_);
    RGB_color_set("blue");
    delay(delay_);
  }
}
