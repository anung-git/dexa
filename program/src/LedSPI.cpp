#include "Arduino.h"
class LedSPI
{
private:
    int stb;
    int data;
    int clk;
    uint8_t buffer;
    void sendSPI();

public:
    LedSPI(int sck, int data, int stb);
    void write(uint8_t pin, uint8_t data);
    ~LedSPI();
};

void LedSPI::write(uint8_t pin, uint8_t data)
{
    if (data == LOW)
    {
        buffer &= (1 << pin);
    }
    else
    {
        buffer |= (1 << pin);
    }
    this->sendSPI();
}
void LedSPI::sendSPI()
{
    digitalWrite(stb, LOW);
    shiftOut(data, clk, LSBFIRST, buffer);
    digitalWrite(stb, HIGH);
}
LedSPI::LedSPI(int sck, int data, int stb)
{
    pinMode(sck, OUTPUT);
    pinMode(data, OUTPUT);
    pinMode(stb, OUTPUT);
    this->data = data;
    this->stb = stb;
    this->clk = clk;
}

LedSPI::~LedSPI()
{
}
