from gpiozero import DistanceSensor
import time

ultrasonic = DistanceSensor(echo=12, trigger=6)

try:
    while True:
        print(ultrasonic.distance * 100)
        result = '{}'.format(ultrasonic.distance * 100)
        time.sleep(0.1)
except KeyboardInterrupt:
    pass
finally:
    pass
