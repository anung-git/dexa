#include "CountDown.h"
CountDown::CountDown(unsigned int addres)
{
}

CountDown::~CountDown()
{
}
unsigned char CountDown::getMinute()
{
    return this->min;
}
unsigned char CountDown::getSecond()
{
    return this->sec;
}
bool CountDown::halfSec()
{
    return half;
}
int CountDown::millisToSecond(unsigned long milis)
{
    return milis / 1000;
}
unsigned long CountDown::secondToMillis(int second)
{
    return (second * 1000L);
}

bool CountDown::isFinish()
{
    if (finish == true)
    {
        finish = false;
        return true;
    }
    return finish;
}
void CountDown::loop()
{
    unsigned long mymillis = millis();
    if (start == true)
    {
        if (mymillis >= millisCounter)
        {
            finish = true;
            start = false;
        }
        else
        {
            unsigned long bufer = millisCounter - mymillis;
            int detik = millisToSecond(bufer);
            min = detik / 60;
            sec = detik % 60;
            (mymillis % 1000) > 500 ? half = true : half = false;
        }
    }
}

void CountDown::resetCount(unsigned char min, unsigned char sec)
{
    start = false;
    this->setCount(min, sec);
}
void CountDown::startCount()
{
    if (start == false)
    {
        if (min + sec > 0)
        {
            startMillis = millis();
            millisCounter = startMillis + secondToMillis((min * 60) + sec);
            start = true;
            finish = false;
        }
    }
}
void CountDown::stopCount()
{
    start = false;
}

bool CountDown::isRun()
{
    return start;
}
void CountDown::setCount(unsigned char min, unsigned char sec)
{
    this->min = min;
    this->sec = sec;
}