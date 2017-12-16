#include "Abstract\Item.cpp"

class MotionSensor : public IItem
{
  #define	PIR_PIN	12 //D6
  bool currentState;

  public:
    void setup(String _name, String _loopPriority)
    {
      IItem::setProps(_name, _loopPriority);
      subChannels["currentState"] = "openhab/out/"+_name+"/state";
      pubChannels["currentState"] = "openhab/in/"+_name+"/state";
      pinMode(PIR_PIN, INPUT);
    }

    void loop()
    {
      int motion = digitalRead(PIR_PIN);
      currentState = (motion == HIGH);
    }

    String command(const String* args)
    {
      if (args == NULL || args[0] == NULL) return "";
      if (args[0] == "currentState") return String(currentState);
      return "";
    }
};
