
#ifndef __sevensegment__
#define __sevensegment__

#include "CharacterMap.h"

class SevenSegment
{

private:
  CharacterMap charMap;

  int sh_cp;
  int st_cp;
  int ds;

  int lastTime = 0;
  int curRefreshIndex = 0; // current active shown digit
  static const int DIGITS = 4;
  int digits[DIGITS];

  const int *data[]; // current shown string

public:
  void begin(int sh_cp, int st_cp, int ds, int d0, int d1, int d2, int d3)
  {
    this->sh_cp = sh_cp;
    this->st_cp = st_cp;
    this->ds = ds;
    this->digits[0] = d0;
    this->digits[1] = d1;
    this->digits[2] = d2;
    this->digits[3] = d3;

    // Pins 8,9,10 auf Ausgabe
    pinMode(this->st_cp, OUTPUT);
    pinMode(this->sh_cp, OUTPUT);
    pinMode(this->ds, OUTPUT);

    for (int i = 0; i < DIGITS; i++)
    {
      pinMode(this->digits[i], OUTPUT);
      digitalWrite(this->digits[i], LOW);
    }
  }

  void write(char characters[])
  {
    for (int i = 0; i < DIGITS; i++)
    {
      this->data[i] = charMap.get(characters[i]);
    }
  }

  void update()
  {

    if (millis() < this->lastTime)
    {
      return;
    }
    this->lastTime = millis();

    digitalWrite(this->st_cp, LOW); // deactivate display

    // just show the current digit,
    // it will be shifted each frame
    for (int i = 0; i < DIGITS; i++)
    {
      int v = this->curRefreshIndex == i ? LOW : HIGH;
      digitalWrite(i, v);
    }

    const int *curCharacters = this->data[this->curRefreshIndex];
    for (int i = 0; i < CharacterMap::SEGMENTS; i++)
    {
      // Zuerst immer alle 3 Pins auf LOW
      // Aktion passiert bei Wechsel von LOW auf HIGH
      digitalWrite(this->sh_cp, LOW);
      // Jetzt den Wert der aktuellen Stelle ans Datenpin DS anlegen
      digitalWrite(this->ds, curCharacters[i]);
      // Dann ShiftPin SHCP von LOW auf HIGH, damit wird der Wert
      // am Datenpin ins Register geschoben.
      digitalWrite(this->sh_cp, HIGH);
    }

    // Wenn alle 8 Stellen im Register sind, jetzt das StorePin STCP
    // von LOW auf HIGH, damit wird Registerinhalt an Ausgabepins
    // kopiert und der Zustand an den LEDs sichtbar

    digitalWrite(this->st_cp, HIGH); // activate again

    this->curRefreshIndex++;
  }
};

#endif
