#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include "bcm2835.h"

#define DISPLAY_DELAY_NSEC 6000000L
#define SEGMENT_COUNT 8
#define DIGIT_COUNT 4

static uint8_t _digits[DIGIT_COUNT];
static char display_board[5];
static uint32_t lookup[11], segment_mask;

/*
 * In the order of segments:
 *      A, B, C, D, E, F, G, DP
 */
static const uint8_t char_map[] =
{ 
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

void *display(void *dummy)
{
    uint8_t digit;
    uint8_t index, c;
    struct timespec sleeper;

    sleeper.tv_sec = 0;
    sleeper.tv_nsec = DISPLAY_DELAY_NSEC;

    for(;;)
    {
        for(digit = 0; digit < DIGIT_COUNT; digit++)
        {
            c = display_board[digit];
            if((c >= '0') & (c <= '9'))
                index = c - '0';
            else
                index = 10;

            bcm2835_gpio_set(BCM2835_GPSET0, lookup[index]);
            bcm2835_gpio_pin_set(_digits[digit]);
            nanosleep(&sleeper, NULL);
            bcm2835_gpio_set(BCM2835_GPCLR0, lookup[10]);
            bcm2835_gpio_pin_clr(_digits[digit]);
        } 
    }
}

void seven_segment_display_close(void)
{
    uint8_t i;

    for(i = 0; i < 32; i++)
        if(segment_mask & (0x1 << i))
            bcm2835_gpio_fsel(i, BCM2835_GPIO_FSEL_INPUT);

    for(i = 0; i < DIGIT_COUNT; i++)
        bcm2835_gpio_fsel(_digits[i], BCM2835_GPIO_FSEL_INPUT);
}

char *seven_segment_display_init(const uint8_t *segments, const uint8_t *digits)
{
    uint8_t i, j;
    pthread_t display_thread; 

    bcm2835_init();

    for(i = 0; i < DIGIT_COUNT; i++){
        _digits[i] = digits[i];
        bcm2835_gpio_fsel(_digits[i], BCM2835_GPIO_FSEL_OUTPUT);
    }

    segment_mask = ~(0xffffffff);
    for(i = 0; i < 8; i++)
        segment_mask |= 0x1 << segments[i];
    for(i = 0; i < 11; i++)
    {
        lookup[i] = segment_mask;
        for(j = 0; j < 8; j++)
        {
            bcm2835_gpio_fsel(segments[j], BCM2835_GPIO_FSEL_OUTPUT);
            if(char_map[i] & (0x80 >> j))
                lookup[i] &= ~(0x1 << segments[j]);
        }
    }

    sprintf(display_board, "    ");
    
    if(pthread_create(&display_thread, NULL, display, NULL) != 0)
        printf("Thread create failed: %s\n", strerror(errno));

    return display_board;
}
