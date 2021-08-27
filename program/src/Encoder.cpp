
#include "Encoder.h"
Encoder::Encoder(int A, int B)
{
    pinMode(A, INPUT_PULLUP);
    pinMode(B, INPUT_PULLUP);
    pinA = A;
    pinB = B;
}

int Encoder::getCounter()
{
    return counter;
}

void Encoder::resetCounter()
{
    counter = 0;
}

void Encoder::setCounter(int value)
{
    counter = value;
}

int Encoder::available()
{
    int value = update;
    update = 0;
    return value;
}
void Encoder::loop()
{

    int n = digitalRead(pinA);
    if ((pinALast == LOW) && (n == HIGH))
    {
        if (digitalRead(pinB) == LOW)
        {
            // counter--;
            if (--counter < min)
            {
                // counter = max;
                counter = min;
            }
        }
        else
        {
            // counter++;
            if (++counter > max)
            {
                // counter = min;
                counter = max;
            }
        }
        update = 1;
    }
    pinALast = n;
}

void Encoder::setMax(int value)
{
    max = value;
    if (counter > max)
    {
        counter = max;
    }
}
void Encoder::setMin(int value)
{
    min = value;
    if (counter < min)
    {
        counter = min;
    }
}
Encoder::~Encoder()
{
}
