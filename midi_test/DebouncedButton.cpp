#include <Arduino.h>
#include "DebouncedButton.h"

bool DebouncedButton::isDown()
{
  if (buttonState == LOW)
    return false;
  else
    return true;
}
void DebouncedButton::begin(int id, int buttonPin) // void (*cb)(int))
{
  this->id = id;
  this->buttonPin = buttonPin;

  // this->onToggle = cb;
  pinMode(buttonPin, INPUT);
}

void DebouncedButton::onToggle(IBtnEventHandler *evtHandler)
{
  this->evtHandler = evtHandler;
}

void DebouncedButton::update()
{
  // read the state of the switch into a local variable:
  int reading = digitalRead(this->buttonPin);

  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != this->lastButtonState)
  {
    // reset the debouncing timer
    this->lastDebounceTime = millis();
  }

  if ((millis() - this->lastDebounceTime) <= this->debounceDelay)
    return;
  // whatever the reading is at, it's been there for longer than the debounce
  // delay, so take it as the actual current state:

  // if the button state has changed:
  if (reading != this->buttonState)
  {
    this->buttonState = reading;
    if (this->evtHandler != NULL)
    {
      this->evtHandler->handleEvent(this->id, this->buttonState);
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  this->lastButtonState = reading;
}
