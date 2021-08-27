#if !defined(ENCODER_H_)
#define ENCODER_H_

#include <Arduino.h>

class Encoder
{
private:
    /* data */
    int counter;
    int pinA, pinB, pinALast = HIGH;
    int update;
    int max,min;

public:
    Encoder(int clk, int dat);
    ~Encoder();
    int getCounter();
    void resetCounter();
    void setCounter(int value);
    void loop();
    int available();
    void setMax(int value);
    void setMin(int value);
    void add(int val);
    void minus(int val);
};

#endif // ENCODER_H_
