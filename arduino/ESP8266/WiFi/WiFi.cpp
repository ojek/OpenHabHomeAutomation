#include <ESP8266WiFi.h>

class HomeWiFi
{
    const char* ssid = "multimedia_";
    const char* password = "1111111111";

    public:
    void setup_wifi() 
    {
        delay(10);
    
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
    
        while (WiFi.status() != WL_CONNECTED) 
        {
            delay(500);
        }
    }
};
