#include <Arduino.h>

class Buzer
{
private:
    int pin;
    unsigned long duration;

public:
    Buzer(int pin);
    void on(unsigned long duration);
    void loop();
    ~Buzer();
};
