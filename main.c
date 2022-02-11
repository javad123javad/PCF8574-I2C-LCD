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
#include "pcf8574t_i2c.h"

