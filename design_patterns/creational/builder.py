#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Separates object construction from its representation
"""

class Director(object):
    __builder = None

    def set_builder(self, builder):
        self.__builder = builder

    def get_car(self):
        car = Product()

        body = self.__builder.get_body()
        car.set_body(body)

        engine = self.__builder.get_engine()
        car.set_engine(engine)

        for i in range(4):
            wheel = self.__builder.get_wheel()
            car.attach_wheel(wheel)

        return car

class Product(object):
    def __init__(self):
        self.__body = None
        self.__engine = None
        self.__wheels = list()

    def set_body(self, body):
        self.__body = body

    def set_engine(self, engine):
        self.__engine = engine

    def attach_wheel(self, wheel):
        self.__wheels.append(wheel)

    def specification(self):
        print("body: {}".format(self.__body.shape))
        print("engine horsepower: {}".format(self.__engine.horsepower))
        print("tire size: {}".format(self.__wheels[0].size))

class Builder(object):
    def get_body(self):
        pass
    def get_engine(self):
        pass
    def get_wheel(self):
        pass

class ToyotaBuilder(Builder):
    def get_body(self):
        body = Body()
        body.shape = "Practical"
        return body

    def get_engine(self):
        engine = Engine()
        engine.horsepower = 200
        return engine
    
    def get_wheel(self):
        wheel = Wheel()
        wheel.size = 18
        return wheel

class LexusBuilder(Builder):
    def get_body(self):
        body = Body()
        body.shape = "Fancy"
        return body

    def get_engine(self):
        engine = Engine()
        engine.horsepower = 600
        return engine
    
    def get_wheel(self):
        wheel = Wheel()
        wheel.size = 20
        return wheel

class Body(object):
    shape = None

class Engine(object):
    horsepower = None

class Wheel(object):
    size = None

if __name__ == "__main__":
    toyota_builder = ToyotaBuilder()
    lexus_builder = LexusBuilder() 

    director = Director()

    director.set_builder(toyota_builder)
    toyota = director.get_car()
    toyota.specification()

    director.set_builder(lexus_builder)
    lexus = director.get_car()
    lexus.specification()
        
