class NodeMCUDiode
{
    #define diode_on LOW
    #define diode_off HIGH

    public:
        int diode_pin = 16;
        char* outTopic = "openhab/out/Diode2/command";
        char* inTopic = "openhab/in/Diode2/command";

        void on() 
        {
            digitalWrite(diode_pin, diode_on);
        }
        void off() 
        {
            digitalWrite(diode_pin, diode_off);
        }
};
