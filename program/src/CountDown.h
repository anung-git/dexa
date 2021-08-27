#if !defined(CountDown_h_)
#define CountDown_h_

#include <Arduino.h>
class CountDown
{
private:
    /* data */
    unsigned long startMillis, millisCounter;
    unsigned char min, sec;
    bool start,half;
    bool finish = false;
    int millisToSecond(unsigned long milis);
    unsigned long secondToMillis(int second);

public:
    CountDown(unsigned int addres);
    unsigned char getMinute();
    unsigned char getSecond();
    void startCount();
    void stopCount();
    void resetCount();
    bool countFinish();
    bool halfSec();
    void setCount(unsigned char min, unsigned char sec);
    void loop();
    bool isRun();
    ~CountDown();
};

#endif // CountDown_h_
