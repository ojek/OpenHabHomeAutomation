#include "Abstract\Item.cpp"

class MotionSensor : public IItem
{
  #define	PIR_PIN	12 //D6
  bool currentState;

  public:
    void setup(String _name, String _loopPriority)
    {
      IItem::setProps(_name, _loopPriority);
      pubChannels["currentState"] = "openhab/in/"+_name+"/state";
      pinMode(PIR_PIN, INPUT);
    }

    void loop()
    {
      int motion = digitalRead(PIR_PIN);
      currentState = (motion == HIGH);
    }

    virtual String command(String command)
    {
      if (command == NULL || command.length() == 0) return "";
      if (command == "currentState") return String(currentState);
      return "";
    }
};
