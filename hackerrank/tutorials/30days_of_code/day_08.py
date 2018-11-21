#!/usr/bin/env python3

if __name__ == "__main__":
    phonebook = dict()
    for i in range(int(input())):
        entry = input().split()
        phonebook[entry[0]] = entry[1]

    while True:
        name = input()
        if name in phonebook:
            print("{}={}".format(name, phonebook[name]))
        else:
            print("Not found")
