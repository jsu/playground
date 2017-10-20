#include <stdio.h>
#include <mosquitto.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <regex.h>
#include <wiringSerial.h>
#include <bcm2835.h>

#define SN "03"
#define COMPIN 22
#define LEDPIN 5
#define BUTTON1 23
#define BUTTON2 24
#define RELAYIT 27
#define RELAY1 5
#define RELAY2 6
#define RELAY3 13
#define RELAY4 26
#define RELAY5 12
#define BUZZER 16

struct status{
    int LED;
    int machine;
    int EP;
    int UV;
    int ozone;
    int ion;
    int fan;
    int buzzer;
    int pwm_duty;
    int op_mode;
}status;

int strtoint(char *str)
{
    char c, *ptr = str;
    int n = 0;
    /* char c should be 0-9 */
    while((c = *ptr++) >= 0x30 && c <= 0x39 && c != 0x2f)
        n = n * 10 + c - '0';

    return n;
}

void LED_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.LED = flag;
    sprintf(buffer2, "%d", status.LED);
    sprintf(buffer, "XYCS/%s/status/LED", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
    bcm2835_gpio_write(LEDPIN, status.LED);
}

void machine_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.machine = flag;
    sprintf(buffer2, "%d", status.machine);
    sprintf(buffer, "XYCS/%s/status/machine", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
    bcm2835_gpio_write(RELAY1, flag);
}

void EP_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.EP = flag;
    sprintf(buffer2, "%d", status.EP);
    sprintf(buffer, "XYCS/%s/status/EP", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void UV_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.UV = flag;
    sprintf(buffer2, "%d", status.UV);
    sprintf(buffer, "XYCS/%s/status/UV", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void ozone_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.ozone = flag;
    sprintf(buffer2, "%d", status.ozone);
    sprintf(buffer, "XYCS/%s/status/ozone", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void ion_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.ion = flag;
    sprintf(buffer2, "%d", status.ion);
    sprintf(buffer, "XYCS/%s/status/ion", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void fan_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.fan = flag;
    sprintf(buffer2, "%d", status.fan);
    sprintf(buffer, "XYCS/%s/status/fan", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void buzzer_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.buzzer = flag;
    sprintf(buffer2, "%d", status.buzzer);
    sprintf(buffer, "XYCS/%s/status/buzzer", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void pwm_duty_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.pwm_duty = flag;
    sprintf(buffer2, "%d", status.pwm_duty);
    sprintf(buffer, "XYCS/%s/status/pwm_duty", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void op_mode_switch(struct mosquitto *mosq, int flag)
{
    char buffer[80], buffer2[2];
    status.op_mode = flag;
    sprintf(buffer2, "%d", status.op_mode);
    sprintf(buffer, "XYCS/%s/status/op_mode", SN);
    mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
            buffer2, 0, false);
}

void message_callback(struct mosquitto *mosq, void *userdata,
        const struct mosquitto_message *message)
{
    int i;
    char *buffer;
    char *match;
    regex_t regex;
    int nmatch = 2;
    regmatch_t matchptr[nmatch];
    match = (char *)malloc(sizeof(match) * 80);
    buffer = (char *)malloc(sizeof(buffer) * 80);

    sprintf(buffer, "XYCS/%s/command/([A-Za-z0-9]+)", SN);
    if(regcomp(&regex, buffer, REG_EXTENDED))
    {
        pthread_exit(NULL); 
    }
    if(regexec(&regex, message->topic, nmatch, matchptr, 0))
    {
        pthread_exit(NULL); 
    }
    strcpy(match, message->topic);
    match[matchptr[1].rm_eo] = 0;
    strcpy(match, match + matchptr[1].rm_so);

    if(message->payloadlen){
        if(strcmp(match, "LED") == 0)
        {
            if((i = strtoint(message->payload)) != status.LED)
                LED_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "machine") == 0)
        {
            if((i = strtoint(message->payload)) != status.machine)
                machine_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "EP") == 0)
        {
            if((i = strtoint(message->payload)) != status.EP)
                EP_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "UV") == 0)
        {
            if((i = strtoint(message->payload)) != status.UV)
                UV_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "ozone") == 0)
        {
            if((i = strtoint(message->payload)) != status.ozone)
                ozone_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "ion") == 0)
        {
            if((i = strtoint(message->payload)) != status.ion)
                ion_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "fan") == 0)
        {
            if((i = strtoint(message->payload)) != status.fan)
                fan_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "buzzer") == 0)
        {
            if((i = strtoint(message->payload)) != status.buzzer)
                buzzer_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "pwm_duty") == 0)
        {
            if((i = strtoint(message->payload)) != status.pwm_duty)
                pwm_duty_switch(mosq, strtoint(message->payload));
        }
        else if(strcmp(match, "op_mode") == 0)
        {
            if((i = strtoint(message->payload)) != status.op_mode)
                op_mode_switch(mosq, strtoint(message->payload));
        }
    }else{
        printf("%s (null)\n", message->topic);
    }
    free(buffer);
    free(match);
    regfree(&regex);
    fflush(stdout);
}

