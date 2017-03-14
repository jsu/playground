#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#include "bcm2835.h"

#define	FAST_COUNT	10000000
#define	SLOW_COUNT	 1000000
#define	PASSES		       5

uint64_t epochMilli;

unsigned int millis (void)
{
  uint64_t now;

  struct  timespec ts ;

  clock_gettime (CLOCK_MONOTONIC_RAW, &ts) ;

  now  = (uint64_t)ts.tv_sec * (uint64_t)1000 + (uint64_t)(ts.tv_nsec / 1000000L) ;

  return (uint32_t)(now - epochMilli) ;
}

void speedTest (int pin, int maxCount)
{
  int count, sum, perSec, i ;
  unsigned int start, end ;


  sum = 0 ;

  for (i = 0 ; i < PASSES ; ++i)
  {
    start = millis () ;
    for (count = 0 ; count < maxCount ; ++count)
        bcm2835_gpio_set(pin);
    end = millis () ;
    printf (" %6d", end - start) ;
    fflush (stdout) ;
    sum += (end - start) ;
  }

  bcm2835_gpio_clr(pin);
  printf (". Av: %6dmS", sum / PASSES) ;
  perSec = (int)(double)maxCount / (double)((double)sum / (double)PASSES) * 1000.0 ;
  printf (": %7d/sec\n", perSec) ;
}


int main (void)
{
  struct  timespec ts ;
  clock_gettime (CLOCK_MONOTONIC_RAW, &ts) ;
  epochMilli = (uint64_t)ts.tv_sec * (uint64_t)1000    + (uint64_t)(ts.tv_nsec / 1000000L) ;

  printf ("Raspberry Pi wiringPi GPIO speed test program\n") ;
  printf ("=============================================\n") ;


  printf ("\nNative wiringPi method: (%8d iterations)\n", FAST_COUNT) ;
  bcm2835_init();
    bcm2835_gpio_fsel(17, BCM2835_GPIO_FSEL_OUTPUT);
    speedTest(17, FAST_COUNT);
    bcm2835_gpio_fsel(17, BCM2835_GPIO_FSEL_INPUT);

  return 0 ;
}
