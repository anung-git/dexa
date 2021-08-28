#if !defined(Display_h_)
#define Display_h_

#include <Arduino.h>
#define setPin(b) ((b) < 8 ? PORTD |= (1 << (b)) : PORTB |= (1 << (b - 8)))
#define clrPin(b) ((b) < 8 ? PORTD &= ~(1 << (b)) : PORTB &= ~(1 << (b - 8)))
#define setPinC(b) PORTC |= (1 << (b))
#define clrPinC(b) PORTC &= ~(1 << (b))
#define setPinD(b) PORTD |= (1 << (b))
#define clrPinD(b) PORTD &= ~(1 << (b))
#define setPinB(b) PORTB |= (1 << (b))
#define clrPinB(b) PORTB &= ~(1 << (b))
//#define setPinABC(b) ( ((b)>13) ?   PORTC |=(1<<(b-13))  : ( (b)<8 ? PORTD |=(1<<(b)) : PORTB |=(1<<(b-8)) )  )

#define com1 12
#define com2 11
#define com3 10
#define com4 9

class Display
{
private:
    /* data */
    bool lamp;
    uint8_t scan;
    uint8_t buf[8];
    // int count;
    void segOut(uint8_t s);


public:
    void setRPM(int rpm);
    void setCounter(unsigned char min, unsigned char sec);
    void loop();
    void blink(bool val);

    Display(/* args */);
    ~Display();
};

#endif // Display_h_