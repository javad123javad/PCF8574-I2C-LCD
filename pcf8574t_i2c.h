#ifndef PCF8574T_I2C_H
#define PCF8574T_I2C_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
/*******************************************************
 * PCF8574 pin map
 * P0 <---> RS
 * P1 <---> RW
 * P2 <---> E
 * P4 <---> D4
 * P5 <---> D5
 * P6 <---> D6
 * P7 <---> D7
 *
 *
 */

typedef enum _LCD_CMD{
    LCD_4bit        = 0x20,
    LCD_8bit        = 0x30,
    LCD_1x5x8       = 0x00,
    LCD_LSB         = 0x08,
    LCD_1X5x11      = 0x40,
    LCD_2X5x8       = 0x80,
    LCD_2X5x11      = 0x84,
    LCD_DISP_ON     = 0xC0,
    LCD_CUR_ON      = 0xA0,
    LCD_BLINK_ON    = 0x90,
    LCD_CLR         = 0x18,
    LCD_MODE_DEC    = 0x00,
    LCD_MODE_INC    = 0x20,
    LCD_SHIFT_ON    = 0x10

} LCD_CMD;

typedef enum  _LCD_LINE
{
    LCD_L1      = 0x80,
    LCD_L2      = 0xC0,
    LCD_L3      = 0x90,
    LCD_L4      = 0xD0
}LCD_LINE;

int32_t lcd_init(const char * i2c_dev, const uint16_t dev_addr);
int32_t lcd_close(int32_t lcd_fd);
int32_t lcd_clear(int32_t lcd_fd);
int32_t lcd_putc(const int32_t lcd_fd, const char c);
int32_t lcd_go_line(const int32_t lcd_fd, const uint8_t lcd_line);
int32_t lcd_puts(const int32_t lcd_fd, const char *const str, const uint8_t lcd_line);

#endif // PCF8574T_I2C_H
