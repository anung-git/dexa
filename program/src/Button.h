#if !defined(Button_h_)
#define Button_h_

#include <Arduino.h>
class Button
{
private:
    int pin;
    bool value=HIGH;
    bool btnEnable = true;
    int wait;
    unsigned long debounce;

public:
    Button(int pin);
    ~Button();
    void disable();
    void enable();
    void reset();
    void loop();
    bool getValue();
};

#endif // Button_h_
