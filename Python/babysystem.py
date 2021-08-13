#has not been tested

from epics import caget, caput, cainfo
from time import sleep
import math

while True:
    value = caget("baby:pot")
    leds = math.floor(value/4)
    caput("leds:set", leds)
    print(caget("BB:VAL"))
    if(caget("baby:rocker"))==1:
        caput("shu:pos", 0.0)
    else:
        caput("shu:pos", 90.0)
    sleep (.25)
