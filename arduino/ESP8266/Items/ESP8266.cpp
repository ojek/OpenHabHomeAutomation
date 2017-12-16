#include "Abstract\Item.cpp"
extern "C" {
    #include "user_interface.h"
}

class ESP_8266 : public IItem
{
    #define diode_pin 16
    #define diode_on LOW
    #define diode_off HIGH

    char* currentState;
    String mem_free = "0";
    String cpu_freq = "0";
    String uptime = "0";

    public:        
        void setup(String _name, String _loopPriority)
        {
            IItem::setProps(_name, _loopPriority);
            pubChannels["freemem"] = "openhab/in/"+_name+"_FreeMem/state";
            pubChannels["cpufreq"] = "openhab/in/"+_name+"_CPUFreq/state";
            pubChannels["uptime"] = "openhab/in/"+_name+"_Uptime/state";
            pubChannels["esp8266"] = "openhab/in/"+_name+"/state";
        }

        void loop()
        {
            mem_free = String(system_get_free_heap_size());
            cpu_freq = String(system_get_cpu_freq());
            uptime = String(millis()/1000);
        }

        String command(const String* args)
        {
            if (args == NULL || args[0] == NULL) return "";
            if (args[0] == "freemem") return String(mem_free);
            if (args[0] == "cpufreq") return String(cpu_freq);
            if (args[0] == "uptime") return String(uptime);
            if (args[0] == "esp8266") return String(currentState);
            return "";
        }
};
