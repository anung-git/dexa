#include <Arduino.h>
#include "Button.h"
#include "CountDown.h"
#include "Display.h"
#include "TimerOne.h"
// #include "Encoder.h"

//https://l.facebook.com/l.php?u=https%3A%2F%2Fdbuezas.github.io%2Farduino-web-timers%2F%3Ffbclid%3DIwAR0nvm_teQS8hrZm7RUJoPLxb1kUKauIEoZFqoQr3dszwNydVLWvEZobZ2Y%23mcu%3DATMEGA328P%26timer%3D0&h=AT04QPLwQphbuBrsb5QWbaD5sJQGw3AUMt_1wcrC-ymblfux42M-MMgCVCiwPnIsjoUrLjVvmfKIAkNg8SGZWIqZk2X1Wk6MFFNv4uGZLr8UA0a_4ni0l5ynjmschA

// konstan variabel io
const int relay = 7;
const int clk = 3;
const int dat = 2;
const int buzer = 6;

volatile int counterRPM, displyRPM;

// Create Object from class
Button stop = Button(A4);
Button start = Button(A5);
Button up = Button(A2);
Button down = Button(A3);
Button reset = Button(A1);

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

void beepOn()
{
  digitalWrite(buzer, HIGH);
  delay(300);
  digitalWrite(buzer, LOW);
}
void setup()
{
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);
  pinMode(buzer, OUTPUT);
  digitalWrite(buzer, HIGH);
  delay(400);
  digitalWrite(buzer, LOW);
  myCounter.setCount(10, 15);

  // myCounter.startCount();
  start.changeMode(FALLING);
  stop.changeMode(FALLING);
  reset.changeMode(FALLING);

  pinMode(clk, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(clk), incriment, FALLING);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(rpm); // rpm call every 1 seconds
}
unsigned long rate;
void loop()
{
  if (reset.getValue() == LOW)
  {
    myCounter.resetCount(15, 00);
  }

  if (start.getValue() == LOW)
  {
    myCounter.startCount();
  }
  if (stop.getValue() == LOW)
  {
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
    // if (potensio.available())
    // {
    //   myCounter.setCount(potensio.getCounter(), 0);
    // }
  }

  display.setCounter(myCounter.getMinute(), myCounter.getSecond());

  while (rate == millis())
  {
    //object loop
    start.loop();
    stop.loop();
    reset.loop();
    // potensio.loop();
  }
  rate = millis();
  myCounter.loop();
  display.loop();
}
