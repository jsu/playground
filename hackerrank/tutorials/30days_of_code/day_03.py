#!/usr/bin/env python3

if __name__ == "__main__":
    n = int(input())

    if n % 2:
        print("Weird\n")
    elif n >= 2 and n <= 5:
        print("Not Weird\n")
    elif n >= 6 and n <= 20:
        print("Weird\n")
    else:
        print("Not Weird\n")
