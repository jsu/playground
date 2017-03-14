import RPi.GPIO
import time

RPi.GPIO.setmode(RPi.GPIO.BCM)

# 7 Segment pins to GPIO ports mapping
#           11,  7,  4,  2,  1, 10,  5,  3
segments = (11, 17, 23,  8,  7,  9, 18, 25)
for segment in segments:
    RPi.GPIO.setup(segment, RPi.GPIO.OUT)
    RPi.GPIO.output(segment, 1)

# Digit pins to GPIO ports mapping
#         12,  9,  8,  6 
digits = (10, 22, 27, 24)
for digit in digits:
    RPi.GPIO.setup(digit, RPi.GPIO.OUT)
    RPi.GPIO.output(digit, 1)

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
    'o': (1, 1, 0, 0, 0, 1, 0),
    'r': (1, 1, 1, 1, 0, 1, 0),
}

TRIG = 6
ECHO = 12

RPi.GPIO.setup(TRIG, RPi.GPIO.OUT)
RPi.GPIO.setup(ECHO, RPi.GPIO.IN)
RPi.GPIO.output(TRIG, False)
time.sleep(2)

try:
    result = '----'
    while True:
        RPi.GPIO.output(TRIG, True)
        '''
        The HC-SR04 sensor requires a short 10uS pulse to trigger the module, which will cause the sensor to start the ranging program (8 ultrasound bursts at 40 kHz) in order to obtain an echo response. So, to create our trigger pulse, we set out trigger pin high for 10uS then set it low again.
        '''
        time.sleep(0.00001)
        RPi.GPIO.output(TRIG, False)
        while RPi.GPIO.input(ECHO) == 0:
            pulse_start = time.time()

        while RPi.GPIO.input(ECHO) == 1:
            pulse_end = time.time()


        pulse_duration = pulse_end - pulse_start
        # Multiply pulse duration by 17160 to get distance
        # Speed of sound = 343.21 m/s
        # Distance  (m) = 343.21 * (Travel Time / 2)
        # Distance (cm) = 17160 * Travel Time
        distance = pulse_duration * 17160

        if distance > 2 and distance < 400:
            result = '{}'.format(int((distance - 0.5) * 10))
            if len(result) is not 5:
                for i in range(4 - len(result)):
                    result = ' ' + result

        print(result)
        for i in range(100):
            for digit in range(4):
                for loop in range(7):
                    RPi.GPIO.output(segments[loop], num[result[digit]][loop])
                if digit == 2:
                    RPi.GPIO.output(segments[-1], 0)
                else:
                    RPi.GPIO.output(segments[-1], 1)
                RPi.GPIO.output(digits[digit], 1)
                time.sleep(0.001)
                RPi.GPIO.output(digits[digit], 0)

except KeyboardInterrupt:
    pass
finally:
    RPi.GPIO.cleanup()
