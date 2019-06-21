
#ifndef __state__
#define __state__

#include "DebouncedButton.h"

class IState
{

private:
public:
  virtual void setup(DebouncedButton *commonBtn);
  virtual void resume();
  virtual void update();
};

#endif
