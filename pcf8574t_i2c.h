#ifndef PCF8574T_I2C_H
#define PCF8574T_I2C_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t lcd_init(const char * i2c_dev);
int32_t lcd_close(int32_t lcd_fd);


#endif // PCF8574T_I2C_H
