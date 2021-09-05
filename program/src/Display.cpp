#include "Display.h"
#include <Arduino.h>
Display::Display(/* args */)
{
    pinMode(dataReg, OUTPUT);
    pinMode(stbReg, OUTPUT);
    pinMode(clkReg, OUTPUT);
}

Display::~Display()
{
}

void Display::setCounter(unsigned char min, unsigned char sec)
{
    int count = (min * 100) + sec;
    uint8_t lookupData[] = {129, 243, 73, 97, 51, 37, 5, 241, 1, 33};
    buf[0] = lookupData[count / 1000];
    buf[1] = lookupData[(count % 1000) / 100];
    buf[2] = lookupData[(count % 100) / 10];
    buf[3] = lookupData[count % 10];
}

void Display::setRPM(int rpm)
{

    uint8_t data1[] = {3, 111, 133, 37, 105, 49, 17, 103, 1, 33};
    uint8_t data2[] = {17, 221, 41, 137, 197, 131, 3, 217, 1, 129};
    buf[4] = data1[rpm / 1000];
    buf[5] = data2[(rpm % 1000) / 100];
    buf[6] = data1[(rpm % 100) / 10];
    buf[7] = data2[rpm % 10];
}
void Display::segOut(uint8_t s)
{

    digitalWrite(stbReg, LOW);
    shiftOut(dataReg, clkReg, MSBFIRST, s);
    digitalWrite(stbReg, HIGH);
}

void Display::tick(bool val)
{
    lamp = val;
}
void Display::blink(bool value)
{
    kedip = value;
}
void Display::loop()
{

    bool off = false;
    if (kedip)
    {
        if (millis() % 500 > 250)
        {
            off = true;
        }
    }

    switch (scan)
    {
    case 0:
        clrPin(com4);
        segOut(buf[0]);
        segOut(0xff);
        off == true ? clrPin(com1) : setPin(com1);
        break;
    case 1:
        clrPin(com1);
        segOut(buf[1]);
        segOut(0xff);
        off == true ? clrPin(com2) : setPin(com2);
        break;
    case 2:
        clrPin(com2);
        lamp == true ? segOut(buf[2] & 0xfe) : segOut(buf[2]);
        segOut(0xff);
        off == true ? clrPin(com3) : setPin(com3);
        break;
    case 3:
        clrPin(com3);
        lamp == true ? segOut(buf[3] & 0xfe) : segOut(buf[3]);
        segOut(0xff);
        off == true ? clrPin(com4) : setPin(com4);
        break;
    case 4:
        clrPin(com4);
        segOut(0xff);
        segOut(buf[4]);
        setPin(com1);
        break;
    case 5:
        clrPin(com1);
        segOut(0xff);
        segOut(buf[5]);
        setPin(com2);
        break;
    case 6:
        clrPin(com2);
        segOut(0xff);
        segOut(buf[6]);
        setPin(com3);
        break;
    case 7:
        clrPin(com3);
        segOut(0xff);
        segOut(buf[7]);
        setPin(com4);
        break;
    }
    if (++scan > 7)
    {
        scan = 0;
    }
}
