#if !defined(Setting_h)
#define Setting_h

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

#endif // Setting_h