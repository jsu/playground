from gpiozero import MotionSensor
import time

pir = MotionSensor(9)

while True:
    if pir.motion_detected:
        print("You Movied")
    else:
        print("==========")
    time.sleep(0.5)
