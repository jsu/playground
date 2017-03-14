#include <time.h>
#include <stdio.h>
#include "bcm2835.h"

int main(int argc, char **argv)
{
    struct timespec sleeper;
    uint8_t pin;
    uint32_t mask, i;


    pin = 27;

    bcm2835_init();
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTPUT);
    printf("%d\n", bcm2835_gpio_pin_lev_get(pin));
    bcm2835_gpio_pin_set(pin);
    printf("%d\n", bcm2835_gpio_pin_lev_get(pin));

    sleeper.tv_sec = 1;
    sleeper.tv_nsec = 0L;
    nanosleep(&sleeper, NULL);
    bcm2835_gpio_pin_clr(pin);
    printf("%d\n", bcm2835_gpio_pin_lev_get(pin));
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPUT);
    bcm2835_close();


    mask = 0xf2000000;
    printf("Hey, im here\n");
    for(i = 0; i < 32; i ++)
    {
        printf("%d", (mask & (1 >> i)) ? 1 : 0); 
    }
    printf("\n");


    return 0;
}
