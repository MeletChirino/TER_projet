#ifndef Gy521_h
#define Gy521_h
#include <Wire.h>
#include "Arduino.h"

class Gy521 {
  private:
    const uint8_t MPU = 0x68;
    uint8_t _addrs;
  public:
    Gy521();
    Gy521(uint8_t);
    void init();
    void read_data();
    int16_t* accelerometer_data();
    int16_t* gyroscope_data();

    int16_t *Ac;
    int16_t* Gy;
};

#endif
