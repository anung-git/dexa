#include "CircularEprom.h"
class Setting
{
private:
    CircularEprom memori = CircularEprom();
    int value;
    int max, min;

public:
    void increment();
    void decrement();
    int getValue();
    Setting(int min, int max);
    ~Setting();
};
