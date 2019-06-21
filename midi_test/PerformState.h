
#ifndef __performstate__
#define __performstate__

#include <EEPROM.h>

#include "PinMap.h"
#include "DebouncedButton.h"
#include "MidiPort.h"

#include "IBtnEventHandler.h"
#include "IState.h"

/* 
EEPROM.read(address);
  address = address + 1;
  if (address == EEPROM.length()) {
    address = 0;
  }*/
class PerformState : public IState, public IBtnEventHandler
{

private:
  MidiPort midiPort;
  /**
 *  address of the data that indicates that there is an existing config
 */
  const static int EEPROM_INIT_ADDR = 500;

  /**
   * address of the data
   */
  const static int EEPROM_DATA_ADDR = 0;

  /**
   * number of supportet FootSwitches
   */
  const static int BTN_COUNT = 6;

  /**
   * size of the supported config per FootSwitche
   */
  const static int BTN_EEPROM_SIZE = 8;
  // constexpr static int BTNS[BTN_COUNT] = {BTN_0, BTN_1, BTN_2, BTN_3, BTN_4, BTN_5};
  DebouncedButton *buttons[BTN_COUNT];

  DebouncedButton *commonBtn;

  int commonDownTime = 0;

  /**
   * the config of the buttons
   */
  byte btnMidiConfig[BTN_COUNT * BTN_EEPROM_SIZE];

  /**
   * initializes the config of the buttons in the EEPROM
   */
  void _initEEPROM()
  {
    if (EEPROM_INIT_ADDR < EEPROM.length() && EEPROM.read(EEPROM_INIT_ADDR) != 0x1)
      return;

    EEPROM.write(EEPROM_INIT_ADDR, 0x1);

    EEPROM.put(EEPROM_DATA_ADDR, btnMidiConfig);
  }

public:
  void setup(DebouncedButton *commonBtn)
  {
    this->commonBtn = commonBtn;
    this->commonBtn->onToggle(this);
    this->_initEEPROM();
    EEPROM.get(EEPROM_DATA_ADDR, btnMidiConfig);

    int BTNS[BTN_COUNT] = {BTN_0,
                           BTN_1,
                           BTN_2,
                           BTN_3,
                           BTN_4,
                           BTN_5};
    for (int i = 0; i < PerformState::BTN_COUNT; i++)
    {
      buttons[i] = new DebouncedButton();
      buttons[i]->begin(i, BTNS[i]);
      buttons[i]->onToggle(this);
    }
  }

  void resume()
  {
    this->commonBtn->onToggle(this);
  }

  void update()
  {
    for (int i = 0; i < PerformState::BTN_COUNT; i++)
    {
      buttons[i]->update();
    }
  }

  void handleEvent(int id, int state)
  {
    if (id == 500)
    {

      return;
    }
    if (state != 1)
      return;
    int firstNodeAddr = 0;
    midiPort.send(0xC1, btnMidiConfig[id * BTN_EEPROM_SIZE + firstNodeAddr]);

    // TODO: update LED
  }
};

#endif
