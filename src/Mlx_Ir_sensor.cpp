#include "Mlx_Ir_sensor.h"
#include <Arduino.h>
// Method definitions

// Konstruktor

/*
MLX90614::MLX90614(uint8_t mlx_addr_val): mlx_addr{mlx_addr_val}
{
}
*/

/****************************************
    Begin MLX90614 communication
*****************************************/
/*
bool MLX90614::begin(void)
{
  //Inicialize SMBus as arduino master
  Wire.begin();
  return true;
}
*/
/***************************************************
  Read device addres from addres register
****************************************************/

uint8_t MLX90614::readDeviceAddr(uint8_t current_device_addr)
{
  uint16_t val = read16bit(MLX90614_ADDR, current_device_addr);
  uint8_t device_addr = val & 0x00FF;

  return device_addr;
}

/***************************************************
  Read ambient temperature in deg Celsius
****************************************************/

float MLX90614::readAmbientTemp(uint8_t device_addr)
{
  // Read raw data from sensor register
  uint16_t raw_data = read16bit(MLX90614_TA, device_addr);

  // Convert data to degress
  float ambient_temp = (raw_data * 0.02) - 272.15;

  return ambient_temp;

}

/***************************************************
  Read object temperature in deg Celsius
****************************************************/

float MLX90614::readObjectTemp(uint8_t device_addr)
{
  // Read raw data from sensor register
  uint16_t raw_data = read16bit(MLX90614_TOBJ1, device_addr);

  // Convert data to degress
  float ambient_temp = (raw_data * 0.02) - 272.15;

  return ambient_temp;

}


/***************************************************
      Write new I2C addr to  MLX90614
      after succesful writing power cycle MLX
****************************************************/

bool MLX90614::writeDeviceAddr(uint16_t _addr, uint8_t device_addr)
{

    write16bit(MLX90614_ADDR, device_addr, 0); // erase
    delay(10);

    // Write new addres
    write16bit(MLX90614_ADDR, device_addr,_addr);
    return true;

}

/***************************************************
          Read 16 bit data from sensor
****************************************************/

uint16_t MLX90614::read16bit(uint8_t _reg, uint8_t device_addr)
{
  uint16_t val;

  // Send addr of requested mlx register

  // Begin transmission
  Wire.beginTransmission(device_addr);
  Wire.write(_reg);
  Wire.endTransmission(false);

  // Read data from required register
  Wire.requestFrom(device_addr, (size_t) 3);
  val = Wire.read();  // First byte
  val |= Wire.read() << 8;  // Second byte

  uint8_t pec = Wire.read();

  return val;
}

/***************************************************
          Write 16 bit data from sensor
****************************************************/

void MLX90614::write16bit(uint8_t _reg, uint8_t device_addr, uint16_t v)
{
  uint8_t pec;
  uint8_t pecbuf[4];

  pecbuf[0] = device_addr << 1;
  pecbuf[1] = _reg;
  pecbuf[2] = v & 0xff;
  pecbuf[3] = v >> 8;
  pec = crc8(pecbuf, sizeof pecbuf);


  Wire.beginTransmission(device_addr);
  Wire.write(_reg);
  Wire.write(v & 0xff);
  Wire.write(v >> 8);
  Wire.write(pec);
  Wire.endTransmission(true);

}

/***************************************************
              CRC parity check
****************************************************/

byte MLX90614::crc8(byte *addr, byte len)
// The PEC calculation includes all bits except the START, REPEATED START, STOP,
// ACK, and NACK bits. The PEC is a CRC-8 with polynomial X8+X2+X1+1.
{
  byte crc = 0;
  while (len--) {
    byte inbyte = *addr++;
    for (byte i = 8; i; i--) {
      byte carry = (crc ^ inbyte) & 0x80;
      crc <<= 1;
      if (carry)
        crc ^= 0x7;
      inbyte <<= 1;
    }
  }
  return crc;
}
