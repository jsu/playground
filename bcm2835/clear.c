#include <stdint.h>

#include "bcm2835.h"

int main(int argc, char **argv)
{
    uint8_t i;
    bcm2835_init();
    for(i = 0; i<= 28; i++)
        bcm2835_gpio_fsel(i, BCM2835_GPIO_FSEL_INPUT);
    bcm2835_close();
    return 0;
}
