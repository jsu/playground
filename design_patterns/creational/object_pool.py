#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class Reusable:
    pass

class ReusablePool(object):
    def __init__(self, size):
        self._reusables = [Reusable() for _ in range(size)]

    def acquire(self):
        return self._reusables.pop()

    def release(self, reusable):
        self._reusables.append(reusable)

if __name__ == "__main__":
    pool = ReusablePool(10)
    reusable = pool.acquire()
    pool.release(reusable)

