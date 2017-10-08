class NodeMCUDiode
{
    int diode_pin = 16;
    #define diode_on LOW
    #define diode_off HIGH

    public:
        const char* outTopic = "openhab/out/Diode2/command";
        const char* inTopic = "openhab/in/Diode2/command";

        void on() 
        {
            digitalWrite(diode_pin, diode_on);
        }
        void off() 
        {
            digitalWrite(diode_pin, diode_off);
        }
};
