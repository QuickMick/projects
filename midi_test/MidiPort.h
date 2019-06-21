
#ifndef __midiport__
#define __midiport__

class MidiPort
{

private:
public:
  void begin()
  {
    // Set MIDI baud rate:
    Serial.begin(31250);
  }

  void send(byte cmd, byte data)
  {
    Serial.write(cmd);
    Serial.write(data);
  }
};

#endif
