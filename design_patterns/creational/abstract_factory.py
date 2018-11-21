#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Creates an intstance of several families of classes.
"""

class Button(object):
    def paint(self):
        pass

class LinuxButton(Button):
    def paint(self):
        return "Linux style"

class MacOSButton(Button):
    def paint(self):
        return "MacOS style"

class WindowsButton(Button):
    def paint(self):
        return "Windows style"


if __name__ == "__main__":
    appearance = "linux"

    if appearance == "linux":
        factory = LinuxButton
    elif appearance == "osx":
        factory = MacOSButton
    elif appearance == "win":
        factory = WindowsButton
    else:
        raise NotImplementedError(
            "Not implemented for your platform: {}".format(appearance)
        )

    if factory:
        button = factory()
        print(button.paint())
