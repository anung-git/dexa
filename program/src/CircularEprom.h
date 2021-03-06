#if !defined(CircularEprom_h)
#define CircularEprom_h
#include <EEPROM.h>

class CircularEprom
{
private:
    int index;
    uint8_t value;
    const int startIdx = 1;

public:
    CircularEprom(/* args */);
    ~CircularEprom();
    uint8_t read();
    void write(uint8_t value);
};
#endif // CircularEprom_h