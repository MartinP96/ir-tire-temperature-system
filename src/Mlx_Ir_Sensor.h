#ifndef _MLX_IR_SENSOR
#define _MLX_IR_SENSOR

#include <Wire.h>
#include <Arduino.h>

//#include "IR_Tire_System.h"

// MLX 90614 Register Addresses
//EEPROM R/W
#define MLX90614_TOMAX        0x20
#define MLX90614_TOMIN        0x21
#define MLX90614_PWMCTRL      0x22
#define MLX90614_TARANGE      0x23
#define MLX90614_EMISSIVITY   0x24
#define MLX90614_CONFIGREG1   0x25
#define MLX90614_ADDR         0x2E
#define MLX90614_ID1
#define MLX90614_ID2
#define MLX90614_ID3
#define MLX90614_ID4

//RAM R only
#define MLX90614_RAWCH1   0x04
#define MLX90614_RAWCH2   0x05
#define MLX90614_TA       0x06
#define MLX90614_TOBJ1    0x07
#define MLX90614_TOBJ2    0x08

#define MLX90614_DEFAULT_ADDR     0x5A


class MLX90614
{
  public:

  // Konstructor
  //MLX90614(uint8_t mlx_addr_val = MLX90614_DEFAULT_ADDR);

  // Methods
  //bool begin(void);

  float readAmbientTemp(uint8_t device_addr);
  float readObjectTemp(uint8_t device_addr);

  uint8_t readDeviceAddr(uint8_t current_device_addr);
  bool writeDeviceAddr(uint16_t _addr, uint8_t device_addr);

  private:
  uint16_t read16bit(uint8_t _reg, uint8_t device_addr);
  void write16bit(uint8_t _reg, uint8_t device_addr, uint16_t v);
  byte crc8(byte *addr, byte len);
};


#endif
