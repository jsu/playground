#!/usr/bin/env python3
# -*- coding: utf-8 -*-

class FictionAuthor(object):
    def write(self):
        return "Fiction"

class NonfictionAuthor(object):
    def write(self):
        return "Nonfiction"

class Publisher(object):
    def publish(self):
        self.hire()
        return self.author.write()

class Blog(Publisher):
    def hire(self):
        self.author = FictionAuthor()

class News(Publisher):
    def hire(self):
        self.author = NonfictionAuthor()


if __name__ == "__main__":
    publisher = Blog()
    print(publisher.publish())

    publisher = News()
    print(publisher.publish())
