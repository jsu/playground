# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

class ACGT():
    def __init__(self, a, c, g, t):
        self.a = a
        self.c = c
        self.g = g
        self.t = t
        
def solution(S, P, Q):
    # write your code in Python 3.6
    
    acgt_a = list()
    results = list()
    
    a = c = g = t = 0
    acgt_a.append(ACGT(0, 0, 0, 0))
    for index, value in enumerate(S):
        if value == 'A':
            a += 1
        elif value == 'C':
            c += 1
        elif value == 'G':
            g += 1
        elif value == 'T':
            t += 1
        acgt_a.append(ACGT(a, c, g, t))
    
    for i in range(len(P)):
        p = acgt_a[P[i]]
        q = acgt_a[Q[i] + 1]
        if q.a - p.a > 0:
            results.append(1)
        elif q.c - p.c > 0:
            results.append(2)
        elif q.g - p.g > 0:
            results.append(3)
        elif q.t - p.t > 0:
            results.append(4)
            
    return results
