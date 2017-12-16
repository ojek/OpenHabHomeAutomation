#include "Abstract\Item.cpp"

class SolidStateRelay : public IItem
{
  #define	SSR_PIN	0 //D3
  char* currentState;

  void on()
  {
    digitalWrite(SSR_PIN, HIGH);
    currentState = "ON";
  }

  void off()
  {
    digitalWrite(SSR_PIN, LOW);
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

    String command(const String* args)
    {
      if (args == NULL || args[0] == NULL) return "";
      if (args[0] == "ON") on();
      if (args[0] == "OFF") off();
      if (args[0] == "currentState") return String(currentState);
      return "";
    }
};
