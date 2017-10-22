class NodeMCUDiode
{
    #define diode_pin 16
    #define diode_on LOW
    #define diode_off HIGH

    public:
        char* outTopic = "openhab/out/LedLight/command";
        char* inTopic = "openhab/in/LedLight/command";
        char* currentState;

        void setup()
        {
            pinMode(diode_pin, OUTPUT);
            off();
        }

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
};
