#include "pcf8574t_i2c.h"

int main()
{
    int i2c_fd = 0;
    i2c_fd = lcd_init("/dev/i2c-0");
    if(i2c_fd > 0)
        lcd_close(i2c_fd);

    return 0;
}

