# -*- coding: utf-8 -*-
import RPi.GPIO
import time

# Set Mode to BCM
RPi.GPIO.setmode(RPi.GPIO.BCM)

# 7 Segment pins to GPIO ports mapping
#           11,  7,  4,  2,  1, 10,  5,  3

segments = (11 , 17, 23,  8,  7,  9, 18, 25)
for segment in segments:
    RPi.GPIO.setup(segment, RPi.GPIO.OUT)
    RPi.GPIO.output(segment, 1)

# Digit pins to GPIO ports mapping
#         12,  9,  8,  6 
digits = (10, 22, 27, 24)
for digit in digits:
    RPi.GPIO.setup(digit, RPi.GPIO.OUT)
    RPi.GPIO.output(digit, 0)

num = {
    ' ': (1, 1, 1, 1, 1, 1, 1),
    '-': (1, 1, 1, 1, 1, 1, 0),
    '0': (0, 0, 0, 0, 0, 0, 1),
    '1': (1, 0, 0, 1, 1, 1, 1),
    '2': (0, 0, 1, 0, 0, 1, 0),
    '3': (0, 0, 0, 0, 1, 1, 0),
    '4': (1, 0, 0, 1, 1, 0, 0),
    '5': (0, 1, 0, 0, 1, 0, 0),
    '6': (0, 1, 0, 0, 0, 0, 0),
    '7': (0, 0, 0, 1, 1, 1, 1),
    '8': (0, 0, 0, 0, 0, 0, 0),
    '9': (0, 0, 0, 1, 1, 0, 0),
    'a': (0, 0, 0, 1, 0, 0, 0),
    'b': (1, 1, 0, 0, 0, 0, 0),
    'c': (0, 1, 1, 0, 0, 0, 1),
    'd': (1, 0, 0, 0, 0, 1, 0),
    'e': (0, 1, 1, 0, 0, 0, 0),
    'f': (0, 1, 1, 1, 0, 0, 0),
}

'''
Test all digits / alphabets
counter = 0
for k, v in sorted(num.items()):
    for i in range(100):
        for loop in range(7):
            RPi.GPIO.output(segments[loop], num[k][loop])
        digit = counter % 4
        RPi.GPIO.output(digits[digit], 1)
        time.sleep(0.001)
        RPi.GPIO.output(digits[digit], 0)
    counter += 1
'''

try:
    while True:
        n = time.ctime()[14:16]+time.ctime()[17:19]
        s = str(n).rjust(4)
        for digit in range(4):
            for loop in range(7):
                RPi.GPIO.output(segments[loop], num[s[digit]][loop])
            # Put a dot on third digit
            #dp_switch = digit is not 1
            #RPi.GPIO.output(segments[-1], dp_switch)
            RPi.GPIO.output(digits[digit], 1)
            time.sleep(0.001)
            RPi.GPIO.output(digits[digit], 0)
except KeyboardInterrupt:
    pass
finally:
    RPi.GPIO.cleanup()
