#ifndef RGBLed_h
#define RGBLed_h

class RGBLed{
	private:
		int _pinRed, _pinGreen, _pinBlue;
		int _red, _green, _blue;
	public:
		RGBLed(int, int, int);
		void init();
		void set_color(int, int, int);
		void set_blue();
		void set_yellow();
		void set_green();
		void set_red();
		void lights_on();
		void blink_red(int);
		void test();
};

#endif
