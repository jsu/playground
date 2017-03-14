#include "bcm2835.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdint.h>

/* Virtual memory address of the mapped peripherals block 
 *  */
uint32_t *bcm2835_peripherals = (uint32_t *)MAP_FAILED;
uint32_t bcm2835_peripherals_size;

/* And the register bases within the peripherals block
 *  */
volatile uint32_t *bcm2835_gpio = (uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_pwm  = (uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_clk  = (uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_pads = (uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_spi0 = (uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_bsc0 = (uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_bsc1 = (uint32_t *)MAP_FAILED;
volatile uint32_t *bcm2835_st   = (uint32_t *)MAP_FAILED;

void bcm2835_close(void)
{
    munmap(bcm2835_peripherals, bcm2835_peripherals_size);
    bcm2835_peripherals = MAP_FAILED;
}

uint8_t bcm2835_init(void)
{
    FILE *fp;
    int mem_fd;
    uint32_t bcm2835_peripherals_base, bcm2835_peripherals_size;

    bcm2835_peripherals_base = DEFAULT_BCM2835_PERIPHERALS_BASE;
    bcm2835_peripherals_size = DEFAULT_BLOCK_SIZE;
    if((fp = fopen(BCM2835_DT_FILENAME, "rb")))
    {
        unsigned char buf[4]; 
        fseek(fp, BCM2835_DT_PERI_BASE_ADDRESS_OFFSET, SEEK_SET);
        if(fread(buf, 1, sizeof(buf), fp) == sizeof(buf))
            bcm2835_peripherals_base = (uint32_t)(
                buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3] << 0
            );
        fseek(fp, BCM2835_DT_PERI_SIZE_OFFSET, SEEK_SET);
        if(fread(buf, 1, sizeof(buf), fp) == sizeof(buf))
            bcm2835_peripherals_size = (
                buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3] << 0
            );
        fclose(fp);
    }

    mem_fd = -1;
    if(geteuid() == 0)
    {
        if((mem_fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0)
        {
            printf("Can't open /dev/mem\n");
            exit(-1);
        }

        bcm2835_peripherals = mmap(
            NULL,
            bcm2835_peripherals_size,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            mem_fd,
            bcm2835_peripherals_base
        );

        bcm2835_gpio = bcm2835_peripherals + BCM2835_GPIO_BASE / 4;
        bcm2835_pwm  = bcm2835_peripherals + BCM2835_GPIO_PWM / 4;
        bcm2835_clk  = bcm2835_peripherals + BCM2835_CLOCK_BASE / 4;
        bcm2835_pads = bcm2835_peripherals + BCM2835_GPIO_PADS / 4;
        bcm2835_spi0 = bcm2835_peripherals + BCM2835_SPI0_BASE / 4;
        bcm2835_bsc0 = bcm2835_peripherals + BCM2835_BSC0_BASE / 4;
        bcm2835_bsc1 = bcm2835_peripherals + BCM2835_BSC1_BASE / 4;
        bcm2835_st   = bcm2835_peripherals + BCM2835_ST_BASE / 4;
    }
    else
    {
        /* Non root user can use only GPIO */
        if((mem_fd = open("/dev/gpiomem", O_RDWR|O_SYNC)) < 0){
            printf("Can't open /dev/gpiomem\n");
            exit(-1);
        }

        bcm2835_peripherals_base = 0;
        bcm2835_peripherals = mmap(
            NULL,
            bcm2835_peripherals_size,
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            mem_fd,
            bcm2835_peripherals_base
        );

        bcm2835_gpio = bcm2835_peripherals;
    }
    close(mem_fd);

    return 1;
}

void bcm2835_gpio_set(uint32_t field, uint32_t mask)
{
    *(bcm2835_gpio + field / 4) = mask;
}
/*
 * GPIO Function Select
 * 54 GPIO pins
 * 3 bits to represent the status of each pin
 * 32 bits per address / 3 = 10 pins per address
 */
void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode)
{
    volatile uint32_t *paddr;
    uint32_t mask, value;
    uint8_t shift;

    paddr = bcm2835_gpio + BCM2835_GPFSEL0 / 4 + pin / 10;
    shift = pin % 10 * 3;
    mask = BCM2835_GPIO_FSEL_MASK << shift;
    value = mode << shift;
    *paddr = (*paddr & ~mask) | (value & mask);
}

/* GPIO Pin Output Set */
void bcm2835_gpio_pin_set(uint8_t pin)
{
    /* bcm2835_gpio_set(BCM2835_GPSET0, BCM2835_HIGH << pin % 32); */
    *(bcm2835_gpio + BCM2835_GPSET0 / 4 + pin / 32) = BCM2835_HIGH << pin % 32;
}

/* GPIO Pin Output Clear */
void bcm2835_gpio_pin_clr(uint8_t pin)
{
    /* bcm2835_gpio_set(BCM2835_GPCLR0, pin, BCM2835_HIGH); */
    *(bcm2835_gpio + BCM2835_GPCLR0 / 4 + pin / 32) = BCM2835_HIGH << pin % 32;
}

/* GPIO Pin Level */
uint8_t bcm2835_gpio_pin_lev_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;
                     
    paddr = bcm2835_gpio + BCM2835_GPLEV0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;

    return (value & (BCM2835_HIGH << shift)) ?  BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Event Detect Status */
void bcm2835_gpio_pin_eds_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPEDS0 / 4 + pin / 32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_eds_get(uint8_t pin)
{
    volatile uint32_t  *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPEDS0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Rising Edge Detect Enable */
void bcm2835_gpio_pin_ren_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPREN0 / 4 + pin /32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_ren_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPREN0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Falling Edge Detect Enable */
void bcm2835_gpio_pin_fen_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPFEN0 / 4 + pin / 32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_fen_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPFEN0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin High Detect Enable */
void bcm2835_gpio_pin_hen_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPHEN0 / 4 + pin / 32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_hen_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPHEN0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Low Dectect Enable */
void bcm2835_gpio_pin_len_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPLEN0 / 4 + pin / 32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_len_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPLEN0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Async. Rising Edge Detect */
void bcm2835_gpio_pin_aren_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPAREN0 / 4 + pin / 32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_aren_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPAREN0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Async. Falling Edge Detect */
void bcm2835_gpio_pin_afen_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPAFEN0 / 4 + pin / 32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_afen_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPAFEN0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Pull-up/down Enable */
void bcm2835_gpio_pin_pud_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPPUD / 4) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_pud_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPPUD / 4;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}

/* GPIO Pin Pull-up/down Enable Clock */
void bcm2835_gpio_pin_pud_clk_set(uint8_t pin, uint8_t status)
{
    *(bcm2835_gpio + BCM2835_GPPUDCLK0 / 4 + pin / 32) = status << pin % 32;
}

uint8_t bcm2835_gpio_pin_pud_clk_get(uint8_t pin)
{
    volatile uint32_t *paddr;
    uint8_t shift;
    uint32_t value;

    paddr = bcm2835_gpio + BCM2835_GPPUDCLK0 / 4 + pin / 32;
    shift = pin % 32;
    value = *paddr;
    return (value & (BCM2835_HIGH << shift)) ? BCM2835_HIGH : BCM2835_LOW;
}
