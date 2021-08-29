#include "Buzer.h"
void Buzer::on(unsigned long duration)
{
    digitalWrite(pin, HIGH);
    this->duration = duration + millis();
}
void Buzer::loop()
{
    if (millis() > duration)
    {
        digitalWrite(pin, LOW);
    }
}

Buzer::Buzer(int pin)
{
    pinMode(pin, OUTPUT);
    this->pin = pin;
}

Buzer::~Buzer()
{
}
