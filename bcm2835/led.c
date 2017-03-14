#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

#include "bcm2835.h"

void signal_handler(int signum)
{
    bcm2835_gpio_fsel(21, BCM2835_GPIO_FSEL_INPUT);
    bcm2835_close();
    exit(0);
}

int main(int argc, char **argv)
{
    struct timespec sleeper;
    uint8_t pin;

    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGSTOP, signal_handler);
    bcm2835_init();

    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 500000000L;

    pin = 21;
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTPUT);

    for(;;)
    {
        bcm2835_gpio_set(pin);
        nanosleep(&sleeper, NULL);
        bcm2835_gpio_clr(pin);
        nanosleep(&sleeper, NULL);
    }

    return 0;
}