void *remote_control_thread(void *mosq)
{
    char buffer[80];
    mosquitto_message_callback_set(mosq, message_callback);
    sprintf(buffer, "XYCS/%s/command/+", SN);
    mosquitto_subscribe(mosq, NULL, buffer, 2);
    mosquitto_loop_forever(mosq, -1, 1);

    pthread_exit(NULL);
}

void *local_control_thread(void *mosq)
{
    struct timespec sleeper;
    char out_ch1[] = {0x06, 0x40, 0x00};
    char out_ch2[] = {0x06, 0x80, 0x00};
    char out_ch3[] = {0x06, 0xc0, 0x00};
    char out_ch4[] = {0x07, 0x00, 0x00};
    char out_ch5[] = {0x07, 0x40, 0x00};
    char ch_data[] = {0x00, 0x00, 0x00};

    bcm2835_gpio_fsel(COMPIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RELAYIT, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(RELAY1, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RELAY1, LOW);
    bcm2835_gpio_fsel(RELAY2, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RELAY2, LOW);
    bcm2835_gpio_fsel(RELAY3, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RELAY3, LOW);
    bcm2835_gpio_fsel(RELAY4, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RELAY4, LOW);
    bcm2835_gpio_fsel(RELAY5, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(RELAY5, LOW);
    bcm2835_gpio_fsel(BUZZER, BCM2835_GPIO_FSEL_OUTP);

    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 500000000L; /* 500ms */
    if (!bcm2835_spi_begin())
    {
        printf("bcm2835_spi_begin failed. Are you running as root??\n");
        pthread_exit(NULL);
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536);
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);

    for(;;)
    {
        bcm2835_spi_transfernb(out_ch1, ch_data, 3);
        /* 0x0f when vcc is 5V, 0x09 when vcc is 3.3V */
        if(ch_data[1] == 0x0f || ch_data[1] == 0x09)
        {
            printf("ch1data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        }
        bcm2835_spi_transfernb(out_ch2, ch_data, 3);
        if(ch_data[1] == 0x0f || ch_data[1] == 0x09)
        {
            printf("ch2data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        }    
        bcm2835_spi_transfernb(out_ch3, ch_data, 3);
        if(ch_data[1] == 0x0f || ch_data[1] == 0x09)
        {
            printf("ch3data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        }
        bcm2835_spi_transfernb(out_ch4, ch_data, 3);
        if(ch_data[1] == 0x0f || ch_data[1] == 0x09)
            printf("ch4data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
        bcm2835_spi_transfernb(out_ch5, ch_data, 3);
        if(ch_data[1] == 0x0f || ch_data[1] == 0x09)
        {
            printf("ch5data: %02x %02x %02x\n", ch_data[0], ch_data[1], ch_data[2]);
            status.EP = status.EP ? 0 : 1;
            bcm2835_gpio_write(RELAY1, status.EP);
        }
        nanosleep(&sleeper, NULL);
    }

    bcm2835_spi_end();
    pthread_exit(NULL);
}

void *status_publish_thread(void *mosq)
{
    char *buffer, *buffer2;
    struct timespec sleeper;
    sleeper.tv_sec = 3;
    sleeper.tv_nsec = 0L;
    buffer = (char *)malloc(sizeof(buffer) * 80);
    buffer2 = (char *)malloc(sizeof(buffer2) * 8);

    for(;;)
    {
        sprintf(buffer, "XYCS/%s/status/LED", SN);
        sprintf(buffer2, "%d", status.LED);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/machine", SN);
        sprintf(buffer2, "%d", status.machine);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/EP", SN);
        sprintf(buffer2, "%d", status.EP);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/UV", SN);
        sprintf(buffer2, "%d", status.UV);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/ozone", SN);
        sprintf(buffer2, "%d", status.ozone);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/ion", SN);
        sprintf(buffer2, "%d", status.ion);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/fan", SN);
        sprintf(buffer2, "%d", status.fan);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/buzzer", SN);
        sprintf(buffer2, "%d", status.buzzer);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/pwm_duty", SN);
        sprintf(buffer2, "%d", status.pwm_duty);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        sprintf(buffer, "XYCS/%s/status/op_mode", SN);
        sprintf(buffer2, "%d", status.op_mode);
        mosquitto_publish(mosq, NULL, buffer, strlen(buffer2),
                buffer2, 0 , false);
        nanosleep(&sleeper, NULL);
    }
    free(buffer);
    free(buffer2);
}

void init_status()
{
    status.LED = 0;
    status.machine = 6;
    status.EP = 0;
    status.UV = 0;
    status.ozone = 0;
    status.ion = 0;
    status.fan = 0;
    status.buzzer = 0;
    status.pwm_duty = 0;
    status.op_mode = 0;
}

void *sensor_publish_thread(void *mosq)
{
    char *buffer, *ptr, *sensor, *value;
    char *portname = "/dev/ttyUSB0";	
    char c;
    const char delim[2] = ",";
    int fd;
    buffer = (char *)malloc(sizeof(buffer) * 80);
    init_status();

    if((fd = serialOpen(portname, 9600)) < 0)
    {
        fprintf(stderr, "Unable to open serial device %s\n", strerror(errno));
        pthread_exit(NULL); 
    }

    for(;;)
    {
        ptr = buffer;
        while((c = serialGetchar(fd)) != '\n')
            *ptr++ = c;
        *ptr = '\0';
        sensor = strtok(buffer, delim);
        value = strtok(NULL, delim);

        if(strcmp(sensor, "humidity") == 0)
        {
            sprintf(buffer, "XYCS/%s/sensor/humidity", SN);
            mosquitto_publish(mosq, NULL, buffer, strlen(value), value, 0,
                    false);
        }
        else if(strcmp(sensor, "temperature") == 0)
        {
            sprintf(buffer, "XYCS/%s/sensor/temperature", SN);
            mosquitto_publish(mosq, NULL, buffer, strlen(value), value, 0,
                    false);
        }
        else if(strcmp(sensor, "prd_current") == 0)
        {
            sprintf(buffer, "XYCS/%s/sensor/prd_current", SN);
            mosquitto_publish(mosq, NULL, buffer, strlen(value), value, 0,
                    false);
        }
        else if(strcmp(sensor, "motion"))
        {
            sprintf(buffer, "XYCS/%s/sensor/motion", SN);
            mosquitto_publish(mosq, NULL, buffer, strlen(value), value, 0,
                    false);
        }
        else if(strcmp(sensor, "fan_current"))
        {
            sprintf(buffer, "XYCS/%s/sensor/fan_current", SN);
            mosquitto_publish(mosq, NULL, buffer, strlen(value), value, 0,
                    false);
        }
        else if(strcmp(sensor, "UV"))
        {
            sprintf(buffer, "XYCS/%s/sensor/UV", SN);
            mosquitto_publish(mosq, NULL, buffer, strlen(value), value, 0,
                    false);
        }
        else if(strcmp(sensor, "ozone"))
        {
            sprintf(buffer, "XYCS/%s/sensor/ozone", SN);
            mosquitto_publish(mosq, NULL, buffer, strlen(value), value, 0,
                    false);
        }
    }
    free(buffer);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    char *host = "iot.eclipse.org";
    int port = 1883;
    int keepalive = 60;
    struct mosquitto *mosq = NULL;
    pthread_t id_sensor_pub, id_status_pub, id_local_ctrl, id_remote_ctrl;

    bcm2835_init();
    bcm2835_gpio_fsel(COMPIN, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(COMPIN, 1);
    mosquitto_lib_init();
    mosq = mosquitto_new(NULL, 1, NULL); /* 1 means clean session. */
    if(!mosq){
        fprintf(stderr, "Error: Out of memory.\n");
        return 1;
    }

    if(mosquitto_connect(mosq, host, port, keepalive)){
        fprintf(stderr, "Unable to connect.\n");
        return 1;
    }

    pthread_create(&id_sensor_pub, NULL, sensor_publish_thread, (void *)mosq);
    pthread_create(&id_status_pub, NULL, status_publish_thread, (void *)mosq);
    pthread_create(&id_local_ctrl, NULL, local_control_thread, (void *)mosq);
    pthread_create(&id_remote_ctrl, NULL, remote_control_thread, (void *)mosq);
    pthread_join(id_sensor_pub, NULL);
    pthread_join(id_status_pub, NULL);
    pthread_join(id_local_ctrl, NULL);
    pthread_join(id_remote_ctrl, NULL);

    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();
    return 0;
}
