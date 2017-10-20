#include <bcm2835.h>
#include <stdio.h>
#include <time.h>

void lcd_cmd(uint8_t cmd)
{
    char buffer[1];
    struct timespec sleeper;
    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 2000000L;

    buffer[0] = cmd & 0xf0;
    buffer[0] |= 0x04;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);
    nanosleep(&sleeper, NULL);
    buffer[0] &= 0xfb;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);

    buffer[0] = (cmd & 0x0f) << 4;
    buffer[0] |= 0x04;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);
    nanosleep(&sleeper, NULL);
    buffer[0] &= 0xfb;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);
}

void lcd_put(char data)
{
    char buffer[1];
    struct timespec sleeper;
    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 2000000L;

    buffer[0] = data & 0xf0;
    buffer[0] |= 0x05;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);
    nanosleep(&sleeper, NULL);
    buffer[0] &= 0xfb;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);

    buffer[0] = (data & 0x0f) << 4;
    buffer[0] |= 0x05;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);
    nanosleep(&sleeper, NULL);
    buffer[0] &= 0xfb;
    buffer[0] |= 0x08;
    bcm2835_i2c_write(buffer, 1);
}

void move_cursor(int x, int y)
{
    lcd_cmd(0x80 + 0x40 * y + x);
}

void init_lcd()
{
    struct timespec sleeper;
    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 5000000L;
    lcd_cmd(0x33); /* Init 8-line mode, required */
    nanosleep(&sleeper, NULL);
    lcd_cmd(0x32); /* Init 4-line mode now */
    nanosleep(&sleeper, NULL);
    lcd_cmd(0x28); /* 2 lines w/ 5*7 dots */
    nanosleep(&sleeper, NULL);
    lcd_cmd(0x0c); /* Enable display without cursor */
    nanosleep(&sleeper, NULL);
    lcd_cmd(0x01); /* Clear screen */
    nanosleep(&sleeper, NULL);
}

void lcd_str(char *str)
{
    char c;
    while((c = *str++) != '\0')
        lcd_put(c);
}

int main(int argc, char **argv)
{
    /* init i2c */
    if(!bcm2835_init()) return 1;
    if(!bcm2835_i2c_begin()) return 1;
    bcm2835_i2c_setSlaveAddress(0x27);

    init_lcd();

    move_cursor(0, 0);
    lcd_str("This is");
    move_cursor(0, 1);
    lcd_str("   controlled by");
    move_cursor(20, 0);
    lcd_str(" libbcm2835");
    move_cursor(20, 1);
    lcd_str("              Jay Su");

    /* end i2c */
    bcm2835_i2c_end();
    bcm2835_close();
}
