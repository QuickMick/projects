
#ifndef __editorstate__
#define __editorstate__

#include <EEPROM.h>
#include "PinMap.h"
#include "DebouncedButton.h"

#include "RotaryEncoder.h"

#include "IState.h"
#include "IBtnEventHandler.h"
class EditState : public IState, public IBtnEventHandler
{

private:
  //RotaryEncoder encoder;

public:
  void setup(DebouncedButton *commonBtn)
  {
    //  encoder.begin(ENC_A, ENC_B, NULL);
  }
  void resume()
  {
  }
  void update()
  {
  }
};

#endif
