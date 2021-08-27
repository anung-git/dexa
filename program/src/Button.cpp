#include "Button.h"

void Button::loop()
{
    if (btnEnable == true)
    {
        int pinValue = digitalRead(pin);
        if (wait == LOW && pinValue == LOW)
        {
            if (mode == CHANGE)
            {
                value == HIGH ? value = LOW : value = HIGH;
            }
            if (mode == FALLING)
            {
                value = LOW;
            }
            wait = HIGH;
            debounce = millis() + 80;
        }
        if (wait == HIGH && pinValue == HIGH)
        {
            if (millis() > debounce)
            {
                wait = LOW;
            }
        }
    }
}

void Button::disable()
{
    btnEnable = false;
}
void Button::enable()
{
    btnEnable = true;
}

bool Button::getValue()
{
    if (mode == FALLING)
    {
        bool ret = value;
        value = HIGH;
        return ret;
    }
    return this->value;
}
void Button::changeMode(int mode)
{
    this->mode = mode;
}
Button::Button(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

Button::~Button()
{
}