#!/usr/bin/env python3 
# -*- coding: utf-8 -*-
"""
Adapter makes things work after they are designed!
Bridge makes them work before they are.
"""

class Dog(object):
    def __init__(self):
        self.name = "Dog"

    def bark(self):
        return "Woof!"

class Cat(object):
    def __init__(self):
        self.name = "Cat"

    def meow(self):
        return "Meow!"

class Human(object):
    def __init__(self):
        self.name = "Human"

    def speak(self):
        return "Hello"

class Car(object):
    def __init__(self):
        self.name = "Car"

    def make_noise(self, octane_level):
        return "Zoom{}".format("!" * octane_level)

class Target(object):
    def __init__(self, obj):
        self._adaptee = obj()
    
    def request(self):
        pass

class DogAdapter(Target):
    def request(self):
        return self._adaptee.bark()

class CatAdapter(Target):
    def request(self):
        return self._adaptee.meow()

class HumanAdapter(Target):
    def request(self):
        return self._adaptee.speak()

class CarAdapter(Target):
    def request(self):
        return self._adaptee.make_noise(3)

if __name__ == "__main__":
    dt = DogAdapter(Dog)
    print(dt.request())
    ct = CatAdapter(Cat)
    print(ct.request())
    ht = HumanAdapter(Human)
    print(ht.request())
    cart = CarAdapter(Car)
    print(cart.request())
