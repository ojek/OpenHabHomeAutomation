#include "WiFi\WiFi.cpp"
#include "MQTT\MQTT.cpp"
#include "Items\NodeMCUDiode.cpp"

MQTT mqtt;
NodeMCUDiode nodeMCUDiode;

void setup()
{
   HomeWiFi wifi;
   wifi.setup_wifi();
   
   mqtt.setServer();
   mqtt.setCallback(mqttCallback);
}
 
void loop()
{
    mqtt.loop();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) 
{
    if (strcmp(nodeMCUDiode.outTopic, topic) == 0)
    {
        if ((char)payload[0] == '0') {
            nodeMCUDiode.off();
        } else {
            nodeMCUDiode.on();
        }
    }
}