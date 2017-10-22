#include "WiFi\WiFi.cpp"
#include "MQTT\MQTT.cpp"
#include "Other\ESPHelper.cpp"
#include "Items\NodeMCUDiode.cpp"
#include "Items\LuminositySensor.cpp"
#include "Items\TempHumidSensor.cpp"
#include "Items\LedDisplay.cpp"
#include "Items\MotionSensor.cpp"
#include "Items\SolidStateRelay.cpp"

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
MotionSensor motionSensor;
SolidStateRelay solidStateRelay;
char* mqttChannelList[2];

float tempHumid[2] = {0,0};
double lux;
bool isMotion;

void setup()
{
    Serial.begin(115200);

    HomeWiFi wifi;
    wifi.setup_wifi();
    espHelper.setup();

    getItemChannels(mqttChannelList);
    mqtt.setup(mqttChannelList, mqttCallback);

    setupItems();
}
 
void loop()
{
    delay(200); //safety, power saving

    mqtt.loop();
    motionSensor.loop(&isMotion);
    luminositySensor.loop(&lux);
    tempHumidSensor.loop(tempHumid);
    ledDisplay.loop(String(millis()/1000));

    mqttPublish();
}

void mqttPublish()
{
    Serial.println("test");
    mqtt.sendMsg(luminositySensor.inTopic, String(lux));
    Serial.println("test1");
    mqtt.sendMsg(tempHumidSensor.inTempTopic, String(tempHumid[0]));
    mqtt.sendMsg(tempHumidSensor.inHumidTopic, String(tempHumid[1]));
    mqtt.sendMsg(motionSensor.inTopic, String(isMotion));
    mqtt.sendMsg(ledDisplay.inTopic, String(ledDisplay.currentState));
    mqtt.sendMsg(solidStateRelay.inTopic, String(solidStateRelay.currentState));
    mqtt.sendMsg(nodeMCUDiode.inTopic, String(nodeMCUDiode.currentState));
}

void getItemChannels(char** mqttChannelList)
{
    mqttChannelList[0] = nodeMCUDiode.outTopic;
    mqttChannelList[1] = solidStateRelay.outTopic;
}

void setupItems()
{
    nodeMCUDiode.setup();
    ledDisplay.setup();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) 
{
    if (payload == NULL || payload[0] == NULL)
    {
        return;
    }
    if (strcmp(nodeMCUDiode.outTopic, topic) == 0)
    {
        if ((char)payload[0] == '0') 
            nodeMCUDiode.off();
        else if ((char)payload[0] == '1') 
            nodeMCUDiode.on();
    }
    else if (strcmp(solidStateRelay.outTopic, topic) == 0)
    {
        if ((char)payload[0] == '0') 
            solidStateRelay.off();
        else if ((char)payload[0] == '1') 
            solidStateRelay.on();
    }
}