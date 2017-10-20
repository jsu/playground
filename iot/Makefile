CC=gcc
CFLAGS=-ansi -std=c11 -pedantic -Wall -D_POSIX_C_SOURCE=200809L -lmosquitto -lpthread -lwiringPi -lbcm2835

prog: main.c
	$(CC) $^ -o $@ $(CFLAGS)

test: test.c
	$(CC) $^ -o $@ $(CFLAGS)
