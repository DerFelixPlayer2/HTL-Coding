#ifndef __I2C
#define __I2C
#define SDA_PIN PC4
#define SCL_PIN PC5
#define I2C_PORT PORTC

#define SCL_CLOCK 400000UL

#include <Arduino.h>
#include <stdint.h>

void i2c_init();
uint8_t i2c_start(uint8_t byte);
uint8_t i2c_byte(uint8_t byte);
void i2c_stop();
uint8_t i2c_readAck();
uint8_t i2c_readNak();
void i2c_write(uint8_t data);
#endif	// __I2C