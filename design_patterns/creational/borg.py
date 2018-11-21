#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Borg(object):
    __shared_state = {}

    def __init__(self):
        self.__dict__ = self.__shared_state
        self.state = "Init"

    def __str__(self):
        return self.state

class YourBorg(Borg):
    pass

if __name__ == "__main__":
    rm1 = Borg()
    rm2 = Borg()

    rm1.state = "Idle"
    rm2.state = "Running"

    print("rm1: {}".format(rm1))
    print("rm2: {}".format(rm2))

    rm2.state = "Zombie"

    print("rm1: {}".format(rm1))
    print("rm2: {}".format(rm2))

    print("rm1 id: {}".format(id(rm1)))
    print("rm2 id: {}".format(id(rm2)))

    rm3 = YourBorg()

    print("rm1: {}".format(rm1))
    print("rm2: {}".format(rm2))
    print("rm3: {}".format(rm3))



