#include "pcf8574t_i2c.h"

/* ----------------------------------------------------------------------- *
 * Title:         pcf8574-lcd-demo                                         *
 * Description:   C-code for PCF8574T backpack controlling LCD through I2C *
 *                Tested on Raspberry Pi 3                                 *
 *                20180203 frank4dd                                        *
 *                                                                         *
 * Prerequisites: apt-get libi2c-dev i2c-tools                             *
 * Compilation:   gcc pcf8574-lcd-demo.c -o pcf8574-lcd-demo               *
 *------------------------------------------------------------------------ *
 * PCF8574T backpack module uses 4-bit mode, LCD pins D0-D3 are not used.  *
 * backpack module wiring:                                                 *
 *                                                                         *
 *  PCF8574T     LCD                                                       *
 *  ========     ======                                                    *
 *     P0        RS                                                        *
 *     P1        RW                                                        *
 *     P2        Enable                                                    *
 *     P3        Led Backlight                                             *
 *     P4        D4                                                        *
 *     P5        D5                                                        *
 *     P6        D6                                                        *
 *     P7        D7                                                        *
 *                                                                         *
 * I2C-byte: D7 D6 D5 D4 BL EN RW RS                                       *
 * ----------------------------------------------------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <ctype.h>

static int i2cFile;

/**
 * @brief write_cmd
 * @param byte  The command to be writen in the IR register
 * @return On success: number of bytes written, On failure: error code
 */
static int32_t write_cmd(const  uint8_t byte)
{
    ssize_t ret = 0;
    uint8_t data[1]={byte | 0x04};

    ret = write(i2cFile,data,sizeof (data));
    if(ret < 0)
    {
        perror("[write_cmd--->write]:");
        return ret;
    }

    usleep(1000);
    data[0] = byte | 0x00;
    ret += write(i2cFile,data,sizeof (data));
    usleep(500);
    return ret;
}

/**
 * @brief lcd_write_data
 * @param c
 * @return
 */
static int32_t lcd_write_data(const uint8_t data)
{
    int32_t ret = 0;
    uint8_t buf[1]={(uint8_t)(data<<4) | 0x0D};

    ret = write(i2cFile,buf,sizeof (buf));
    if(ret < 0)
    {
        perror("[lcd_write_data-->open]:");
        return ret;
    }

    usleep(400);
    buf[0] = (uint8_t)((data<<4) | 0x09);
    ret  += write(i2cFile,buf,sizeof (buf));
    usleep(400);

    return  ret;
}

/**
 * @brief lcd_init  intitialize the i2c device for the lcd
 * @param i2c_dev
 * @return the file descriptor of the lcd i2c device on success, returne error code on fail.
 */
int32_t lcd_init(const char * i2c_dev, const uint16_t dev_addr)
{
    int32_t ret = 0;
    int32_t i2c_file = open(i2c_dev, O_RDWR);
    if(i2c_file <0)
    {
        perror("lcd_init_open:");
        return i2c_file;
    }

    ret = ioctl(i2c_file, I2C_SLAVE, dev_addr);
    if(ret < 0)
    {
        perror("[lcd_init_ioctl]:");
        return ret;
    }
    i2cFile = i2c_file;

    // first init in 8 bit mode
    write_cmd(LCD_8bit);
    write_cmd(LCD_8bit);
    write_cmd(LCD_8bit);
    // then in 4 bit mode
    write_cmd(LCD_4bit);
    write_cmd(LCD_4bit);
    // setup lines and char sizes
    write_cmd(LCD_2X5x8);
    //off
    write_cmd(LCD_LSB);
    write_cmd(LCD_2X5x8);

    write_cmd(LCD_LSB);
    write_cmd(LCD_MODE_INC | LCD_SHIFT_ON|LCD_DISP_ON);

    return i2c_file;
}

/**
 * @brief lcd_close     close lcd file descriptor
 * @param lcd_fd        the lcd i2c file descriptor
 * @return              N/A
 */
int32_t lcd_close(int32_t lcd_fd)
{
    return close(lcd_fd);
}


/**
 * @brief lcd_clear
 * @param lcd_fd
 * @return
 */
int32_t lcd_clear(int32_t lcd_fd)
{
    if (lcd_fd < 0)
    {
        return -1;
    }


//    write_cmd(LCD_LSB);
//    write_cmd(LCD_CLR);

//    write_cmd(LCD_LSB);
//    write_cmd(LCD_CUR_ON|LCD_BLINK_ON|LCD_DISP_ON);

//    write_cmd(LCD_LSB);
//    write_cmd(LCD_CLR);


}

int32_t lcd_putc(const char c)
{
    int8_t n1 = c >>4;
    int8_t n2 = c&0x0F;
    fprintf(stderr,"%d:%d\n",n1,n2);


    lcd_write_data(n1);
    lcd_write_data(n2);


}

int32_t lcd_puts(const char *const str,uint8_t lcd_line)
{
    lcd_go_line(lcd_line);

    for(size_t i = 0; isprint(str[i]); i++)
    {
        lcd_putc(str[i]);
    }
}

int32_t lcd_go_line(const uint8_t lcd_line)
{
    write_cmd(lcd_line);
    write_cmd(0x00);

}
