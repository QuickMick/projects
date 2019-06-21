
#ifndef __rotaryencoder__
#define __rotaryencoder__

class RotaryEncoder
{

private:
  int a;
  int b;

  int measure = LOW;
  int measureOld = LOW;
  int encVal = 50;

  int modulo = 16;

  void (*onValueChanged)(int);

public:
  int getValue()
  {
    return this->encVal;
  }

  void begin(int a, int b, void (*cb)(int))
  {
    this->a = a;
    this->b = b;
    this->onValueChanged = cb;
    pinMode(a, INPUT_PULLUP);
    pinMode(b, INPUT_PULLUP);
  }

  void update()
  {
    this->measure = digitalRead(this->a);
    if ((this->measure == HIGH) && (this->measureOld == LOW))
    {
      if (digitalRead(this->b) == HIGH)
      {
        this->encVal++;
      }
      else
      {
        this->encVal--;
      }

      this->encVal = this->encVal % this->modulo;
      //value changed here
      if (this->onValueChanged != NULL)
      {
        this->onValueChanged(this->encVal);
      }
    }
  }
};
#endif
