#include "pcf8574t_i2c.h"
#define LCD_I2C_ADDR   0x27
#define LCD_I2C_DEV    "/dev/i2c-0"
int main()
{
    int i2c_fd = 0;
    i2c_fd = lcd_init(LCD_I2C_DEV, LCD_I2C_ADDR);
    if(i2c_fd > 0)
    {
        lcd_clear(i2c_fd);
        lcd_puts(i2c_fd, "Hello",LCD_L1);
        lcd_puts(i2c_fd, "World",LCD_L2);
        lcd_puts(i2c_fd, "War",LCD_L3);
        lcd_puts(i2c_fd, "Three!",LCD_L4);
    }

    lcd_close(i2c_fd);

    return 0;
}
