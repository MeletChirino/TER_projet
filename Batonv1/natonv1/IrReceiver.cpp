#include "Arduino.h"
#include "IrReceiver.h"

IrReceiver::IrReceiver(int pin){
  //constructor
  _pin = pin;
}
void IrReceiver::init(){
  pinMode(_pin, INPUT);
}
bool IrReceiver::get_status(){
  bool status_;
  status_ = !digitalRead(_pin);
  return status_;
}
