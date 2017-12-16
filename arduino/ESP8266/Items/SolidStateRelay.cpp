#include "Abstract\Item.cpp"

class SolidStateRelay : public IItem
{
  #define	SSR_PIN	0 //D3
  char* currentState;

  void on()
  {
    digitalWrite(SSR_PIN, HIGH);
    currentState = "1";
  }

  void off()
  {
    digitalWrite(SSR_PIN, LOW);
    currentState = "0";
  }

  public:
    void setup(String _name, String _loopPriority)
    {
      IItem::setProps(_name, _loopPriority);
      subChannels["currentState"] = "openhab/out/SolidStateRelay/command";
      pubChannels["currentState"] = "openhab/in/SolidStateRelay/state";
      pinMode(SSR_PIN, OUTPUT);
      currentState = "0";
    }

    void loop()
    {

    }

    String command(const String* args)
    {
      if (args == NULL || args[0] == NULL) return "";
      if (args[0] == "1") on();
      if (args[0] == "0") off();
      if (args[0] == "currentState") return String(currentState);
      return "";
    }
};
