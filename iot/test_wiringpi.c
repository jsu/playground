#include <stdio.h>
#include <mcp3004.h>
#include <wiringPi.h>

#define BASE 200
#define SPI_CHAN 0

int main(int argc, char **argv)
{
    int i;
    int value[6];
    int chan[6] = {0, 1, 2, 3, 4, 5};
    wiringPiSetup();
    mcp3004Setup( BASE, SPI_CHAN );  // 3004»P3008¬°¬Û¦P¨t¦CIC
    for(;;)
    {
        for(i = 1; i < 6; i++)
        {
            value[i] = analogRead(BASE + chan[i]);
            if(value[i] > 400)
            {
                printf("Value%d = %4d\n", i, value[i]);
                delay(1500);
            }
            else
            {
                printf("Value%d = %4d\n", i, value[i]);
                delay(1500);
            }
        }
    }
    return 0;
}
