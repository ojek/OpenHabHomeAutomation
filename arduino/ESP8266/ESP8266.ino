#include "WiFi\WiFi.cpp"
#include "MQTT\MQTT.cpp"
#include "Other\ESPHelper.cpp"
#include "Items\NodeMCUDiode.cpp"
#include "Items\LuminositySensor.cpp"
#include "Items\TempHumidSensor.cpp"
#include "Items\LedDisplay.cpp"

/*
#define D0 16
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO 
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)
*/

ESPHelper espHelper;
MQTT mqtt;
NodeMCUDiode nodeMCUDiode;
LuminositySensor luminositySensor;
TempHumidSensor tempHumidSensor;
LedDisplay ledDisplay;

char* mqttChannelList[99];
float tempHumid[2] = {0,0};
double lux;

void setup()
{
    pinMode(nodeMCUDiode.diode_pin, OUTPUT);
    Serial.begin(115200);

    HomeWiFi wifi;
    wifi.setup_wifi();

    mqtt.setServer();
    mqtt.setCallback(mqttCallback);

    espHelper.setup();

    registerItemChannels();
    setupItems();
}
 
void loop()
{
    delay(200); //safety, power saving

    mqtt.loop(mqttChannelList);
    luminositySensor.loop(&lux);
    tempHumidSensor.loop(tempHumid);
    ledDisplay.loop(String(lux));

    mqtt.sendMsg(luminositySensor.inTopic, String(lux));
    mqtt.sendMsg(tempHumidSensor.inTempTopic, String(tempHumid[0]));
    mqtt.sendMsg(tempHumidSensor.inHumidTopic, String(tempHumid[1]));
}

void registerItemChannels()
{
    mqttChannelList[0] = nodeMCUDiode.outTopic;
}

void setupItems()
{
    nodeMCUDiode.off();
    ledDisplay.setup();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) 
{
    if (strcmp(nodeMCUDiode.outTopic, topic) == 0)
    {
        if ((char)payload[0] == '0') {
            nodeMCUDiode.off();
        } else if ((char)payload[0] == '1') {
            nodeMCUDiode.on();
        }
    }
}