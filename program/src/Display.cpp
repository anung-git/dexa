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
    int count = (min * 100) + sec;
    uint8_t lookupData[] = {129, 187, 73, 25, 51, 21, 5, 185, 1, 17};
    buf[0] = lookupData[count / 1000];
    buf[1] = lookupData[(count % 1000) / 100];
    buf[2] = lookupData[(count % 100) / 10];
    buf[3] = lookupData[count % 10];
}

void Display::setRPM(int rpm)
{
    uint8_t data1[] = {3, 219, 133, 145, 89, 49, 33, 155, 1, 17};
    uint8_t data2[] = {33, 237, 81, 69, 141, 7, 3, 109, 1, 5};
    buf[4] = data1[rpm / 1000];
    buf[5] = data2[(rpm % 1000) / 100];
    buf[6] = data1[(rpm % 100) / 10];
    buf[7] = data2[rpm % 10];
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
    // uint8_t lookupData[] = {129, 187, 73, 25, 51, 21, 5, 185, 1, 17};
    // uint8_t a = count / 1000;
    // uint8_t b = (count % 1000) / 100;
    // uint8_t c = (count % 100) / 10;
    // uint8_t d = count % 10;
    switch (scan)
    {
    case 0:
        clrPin(com4);
        segOut(buf[0]);
        segOut(buf[4]);
        setPin(com1);
        break;
    case 1:
        clrPin(com1);
        segOut(buf[1]);
        segOut(buf[5]);
        setPin(com2);
        break;
    case 2:
        clrPin(com2);
        segOut(buf[2]);
        segOut(buf[6]);
        setPin(com3);
        break;
    case 3:
        clrPin(com3);
        segOut(buf[3]);
        segOut(buf[7]);
        setPin(com4);
        break;
    }
    if (++scan > 3)
    {
        scan = 0;
    }
}
