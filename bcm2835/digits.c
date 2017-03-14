#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include "bcm2835.h"

static const uint8_t segments[] = { 
 /* DP,  G,  F,  E,  D,  C,  B,  A */
    25, 18,  9,  7,  8, 23, 17, 11 
};

static const uint8_t digits[] = { 
 /* D1, D2, D3, D4 */
    10, 22, 27, 24
};

static const uint8_t char_map[] =
{   /* A, B, C, D, E, F, G, DP */
    0xfc, /* 1111 1100 = 0 */
    0x60, /* 0110 0000 = 1 */
    0xda, /* 1101 1010 = 2 */
    0xf2, /* 1111 0010 = 3 */
    0x66, /* 0110 0110 = 4 */
    0xb6, /* 1011 0110 = 5 */
    0xbe, /* 1011 1110 = 6 */
    0xe0, /* 1110 0000 = 7 */
    0xfe, /* 1111 1110 = 8 */
    0xf6, /* 1111 0110 = 9 */
    0x00, /* 0000 0000 = BLANK */
};

char display_board[8];

void *display(void *dummy)
{
    uint8_t digit, segment;
    uint8_t index, c;
    struct timespec sleeper;

    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 5500000L;

    for(;;)
    {
        for(digit = 0; digit < 4; digit++)
        {
            c = display_board[digit];
            if((c >= '0') && (c <= '9'))
                index = c - '0';
            else
                index = 10;

            for(segment = 0; segment < 8 ; segment++)
            {
                /* sizeof(uint8_t) = 7 */
                if((char_map[index] & (0x1 << segment)))
                    bcm2835_gpio_clr(segments[segment]);
                else
                    bcm2835_gpio_set(segments[segment]);
            }
            bcm2835_gpio_set(digits[digit]);
            nanosleep(&sleeper, NULL);
            bcm2835_gpio_clr(digits[digit]);
        } 
    }
}

void init_display(void)
{
    uint8_t i;
    pthread_t display_thread; 

    for(i = 0; i < 8; i++)
        bcm2835_gpio_fsel(segments[i], BCM2835_GPIO_FSEL_OUTPUT);

    for(i = 0; i < 4; i++)
        bcm2835_gpio_fsel(digits[i], BCM2835_GPIO_FSEL_OUTPUT);

    sprintf(display_board, "    ");
    
    if(pthread_create(&display_thread, NULL, display, NULL) != 0)
        printf("Thread create failed: %s\n", strerror(errno));
}

void *pclock(void *dummy)
{
    struct timespec sleeper;
    struct tm *t;
    time_t now;

    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 200000000L;
    for(;;)
    {
        now = time(NULL);
        t = localtime(&now); 
        sprintf(display_board, "%02d%02d", t->tm_min, t->tm_sec);
        nanosleep(&sleeper, NULL);
    }
}

void init_clock(void)
{
    pthread_t clock_thread;
    if(pthread_create(&clock_thread, NULL, pclock, NULL) != 0)
        printf("Thread create failed: %s\n", strerror(errno));
}

int main(int argc, char **argv)
{
    struct timespec sleeper;

    bcm2835_init();
    init_display();
    init_clock();

    sleeper.tv_sec = 10;
    sleeper.tv_nsec = 0L;
    for(;;)
        nanosleep(&sleeper, NULL);

    return 0;
}
