#include "Abstract\Item.cpp"

class Diode : public IItem
{
    #define diode_pin 16
    #define diode_on LOW
    #define diode_off HIGH
    char* currentState;

    void on() 
    {
        digitalWrite(diode_pin, diode_on);
        currentState = "1";
    }

    void off() 
    {
        digitalWrite(diode_pin, diode_off);
        currentState = "0";
    }
    
    public:

        void setup(String _name, String _loopPriority)
        {
            IItem::setProps(_name, _loopPriority);

            pubChannels["currentState"] = "openhab/in/LedLight/state";
            subChannels["currentState"] = "openhab/out/LedLight/command";
            pinMode(diode_pin, OUTPUT);
            off();
        }
        
        void loop()
        {
    
        }
    
        String command(const String* args)
        {
            if (args == NULL || args[0] == NULL) return "";
            if (args[0] == "1") on();
            if (args[0] == "0") off();
            if (args[0] == "currentState") String(currentState);
            return "";
        }
};
