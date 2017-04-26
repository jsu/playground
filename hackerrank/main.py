#!/usr/bin/env python3
from random import randrange

if __name__ == '__main__':
    t = 5
    set_n = set()
    print(t)
    l = [True, False, True, False, True]
    for index in range(t):
        while True:
            n = randrange(3, 200)
            if n not in set_n:
               set_n.add(n)
               break
        k = randrange(1, n)
        print("{} {}".format(n, k))
        a = list()
        a.append('0')
        a.append(str(randrange(-1000, -1)))
        a.append(str(randrange(1, 1000)))
        if l[index]:
            rk = k - 2 - 1
        else:
            rk = k - 2 
        for _ in range(rk):
            a.append(str(randrange(-1000, 0)))
        for _ in range(n - rk - 2):
            a.append(str(randrange(1, 1000)))
        print(' '.join(a))
