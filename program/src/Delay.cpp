#include "Delay.h"

void Delay::loop()
{

    if (enable)
    {
        if (millis() > duration)
        {
            enable = false;
            call = true;
        }
    }
}
bool Delay::callBack()
{
    if (call)
    {
        call = false;
        return true;
    }
    else
    {
        return false;
    }
}
void Delay::setTimeout(unsigned long duration)
{
    if (duration > 0)
    {
        enable = true;
        this->duration = duration + millis();
    }
}
Delay::Delay(/* args */)
{
}

Delay::~Delay()
{
}
