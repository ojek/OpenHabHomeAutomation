#include <ESP8266WiFi.h>

class HomeWiFi
{
    const char* ssid = "multimedia_test";
    const char* password = "1234567890";
    int status = WL_IDLE_STATUS;

    public:
    void setup_wifi() 
    {
        delay(10);
        WiFi.mode(WIFI_STA);
    
        // attempt to connect to Wifi network:
        while ( status != WL_CONNECTED) {
            status = WiFi.begin(ssid, password);

            // wait 10 seconds for connection:
            delay(10000);
        }
    }
};
