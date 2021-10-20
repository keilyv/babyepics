#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
epicstest1.py: Very first test of turn on LEDs

Created by Scott Feister on Fri Aug 13 15:11:28 2021
"""

from epics import caget, caput, cainfo
from time import sleep

if __name__ == "__main__":
    print("Hello, world!")
    
    print(caget("shu:pos"))
    print(caget("BB:ID"))
    while True:
        print(caget("BB:VAL"))
        sleep(0.25)
    # for i in range(3):
    #     print(caput("shu:pos", 90.0))
    #     sleep(5)
    #     print(caput("shu:pos", 0.0))
    #     sleep(5)
