#include "CircularEprom.h"

uint8_t CircularEprom::read()
{
    return EEPROM.read(index);
}
void CircularEprom::write(uint8_t value)
{
    EEPROM.write(index, value);
}
CircularEprom::CircularEprom()
{

    index = EEPROM.read(startIdx);     //baca alamat pointer
    uint8_t copy = EEPROM.read(index); //
    index++;
    if (index > 255 || index < 2)
    {
        index = 2;
    }
    EEPROM.write(startIdx, index); // simpan alamat pointer
    EEPROM.write(index, copy);
}

CircularEprom::~CircularEprom()
{
}
