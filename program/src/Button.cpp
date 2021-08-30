#include "Button.h"

void Button::loop()
{
    if (btnEnable == true)
    {
        int pinValue = digitalRead(pin);
        if (wait == LOW && pinValue == LOW)
        {
            value = LOW;
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
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}
void Button::enable()
{
    btnEnable = true;
    pinMode(pin, INPUT_PULLUP);
}

bool Button::getValue()
{
        bool ret = value;
        value = HIGH;
        return ret;
}
Button::Button(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT_PULLUP);
}

Button::~Button()
{
}