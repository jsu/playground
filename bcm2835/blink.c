#include <time.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

#include "bcm2835.h"

void signal_handler(int signum)
{
    bcm2835_gpio_set(BCM2835_GPCLR0, 0xffffffff);
    bcm2835_close();
    exit(0);
}

int main (void)
{
    struct timespec sleeper;
    uint8_t i, led[] = {21, 26, 19, 13};
    uint32_t leds[] = {
        0x04282000,
        0x00280000,
        0x04002000,
        0x04080000,
        0x00202000,
        0x04282000,
    };

    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGSTOP, signal_handler);

    bcm2835_init();

    for(i = 0; i < 4 ; i++)
        bcm2835_gpio_fsel(led[i], BCM2835_GPIO_FSEL_OUTPUT);

    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 500000000L;


    for(i = 0; i < 5; i++)
    {
        bcm2835_gpio_set(BCM2835_GPSET0, leds[i]);    
        nanosleep(&sleeper, NULL);
        bcm2835_gpio_set(BCM2835_GPCLR0, 0xffffffff);
    }  

    printf("0x%08x, %d\n", BCM2835_GPSET0, BCM2835_GPSET0 / 4);

    bcm2835_close();
    return 0;
}
