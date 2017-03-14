#include <stdint.h>
#include "bcm2835.h"

int main(int argc, char **argv)
{
    uint8_t button, led;

    button = 2;
    led = 14;

    bcm2835_init();
    bcm2835_gpio_fsel(button, BCM2835_GPIO_FSEL_INPUT);
    bcm2835_gpio_fsel(led, BCM2835_GPIO_FSEL_OUTPUT);

    for(;;)
    {
        if(bcm2835_gpio_lev(button) == LOW)
            bcm2835_gpio_set(led); 
        else
            bcm2835_gpio_clr(led);
    }

    return 0;
}
