#include "Display.h"
#include <Arduino.h>
Display::Display(/* args */)
{
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
}

Display::~Display()
{
}

void Display::setCounter(unsigned char min, unsigned char sec)
{
    count = (min * 100) + sec;
}

void Display::segOut(uint8_t s)
{
    if (lamp)
    {
        s &= 0xfe;
    }
    digitalWrite(7, LOW);
    shiftOut(6, 8, MSBFIRST, s);
    digitalWrite(7, HIGH);
}

void Display::blink(bool val)
{
    lamp = val;
}
void Display::loop()
{
    uint8_t lookupData[] = {129, 187, 73, 25, 51, 21, 5, 185, 1, 17};
    uint8_t a = count / 1000;
    uint8_t b = (count % 1000) / 100;
    uint8_t c = (count % 100) / 10;
    uint8_t d = count % 10;
    switch (scan)
    {
    case 0:
        clrPin(com4);
        segOut(lookupData[a]);
        setPin(com1);
        break;
    case 1:
        clrPin(com1);
        segOut(lookupData[b]);
        setPin(com2);
        break;
    case 2:
        clrPin(com2);
        segOut(lookupData[c]);
        setPin(com3);
        break;
    case 3:
        clrPin(com3);
        segOut(lookupData[d]);
        setPin(com4);
        break;
    }
    if (++scan > 3)
    {
        scan = 0;
    }
}
