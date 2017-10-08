#include "WiFi\WiFi.cpp"
#include "MQTT\MQTT.cpp"
#include "Items\NodeMCUDiode.cpp"
#include "Items\LuminositySensor.cpp"

MQTT mqtt;
NodeMCUDiode nodeMCUDiode;
LuminositySensor luminositySensor;
char* mqttChannelList[99];

void setup()
{
    pinMode(nodeMCUDiode.diode_pin, OUTPUT);
    Serial.begin(115200);

    HomeWiFi wifi;
    wifi.setup_wifi();

    mqtt.setServer();
    mqtt.setCallback(mqttCallback);

    registerItemChannels();

    setupItems();
}
 
void loop()
{
    delay(200); //safety, power saving

    mqtt.loop(mqttChannelList);

    char lux[6];
    luminositySensor.read(lux);
    mqtt.sendMsg(luminositySensor.inTopic, lux);
}

void registerItemChannels()
{
    mqttChannelList[0] = nodeMCUDiode.outTopic;
}

void setupItems()
{
    luminositySensor.setup();
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