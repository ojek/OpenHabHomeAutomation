#include <ESP8266WiFi.h>

class HomeWiFi
{
    const char* ssid = "ojek";
    const char* password = "1996199619";
    int status = WL_IDLE_STATUS;

    public:
    void setup_wifi() 
    {
        delay(10);
        WiFi.mode(WIFI_STA);
    
        for (int i = 0;;++i)
        {
            //Serial.println("WiFi connecting...");
            //Serial.println(WiFi.status());
            if (WiFi.status() == WL_CONNECTED) break;
            if (i%30==0) WiFi.begin(ssid, password);
            delay(1000);
        }
        //Serial.println("WiFi connected!");
    }
};
