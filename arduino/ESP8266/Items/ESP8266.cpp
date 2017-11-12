extern "C" {
    #include "user_interface.h"
}

class ESP_8266
{
    #define diode_pin 16
    #define diode_on LOW
    #define diode_off HIGH

    public:
        char* outTopic = "openhab/out/ESP8266/state";
        char* inFreeMemTopic = "openhab/in/ESP8266_FreeMem/state";
        char* inCPUFreqTopic = "openhab/in/ESP8266_CPUFreq/state";
        char* inUptimeTopic = "openhab/in/ESP8266_Uptime/state";
        char* currentState;
        String mem_free = "0";
        String cpu_freq = "0";
        String uptime = "0";

        void setup()
        {
        }

        void loop() 
        {
            mem_free = String(system_get_free_heap_size());
            mem_free = String(system_get_cpu_freq());
            mem_free = String(millis()/1000);
        }
};
