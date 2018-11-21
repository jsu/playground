#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def lazy_property(fn):
    attr_name = "__lazy__" + fn.__name__

    @property
    def _lazy_property(self):
        if not hasattr(self, attr_name):
            setattr(self, attr_name, fn(self))
        return getattr(self, attr_name)
    return _lazy_property

class Person(object):
    def __init__(self, name, occupation):
        self.name = name
        self.occupation = occupation
        self.call_count = 0

    @lazy_property
    def relatives(self):
        self.call_count += 1
        relatives = "Many relatives."
        return relatives


def divby2(n):
    num = 0
    while num < n:
        yield num / 2
        num += 1

if __name__ == "__main__":
    p = Person("Jay", "Engineer")
    print("Name: {}, Occupation: {}".format(p.name, p.occupation))
    print(p.__dict__)
    print(p.relatives)
    print(p.__dict__)
    print(p.relatives)
    print(p.__dict__)
    
    print("{}".format(divby2(500000)))
