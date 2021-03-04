#include "Gy521.h"
#include "Arduino.h"
#include <Wire.h>

Gy521::Gy521(){
	//normal constructor
	_addrs = MPU;
	_Ac = (int16_t*)malloc(3*sizeof(int16_t));
	_Gy = (int16_t*)malloc(3*sizeof(int16_t));
	
}
Gy521::Gy521(uint8_t addrs){
	//in case gyroscope uses a diferent addrs
	_addrs = addrs;
}

void Gy521::init(){
	Wire.beginTransmission(_addrs);
	Wire.write(0x6b);
	Wire.write(0);
	Wire.endTransmission(true);
}
void Gy521::read_data(int16_t *data){
	Wire.beginTransmission(_addrs);
	Wire.write(0x3B);
	Wire.endTransmission(false);
	Wire.requestFrom(_addrs, 12, true);
	_Ac[0] = Wire.read()<<8|Wire.read();
	_Ac[1] = Wire.read()<<8|Wire.read();
	_Ac[2] = Wire.read()<<8|Wire.read();
	_Gy[0] = Wire.read()<<8|Wire.read();
	_Gy[1] = Wire.read()<<8|Wire.read();
	_Gy[2] = Wire.read()<<8|Wire.read();
	data[0] = _Ac[0];
	data[1] = _Ac[1];
	data[2] = _Ac[2];

}
int16_t* Gy521::accelerometer_data(){
	return _Ac;
}
int16_t* Gy521::gyroscope_data(){
	return _Gy;
}

