#if !defined(Delay_h)
#define Delay_h

#include <Arduino.h>
class Delay
{
private:
    bool enable, call;
    unsigned long duration;

public:
    Delay(/* args */);
    void setTimeout(unsigned long duration);
    bool callBack();
    void loop();
    ~Delay();
};
#endif // Delay_h