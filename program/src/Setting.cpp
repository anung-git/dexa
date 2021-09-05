#include "Setting.h"
int Setting::getValue()
{
    return value;
}
void Setting::increment()
{
    if (++value > max)
    {
        value = max;
    }
    memori.write(value);
}
void Setting::decrement()
{
    if (--value < min)
    {
        value = min;
    }
    memori.write(value);
}
Setting::Setting(int min, int max)
{
    this->max = max;
    this->min = min;
    value = memori.read();
}

Setting::~Setting()
{
}
