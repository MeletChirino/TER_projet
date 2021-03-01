#include "Arduino.h"
#include "RGBLed.h"

RGBLed::RGBLed(int pinRed, int pinGreen, int pinBlue){
	//constructor
	_pinRed = pinRed;
	_pinGreen = pinGreen;
	_pinBlue = pinBlue;
}
void RGBLed::init(){
	pinMode(_pinRed, OUTPUT);
	pinMode(_pinGreen, OUTPUT);
	pinMode(_pinBlue, OUTPUT);
}
void RGBLed::lights_on(){
	analogWrite(_pinRed, _red);
	analogWrite(_pinGreen, _green);
	analogWrite(_pinBlue, _blue);
}
void RGBLed::set_color(int red, int green, int blue){
	_red = red;
	_green = green;
	_blue = blue;
	analogWrite(_pinRed, red);
	analogWrite(_pinGreen, green);
	analogWrite(_pinBlue, blue);
	//lights_on();
}
void RGBLed::set_blue(){
	set_color(0, 0, 245);
}
void RGBLed::set_red(){
	set_color(254, 0, 0);
}
void RGBLed::set_green(){
	set_color(0, 254, 0);
}
void RGBLed::set_yellow(){
	set_color(254, 254, 0);
}
void RGBLed::blink_red(int times){
	int delay_ = 200;
	for (int i = 0; i < times; i++)
	{
		set_red();
		delay(delay_);
		set_blue();
		delay(delay_);
	}
}
void RGBLed::test(){
	Serial.print("Pines ");
	Serial.print("R =");Serial.print(_pinRed);
	Serial.print("G = ");Serial.print(_pinGreen);
	Serial.print("B = ");Serial.print(_pinBlue);
	int delay_ = 1000;
	set_yellow();
	delay(delay_);
	set_blue();
	delay(delay_);
	set_red();
	delay(delay_);
	set_green();
	delay(delay_);
}
