#include <bcm2835.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    char out_ch1[] = {0x06, 0x40, 0x00};
    char out_ch2[] = {0x06, 0x80, 0x00};
    char out_ch3[] = {0x06, 0xc0, 0x00};
    char out_ch4[] = {0x07, 0x00, 0x00};
    char out_ch5[] = {0x07, 0x40, 0x00};
    char ch_data[] = {0x00, 0x00, 0x00};
    struct timespec sleeper;
    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 500000000L; /* 500ms */
	if (!bcm2835_init())
	{
		printf("bcm2835_init failed. Are you running as root??\n");
		return 1;
	}
	if (!bcm2835_spi_begin())
	{
		printf("bcm2835_spi_begin failed. Are you running as root??\n");
		return 1;
	}
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    for(;;)
    {
        bcm2835_spi_transfernb(out_ch1, ch_data, 3);
            printf("ch1data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        bcm2835_spi_transfernb(out_ch2, ch_data, 3);
            printf("ch2data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        bcm2835_spi_transfernb(out_ch3, ch_data, 3);
            printf("ch3data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        bcm2835_spi_transfernb(out_ch4, ch_data, 3);
            printf("ch4data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        bcm2835_spi_transfernb(out_ch5, ch_data, 3);
            printf("ch5data: %02x %02x %02x\n\n", ch_data[0], ch_data[1], ch_data[2]);
        nanosleep(&sleeper, NULL);
    }
    
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}
