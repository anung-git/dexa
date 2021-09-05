#if !defined(Buzer_h)
#define Buzer_h
#include <Arduino.h>

class Buzer
{
private:
    uint8_t aktif;
    int pin;
    unsigned long interval;
    unsigned long repeatduration;
    unsigned long duration;

public:
    Buzer(int pin);
    void on(unsigned long duration);
    void onRepeat(uint8_t repeat, unsigned long duration);
    void loop();
    ~Buzer();
};

#endif // Buzer_h