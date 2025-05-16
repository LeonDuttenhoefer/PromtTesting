#ifndef I2C_MODULE_H
#define I2C_MODULE_H

#include <stdint.h>

void i2c_init(uint8_t i2c_port, uint32_t clock_speed);
int i2c_write(uint8_t i2c_port, uint8_t device_address, const uint8_t* data, uint16_t length);
int i2c_read(uint8_t i2c_port, uint8_t device_address, uint8_t* data, uint16_t length);

#endif // I2C_MODULE_H
