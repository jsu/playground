#include <stdio.h>
#include <signal.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include "seven_segment_display.h"

char *display_board;

void *pclock(void *dummy)
{
    struct timespec sleeper;
    struct tm *t;
    time_t now;

    sleeper.tv_sec = 0;
    sleeper.tv_nsec = 200000000L;
    for(;;)
    {
        now = time(NULL);
        t = localtime(&now); 
        sprintf(display_board, "%02d%02d", t->tm_min, t->tm_sec);
        nanosleep(&sleeper, NULL);
    }
}

void clock_init(void)
{
    pthread_t clock_thread;
    if(pthread_create(&clock_thread, NULL, pclock, NULL) != 0)
        printf("Thread create failed: %s\n", strerror(errno));
}

void signal_handler(int signum)
{
    seven_segment_display_close();
    exit(0);
}

int main(int argc, char **argv)
{
    struct timespec sleeper;
    uint8_t segments[] = {
        11, 17, 23, 8, 7, 9, 18, 25
    };
    uint8_t digits[] = {
        10, 22, 27, 24
    };

    signal(SIGINT, signal_handler);
    signal(SIGKILL, signal_handler);
    signal(SIGSTOP, signal_handler);

    display_board = seven_segment_display_init(segments, digits);
    clock_init();

    sleeper.tv_sec = 10;
    sleeper.tv_nsec = 0L;
    for(;;)
        nanosleep(&sleeper, NULL);

    return 0;
}
