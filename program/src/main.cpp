#include <Arduino.h>
#include "Button.h"
#include "CountDown.h"
#include "Display.h"
#include "TimerOne.h"
#include "Setting.h"
#include "Buzer.h"
// konstan variabel io
const int relay = 7;
const int clk = 3;
const int dat = 2;

// interup variabel
volatile int counterRPM, displyRPM;

// Create Object from class
Buzer buzer = Buzer(6);
Button stop = Button(A4);
Button start = Button(A5);
Button up = Button(A3);
Button down = Button(A2);
Button reset = Button(A1);
Setting setting = Setting(1, 60);
CountDown myCounter = CountDown(1);
Display display = Display();

void incriment()
{
  counterRPM++;
}
void rpm()
{
  // displyRPM = counterRPM * 60;
  display.setRPM(counterRPM);
  counterRPM = 0;
}

void setup()
{
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  start.changeMode(FALLING);
  stop.changeMode(FALLING);
  reset.changeMode(FALLING);
  down.changeMode(FALLING);
  up.changeMode(FALLING);

  pinMode(clk, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(clk), incriment, FALLING);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(rpm); // rpm call every 1 seconds
  buzer.on(300);
}
unsigned long rate;
void loop()
{
  if (reset.getValue() == LOW)
  {
    buzer.on(100);
    myCounter.resetCount(setting.getValue(), 00);
  }

  if (start.getValue() == LOW)
  {
    buzer.on(100);
    myCounter.startCount();
  }
  if (stop.getValue() == LOW)
  {
    buzer.on(100);
    myCounter.stopCount();
    digitalWrite(relay, LOW);
  }

  if (myCounter.isRun())
  {
    digitalWrite(relay, HIGH);
    display.blink(myCounter.halfSec());
  }
  else
  {
    display.blink(true);
    digitalWrite(relay, LOW);

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

  display.setCounter(myCounter.getMinute(), myCounter.getSecond());

  while (rate == millis())
  {
    //object loop
    start.loop();
    stop.loop();
    reset.loop();
    up.loop();
    down.loop();
    // potensio.loop();
  }
  rate = millis();
  myCounter.loop();
  display.loop();
  buzer.loop();
}
