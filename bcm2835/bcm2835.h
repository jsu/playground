#ifndef BCM2835_INCLUDED
#define BCM2835_INCLUDED

#include <stdint.h>

#define BCM2835_HIGH 0x1
#define BCM2835_LOW  0x0
#define BCM2835_ENABLE 0x1
#define BCM2835_DISABLE 0x0

#define DEFAULT_BCM2835_PERIPHERALS_BASE 0x3F000000
#define DEFAULT_BLOCK_SIZE (4*1024)

#define BCM2835_DT_FILENAME "/proc/device-tree/soc/ranges"
#define BCM2835_DT_PERI_BASE_ADDRESS_OFFSET 4
#define BCM2835_DT_PERI_SIZE_OFFSET 8

#define BCM2835_ST_BASE    0x3000
#define BCM2835_GPIO_PADS  0x100000
#define BCM2835_CLOCK_BASE 0x101000
#define BCM2835_GPIO_BASE  0x200000
#define BCM2835_SPI0_BASE  0x204000
#define BCM2835_BSC0_BASE  0x205000
#define BCM2835_GPIO_PWM   0x20C000
#define BCM2835_BSC1_BASE  0x804000

/*
 * Register View (P.90)
 */
#define BCM2835_GPFSEL0   0x0000
#define BCM2835_GPFSEL1   0x0004
#define BCM2835_GPFSEL2   0x0008
#define BCM2835_GPFSEL3   0x000c
#define BCM2835_GPFSEL4   0x0010
#define BCM2835_GPFSEL5   0x0014
#define BCM2835_GPSET0    0x001c
#define BCM2835_GPSET1    0x0020
#define BCM2835_GPCLR0    0x0028
#define BCM2835_GPCLR1    0x002c
#define BCM2835_GPLEV0    0x0034
#define BCM2835_GPLEV1    0x0038
#define BCM2835_GPEDS0    0x0040
#define BCM2835_GPEDS1    0x0044
#define BCM2835_GPREN0    0x004c
#define BCM2835_GPREN1    0x0050
#define BCM2835_GPFEN0    0x0058
#define BCM2835_GPFEN1    0x005c
#define BCM2835_GPHEN0    0x0064
#define BCM2835_GPHEN1    0x0068
#define BCM2835_GPLEN0    0x0070
#define BCM2835_GPLEN1    0x0074
#define BCM2835_GPAREN0   0x007c
#define BCM2835_GPAREN1   0x0080
#define BCM2835_GPAFEN0   0x0088
#define BCM2835_GPAFEN1   0x008c
#define BCM2835_GPPUD     0x0094
#define BCM2835_GPPUDCLK0 0x0098
#define BCM2835_GPPUDCLK1 0x009c
/*
 * GPIO Function Select Registers (P.91)
 */
typedef enum
{
    BCM2835_GPIO_FSEL_INPUT  = 0x00,   /*!< Input 0b000 */
    BCM2835_GPIO_FSEL_OUTPUT = 0x01,   /*!< Output 0b001 */
    BCM2835_GPIO_FSEL_ALT0   = 0x04,   /*!< Alternate function 0 0b100 */
    BCM2835_GPIO_FSEL_ALT1   = 0x05,   /*!< Alternate function 1 0b101 */
    BCM2835_GPIO_FSEL_ALT2   = 0x06,   /*!< Alternate function 2 0b110, */
    BCM2835_GPIO_FSEL_ALT3   = 0x07,   /*!< Alternate function 3 0b111 */
    BCM2835_GPIO_FSEL_ALT4   = 0x03,   /*!< Alternate function 4 0b011 */
    BCM2835_GPIO_FSEL_ALT5   = 0x02,   /*!< Alternate function 5 0b010 */
    BCM2835_GPIO_FSEL_MASK   = 0x07    /*!< Function select bits mask 0b111 */
}bcm2835_gpio_function_select;

uint8_t bcm2835_init();
void bcm2835_close();
void bcm2835_gpio_fsel(uint8_t pin, uint8_t mode);
void bcm2835_gpio_set(uint32_t field, uint32_t mask);
void bcm2835_gpio_pin_set(uint8_t pin);
void bcm2835_gpio_pin_clr(uint8_t pin);
uint8_t bcm2835_gpio_pin_lev_get(uint8_t pin);

#endif
