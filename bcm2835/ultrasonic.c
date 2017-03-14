#include <stdio.h>
#include <time.h>
#include "bcm2835.h"

/* 340 m/s */
#define SPEED_OF_SOUND 340

int main(int argc, char **argv)
{
    uint8_t trigger, echo;
    uint8_t echo_rise, echo_fall;
    uint32_t diff;
    float distance;
    struct timespec sleeper, ts_start, ts_checkpoint, ts_echo_rise, ts_echo_fall;

    trigger = 6;
    echo = 12;
    bcm2835_init();
    bcm2835_gpio_fsel(trigger, BCM2835_GPIO_FSEL_OUTPUT);
    bcm2835_gpio_fsel(echo, BCM2835_GPIO_FSEL_INPUT);

    for(;;)
    {
        echo_rise = 0;
        echo_fall = 0;

        sleeper.tv_sec = 0;
        sleeper.tv_nsec = 10000L;

        bcm2835_gpio_clr(echo);
        bcm2835_gpio_set(trigger);
        nanosleep(&sleeper, NULL);
        bcm2835_gpio_clr(trigger);

        bcm2835_gpio_clr(echo);
        clock_gettime(CLOCK_MONOTONIC_RAW, &ts_start);
        for(;;){
            clock_gettime(CLOCK_MONOTONIC_RAW, &ts_checkpoint);
            diff = ts_checkpoint.tv_nsec - ts_start.tv_nsec;
            diff = diff >= 0 ? diff : diff + 1000000000L;
            if(diff >= 40000000L)
                break;

            if(!echo_rise && bcm2835_gpio_lev(echo) == 0){
                echo_rise = 1;
                clock_gettime(CLOCK_MONOTONIC_RAW, &ts_echo_rise);
                /* ts_echo_rise = ts_checkpoint; */
            }

            if(!echo_fall && bcm2835_gpio_lev(echo) == 1){
                echo_fall = 1;
                clock_gettime(CLOCK_MONOTONIC_RAW, &ts_echo_fall);
                /* ts_echo_fall = ts_checkpoint; */
            }

            if(echo_fall && echo_rise){
                diff = ts_echo_fall.tv_nsec - ts_echo_rise.tv_nsec;
                diff = diff >= 0 ? diff : diff + 1000000000L;
                distance = (double)diff / 100000000.0 * SPEED_OF_SOUND / 2.0 * 100;
                printf("%.2f\n", distance);
                printf("%ld\n%ld.%ld\n%ld.%ld\n\n", 
                        diff,
                        ts_echo_rise.tv_sec,
                        ts_echo_rise.tv_nsec,
                        ts_echo_fall.tv_sec,
                        ts_echo_fall.tv_nsec
                      );
                break;
            }
        }

        sleeper.tv_sec = 0;
        sleeper.tv_nsec = 100000000L;
        nanosleep(&sleeper, NULL);
    }

    return 0;
}
