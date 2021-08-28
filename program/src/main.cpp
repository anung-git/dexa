#include <Arduino.h>
#include "Button.h"
#include "CountDown.h"
#include "Display.h"
#include "TimerOne.h"
// #include "Encoder.h"

//https://l.facebook.com/l.php?u=https%3A%2F%2Fdbuezas.github.io%2Farduino-web-timers%2F%3Ffbclid%3DIwAR0nvm_teQS8hrZm7RUJoPLxb1kUKauIEoZFqoQr3dszwNydVLWvEZobZ2Y%23mcu%3DATMEGA328P%26timer%3D0&h=AT04QPLwQphbuBrsb5QWbaD5sJQGw3AUMt_1wcrC-ymblfux42M-MMgCVCiwPnIsjoUrLjVvmfKIAkNg8SGZWIqZk2X1Wk6MFFNv4uGZLr8UA0a_4ni0l5ynjmschA

// konstan variabel io
const int relay = 4;
const int clk = 3;
const int dat = 2;

volatile int counterRPM, displyRPM;

// Create Object from class
Button start = Button(A5);
Button stop = Button(A4);
Button mode = Button(2);
Button reset = Button(5);
CountDown myCounter = CountDown(1);
Display display = Display();
// Encoder potensio = Encoder(clk, dat);

void incriment()
{
  counterRPM++;
}
void rpm()
{
  displyRPM = counterRPM * 60;
  display.setRPM(displyRPM);
  counterRPM = 0;
}

void setup()
{
  pinMode(relay, OUTPUT);

  //debug
  // Serial.begin(9600);
  myCounter.setCount(0, 15);
  // potensio.setMax(15);
  // potensio.setMin(1);

  // myCounter.startCount();
  mode.changeMode(CHANGE);
  start.changeMode(FALLING);
  stop.changeMode(FALLING);

  pinMode(clk, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(clk), incriment, FALLING);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(rpm); // rpm call every 1 seconds
}
unsigned long rate;
void loop()
{

  if (start.getValue() == LOW)
  {
    myCounter.startCount();
    // mode.disable();
    // digitalWrite(relay, HIGH);
  }
  if (stop.getValue() == LOW)
  {
    myCounter.stopCount();
    // digitalWrite(relay, LOW);
    // mode.enable();
  }

  //hidupkan relay
  if (myCounter.countFinish() == HIGH)
  {
    digitalWrite(relay, LOW);
    mode.enable();
  }

  if (myCounter.isRun())
  {
    digitalWrite(relay, LOW);
  }
  else
  {
    digitalWrite(relay, HIGH);
    // if (potensio.available())
    // {
    //   myCounter.setCount(potensio.getCounter(), 0);
    // }
  }

  display.blink(myCounter.halfSec());
  display.setCounter(myCounter.getMinute(), myCounter.getSecond());

  while (rate == millis())
  {
    //object loop
    mode.loop();
    start.loop();
    stop.loop();
    reset.loop();
    // potensio.loop();
  }
  rate = millis();
  myCounter.loop();
  display.loop();
}

/************************************************************* 
 It uses Timer0 or Timer0B, and divide the clock frequncy by 1024.
 The divided frequencys period is multiplied with the
 number og counts Timer0/Timer0B can take before it overflows.
 The number is then multiplied by 61, and gives approximately
 1 second.  
 16MHz / 1024 = 15625 hz        We divide the 16 MHz clock by 1024
 1/15625 = 0.000064s            Period time
 256 * 0.000064 = 0.016384      
 0.016384 * 61 = 0.999424 ≈ 1s   
 X = 0.999424 / 0.016384 where X is approximately 61
**************************************************************/
// #include <avr/io.h>
// #include <util/delay.h>

// #define setPin(b) ( (b)<8 ? PORTD |=(1<<(b)) : PORTB |=(1<<(b-8)) )
// #define clrPin(b) ( (b)<8 ? PORTD &=~(1<<(b)) : PORTB &=~(1<<(b-8)) )
// #define setPinC(b) PORTC |=(1<<(b))
// #define clrPinC(b) PORTC &=~(1<<(b))
// #define setPinD(b) PORTD |=(1<<(b))
// #define clrPinD(b) PORTD &=~(1<<(b))
// #define setPinB(b) PORTB |=(1<<(b))
// #define clrPinB(b) PORTB &=~(1<<(b))
// //#define setPinABC(b) ( ((b)>13) ?   PORTC |=(1<<(b-13))  : ( (b)<8 ? PORTD |=(1<<(b)) : PORTB |=(1<<(b-8)) )  )

// unsigned int timeCount;
// volatile uint16_t counter;
// #define com1  13
// #define com2  12
// #define com3  11
// #define com4  10

// void segOut(uint8_t s){
//   for(byte i=0;i<6;i++){
//     if (s>127){
//       setPinC(i);
//     }
//     else{
//       clrPinC(i);
//     }
//     s=s<<1;
//   }
//     if (s>127){
//       setPinD(2);
//     }
//     else{
//       clrPinD(2);
//     }
// }

// void scan(unsigned int value){
//   uint8_t data1[]={3, 219, 133, 145, 89, 49, 33, 155, 1, 17};
//   uint8_t data2[]={33, 237, 81, 69, 141, 7, 3, 109, 1, 5};
//   uint8_t a=value/1000;
//   uint8_t b=(value%1000)/100;
//   uint8_t c=(value%100)/10;
//   uint8_t d=value%10;
//   segOut(data1[a]);
//   setPin(com1);
//  _delay_ms(1);
//   clrPin(com1);
//   segOut(data2[b]);
//   setPin(com2);
//    _delay_ms(1);
//   clrPin(com2);
//   segOut(data1[c]);
//   setPin(com3);
//    _delay_ms(1);
//   clrPin(com3);
//   segOut(data2[d]);
//   setPin(com4);
//    _delay_ms(1);
//   clrPin(com4);
// }
// int main (void){
//   #if defined(__AVR_ATmega8__)
//     TCCR0 = 0x05; // clock frequency / 1024
//     TCNT0 = 0; // Start to count from zero
//     TIMSK = 0x01; // Enable overflow interrupt

//     TCCR1B = 0X06;
//   #else // ATmega48/P, ATmega88/P, ATmega168/P, ATmega328/P
//     TCCR0B = 0x05; // clock frequency / 1024
//     OCR0B = 0x00;  // Output compare
//     TCNT0 = 0; // Set counter 0 to zero
//     TIMSK0 = 0x01; // Enable overflow interrupt
//   #endif
//   sei(); //Enable global interrupts
//   DDRC=0xFF;
//   DDRB=0x3C;
//   DDRD=0x04;
//   PORTB=0xFF;
//   PORTB=0xFF;
//   while(1){
// //    int RPM;
// //    RPM=counter * 1.25;
// //    scan(RPM);
//     scan(counter*60);
//   }
// }

// ISR(TIMER0_OVF_vect){ //Timer 0 overflow vector - this run every time timer0 overflows
//   timeCount++;
//  if(timeCount == 61) //Timer overflown for the 61th time
//   // if(timeCount == 76) //1.25 dt
//   {
//     counter = TCNT1;
//     TCNT1=0;
//     timeCount = 0;
//   }
// }
