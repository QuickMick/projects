#ifndef __btnevthandler__
#define __btnevthandler__

class IBtnEventHandler
{
public:
  virtual void handleEvent(int id, int state);
};

#endif
