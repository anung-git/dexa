#include <Arduino.h>
#include "Button.h"
#include "CountDown.h"
#include "Display.h"
#include "TimerOne.h"
#include "Setting.h"
#include "Buzer.h"
#include "Delay.h"
// konstan variabel io
const int relay = 7;
const int encoder = 2;

// interup variabel
volatile int counterRPM;//, displyRPM;
uint8_t settingEnable = true;
// Create Object from class
Buzer buzer = Buzer(6);
Button stop = Button(A5);
Button start = Button(A4);
Button up = Button(A3);
Button down = Button(A2);
Button reset = Button(A1);
Setting setting = Setting(1, 60);
CountDown myCounter = CountDown(1);
Display display = Display();
Delay myDelay = Delay();

void incriment()
{
  counterRPM++;
}
void rpm()
{
  // uint8_t oldSREG = SREG;
  // cli();
  // display.setRPM(counterRPM *0.9375);
  display.setRPM(counterRPM );
  counterRPM = 0;
  // SREG = oldSREG;
}

void setup()
{
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  pinMode(encoder, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoder), incriment, FALLING);
  // Timer1.initialize(1000000);
  Timer1.initialize(937500);
  Timer1.attachInterrupt(rpm); // rpm call every 1 seconds
  buzer.on(100);
  myCounter.resetCount(setting.getValue(), 00);
  start.enable();
  stop.disable();
}
unsigned long rate;
void loop()
{
  if (reset.getValue() == LOW)
  {
    start.enable();
    stop.disable();
    buzer.on(100);
    myCounter.resetCount(setting.getValue(), 00);
    settingEnable = true;
  }

  if (start.getValue() == LOW)
  {
    start.disable();
    stop.enable();
    settingEnable = false;
    buzer.on(100);
    myCounter.startCount();
  }
  if (stop.getValue() == LOW)
  {
    stop.disable();
    start.enable();
    buzer.on(100);
    myCounter.stopCount();
    digitalWrite(relay, LOW);
  }

  if (myCounter.isRun())
  {
    digitalWrite(relay, HIGH);
    display.tick(myCounter.halfSec());
  }
  else
  {
    display.tick(true);
    digitalWrite(relay, LOW);

    if (settingEnable == true)
    {
      if (up.getValue() == LOW)
      {
        buzer.on(100);
        setting.increment();
        myCounter.setCount(setting.getValue(), 0);
      }
      if (down.getValue() == LOW)
      {
        buzer.on(100);
        setting.decrement();
        myCounter.setCount(setting.getValue(), 0);
      }
    }
  }
  if (myCounter.isFinish())
  {
    buzer.onRepeat(10, 200);
    myDelay.setTimeout(10000);
    display.blink(true);
  }
  if (myDelay.callBack())
  {
    //auto reset
    display.blink(false);
    start.enable();
    stop.disable();
    myCounter.resetCount(setting.getValue(), 00);
    settingEnable = true;
  }

  display.setCounter(myCounter.getMinute(), myCounter.getSecond());

  while (rate == millis())
  {
    //object loop
    start.loop();
    stop.loop();
    reset.loop();
    up.loop();
    down.loop();
  }
  rate = millis();
  while (rate == millis())
  {
    //object loop
    start.loop();
    stop.loop();
    reset.loop();
    up.loop();
    down.loop();
  }
  rate = millis();
  myCounter.loop();
  display.loop();
  buzer.loop();
  myDelay.loop();
}
