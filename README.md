# Yet another I2C LCD library for 16x2 and 16x4 LCDs

I've developed this library for the projects which required interacting with LCD. It's a simple driver for `PCF8574` I/O expander chips.
## Usage
Simply add `pcf8574t_i2c.h` and `pcf8574t_i2c.c` to you project.

## Sample code

```c
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

```
## LICENSE
[GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html)
