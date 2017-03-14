# -*- coding: utf-8 -*-
from gpiozero import LED, Button
from signal import pause

led = LED(14)
button = Button(2)

try:
    button.when_pressed = led.on
    button.when_released = led.off
    pause()
except KeyboardInterrupt:
    pass
