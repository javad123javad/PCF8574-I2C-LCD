/*******************************************************
 * @Desc: PCF8574 I2C library
 * @Author: Javad Rahimi (javad321javad@gmail.com)
 * @Data: Feb,14,2022
 *
 * PCF8574 pin map
 * P0 <---> RS
 * P1 <---> RW
 * P2 <---> E
 * P3 <---> Back Light
 * P4 <---> D4
 * P5 <---> D5
 * P6 <---> D6
 * P7 <---> D7
 *
 ********************************************************/
#include "pcf8574t_i2c.h"
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
static int32_t write_cmd(const int32_t i2c_fd, const  uint8_t byte)
{
    ssize_t ret = 0;
    uint8_t data[1]={byte | 0x04};

    ret = write(i2c_fd,data,sizeof (data));
    if(ret < 0)
    {
        perror("[write_cmd--->write]:");
        return ret;
    }

    usleep(1000);
    data[0] = byte | 0x00;
    ret += write(i2c_fd,data,sizeof (data));
    usleep(500);
    return ret;
}

/**
 * @brief lcd_write_data
 * @param c
 * @return
 */
static int32_t lcd_write_data(const int32_t lcd_fd, const uint8_t data)
{
    int32_t ret = 0;
    uint8_t buf[1]={(uint8_t)(data<<4) | 0x0D};

    ret = write(lcd_fd,buf,sizeof (buf));
    if(ret < 0)
    {
        perror("[lcd_write_data-->open]:");
        return ret;
    }

    usleep(400);
    buf[0] = (uint8_t)((data<<4) | 0x09);
    ret  += write(lcd_fd,buf,sizeof (buf));
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
    write_cmd(i2c_file, LCD_8bit);
    write_cmd(i2c_file, LCD_8bit);
    write_cmd(i2c_file, LCD_8bit);
    // then in 4 bit mode
    write_cmd(i2c_file, LCD_4bit);
    write_cmd(i2c_file, LCD_4bit);
    // setup lines and char sizes
    write_cmd(i2c_file, LCD_2X5x8);
    //off
    write_cmd(i2c_file, LCD_LSB);
    write_cmd(i2c_file, LCD_2X5x8);

    write_cmd(i2c_file, LCD_LSB);
    write_cmd(i2c_file, LCD_MODE_INC | LCD_SHIFT_ON|LCD_DISP_ON);

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
 * @brief lcd_clear Clears the whole LCD
 * @param lcd_fd    lcd_i2c file descriptor
 * @return          Error code on Failure.
 */
int32_t lcd_clear(int32_t lcd_fd)
{
    int32_t ret = 0;

    ret = write_cmd(lcd_fd, LCD_LSB);
    if ( ret < 0)
    {
        return ret;
    }
    ret = write_cmd(lcd_fd, LCD_CLR);
    return ret;
}

/**
 * @brief lcd_putc
 * @param lcd_fd    lcd i2c file descriptor
 * @param c         charactor to display on LCD
 * @return          On success: number of bytes written, On failure: error code
 */
int32_t lcd_putc(const int32_t lcd_fd, const char c)
{
    int32_t ret = 0;

    ret = lcd_write_data(lcd_fd, c >>4);
    if(ret < 0)
    {
        return ret;
    }

    ret = lcd_write_data(lcd_fd, c&0x0F);
    return ret;
}

/**
 * @brief lcd_puts  print string on the LCD
 * @param lcd_fd    lcd ic2 file descriptor
 * @param str       string to be written on the LCD
 * @param lcd_line  the line number where the LCD should be displayed. (LCD_L1, LCD_L2, etc...)
 * @return          On success: Positive value, On Failure: Error code.
 */
int32_t lcd_puts(const int32_t lcd_fd, const char *const str,uint8_t lcd_line)
{
    int32_t ret = 0;
    ret = lcd_go_line(lcd_fd, lcd_line);
    if(ret < 0)
    {
        return ret;
    }

    for(size_t i = 0; isprint(str[i]); i++)
    {
        ret = lcd_putc(lcd_fd, str[i]);
        if(ret < 0)
            break;
    }
    return ret;
}

/**
 * @brief lcd_go_line   Place the cursor on the specified line
 * @param lcd_fd        i2c lcd file descriptor
 * @param lcd_line      The Line number (LCD_L1, LCD_L2, etc...)
 * @return              On success: Positive value, On Failure: Error code.
 */
int32_t lcd_go_line(const int32_t lcd_fd, const uint8_t lcd_line)
{
    int32_t ret = 0;
    ret = write_cmd(lcd_fd, lcd_line);
    if (ret < 0)
    {
        return ret;
    }

    ret = write_cmd(lcd_fd, 0x00);
    return ret;
}
