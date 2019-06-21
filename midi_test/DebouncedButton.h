#ifndef __debouncedbutton__
#define __debouncedbutton__

#include "IBtnEventHandler.h"

class DebouncedButton
{

private:
  // the following variables are unsigned longs because the time, measured in
  // milliseconds, will quickly become a bigger number than can be stored in an int.
  unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
  unsigned long debounceDelay = 50;   // the debounce time; increase if the output flickers

  int buttonPin;             // the number of the pushbutton pin
  int buttonState;           // the current reading from the input pin
  int lastButtonState = LOW; // the previous reading from the input pin

  // void (*onToggle)(int);

  int id;
  IBtnEventHandler *evtHandler;

public:
  bool isDown();
  void begin(int id, int buttonPin);

  void onToggle(IBtnEventHandler *evtHandler);

  void update();
};
#endif
