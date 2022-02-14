#include "pcf8574t_i2c.h"

int main()
{
    int i2c_fd = 0;
    i2c_fd = lcd_init("/dev/i2c-0", 0x27);
    if(i2c_fd > 0)
    {
        lcd_clear(i2c_fd);
        lcd_puts("Hello",LCD_L1);
        lcd_puts("Hello",LCD_L2);
        lcd_puts("Hello",LCD_L3);
        lcd_puts("Hello",LCD_L4);
        lcd_puts("Hel",LCD_L1);


    }
        lcd_close(i2c_fd);

    return 0;
}

