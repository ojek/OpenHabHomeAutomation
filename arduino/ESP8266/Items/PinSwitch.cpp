#include "Abstract\Item.cpp"

class PinSwitch : public IItem
{
    #define switch_pin 16
    #define switch_on LOW
    #define switch_off HIGH
    char* currentState;

    void on() 
    {
        digitalWrite(switch_pin, switch_on);
        currentState = "ON";
    }

    void off() 
    {
        digitalWrite(switch_pin, switch_off);
        currentState = "OFF";
    }
    
    public:

        void setup(String _name, String _loopPriority)
        {
            IItem::setProps(_name, _loopPriority);
            pubChannels["currentState"] = "openhab/in/"+_name+"/state";
            subChannels["currentState"] = "openhab/out/"+_name+"/command";
            pinMode(switch_pin, OUTPUT);
            off();
        }
        
        void loop()
        {
    
        }
    
        String command(const String* args)
        {
            if (args == NULL || args[0] == NULL) return "";
            if (args[0] == "ON") on();
            if (args[0] == "OFF") off();
            if (args[0] == "currentState") String(currentState);
            return "";
        }
};
