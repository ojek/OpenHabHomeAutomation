#include "Abstract\Item.cpp"

class SolidStateRelay : public IItem
{
  #define	SSR_PIN	0 //D3
  char* currentState;

  void on()
  {
    digitalWrite(SSR_PIN, LOW); //low to trigger active
    currentState = "ON";
  }

  void off()
  {
    digitalWrite(SSR_PIN, HIGH);
    currentState = "OFF";
  }

  public:
    void setup(String _name, String _loopPriority)
    {
      IItem::setProps(_name, _loopPriority);
      subChannels["currentState"] = "openhab/out/"+_name+"/command";
      pubChannels["currentState"] = "openhab/in/"+_name+"/state";
      pinMode(SSR_PIN, OUTPUT);
      currentState = "0";
    }

    void loop()
    {

    }

    virtual String command(String command)
    {
      if (command == NULL || command.length() == 0) return "";
      if (command == "ON") on();
      if (command == "OFF") off();
      if (command == "currentState") return String(currentState);
      return "";
    }
};
