#include "Abstract\Item.cpp"

class PinSwitch : public IItem
{
    #define switch_pin 16
    #define switch_on LOW
    #define switch_off HIGH
    char* currentState = "OFF";

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
    
        virtual String command(String command)
        {
            if (command == NULL || command.length() == 0) return "";
            if (command == "ON") on();
            if (command == "OFF") off();
            if (command == "currentState") return String(currentState);
            return "";
        }
};
