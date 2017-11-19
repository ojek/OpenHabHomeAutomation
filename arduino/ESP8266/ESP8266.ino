#include "WiFi\HomeWiFi.cpp"
#include "MQTT\MQTT.cpp"
#include "Other\ESPHelper.cpp"
#include "Items\NodeMCUDiode.cpp"
#include "Items\LuminositySensor.cpp"
#include "Items\TempHumidSensor.cpp"
#include "Items\LedDisplay.cpp"
#include "Items\MotionSensor.cpp"
#include "Items\SolidStateRelay.cpp"
#include "Items\ESP8266.cpp"

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

#define LOOP_DELAY_MS 200
#define MQTT_PUBLISH_DELAY_MS_PRIORITY_HIGH 500
#define MQTT_PUBLISH_DELAY_MS_PRIORITY_MED 5000
#define MQTT_PUBLISH_DELAY_MS_PRIORITY_LOW 60000

ESPHelper espHelper;
MQTT mqtt;
NodeMCUDiode nodeMCUDiode;
LuminositySensor luminositySensor;
TempHumidSensor tempHumidSensor;
//LedDisplay ledDisplay;
MotionSensor motionSensor;
SolidStateRelay solidStateRelay;
ESP_8266 esp8266;

char* mqttChannelList[3];
int piorityHighTimeStamp = 0;
int piorityMedTimeStamp = 0;
int piorityLowTimeStamp = 0;

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
    delay(LOOP_DELAY_MS); //safety, power saving
    mqtt.loop();
        
    priorityLoop();
}

void priorityLoop()
{
    int currentTimeStamp = millis();
    bool priorityHit = false;
    if (currentTimeStamp - piorityHighTimeStamp > MQTT_PUBLISH_DELAY_MS_PRIORITY_HIGH)
    {
        loopHigh();
        priorityHit = true;
        piorityHighTimeStamp = currentTimeStamp;
    }
    if (currentTimeStamp - piorityMedTimeStamp > MQTT_PUBLISH_DELAY_MS_PRIORITY_MED)
    {
        if (priorityHit) delay(100);
        loopMed();
        priorityHit = true;
        piorityMedTimeStamp = currentTimeStamp;
    }
    if (currentTimeStamp - piorityLowTimeStamp > MQTT_PUBLISH_DELAY_MS_PRIORITY_LOW)
    {
        if (priorityHit) delay(100);
        loopLow();
        priorityHit = true;
        piorityLowTimeStamp = currentTimeStamp;
    }
}

void loopHigh()
{
    //ledDisplay.loop(String(millis()/1000));
    motionSensor.loop();
    luminositySensor.loop();

    mqttPublishHigh();
}

void loopMed()
{
    mqttPublishMed();
}

void loopLow()
{
    esp8266.loop();
    tempHumidSensor.loop();

    mqttPublishLow();
}

void mqttPublishHigh()
{
    mqtt.sendMsg(luminositySensor.inTopic, String(luminositySensor.lux));
    mqtt.sendMsg(motionSensor.inTopic, String(motionSensor.isMotion));
}

void mqttPublishMed()
{
    mqtt.sendMsg(nodeMCUDiode.inTopic, String(nodeMCUDiode.currentState));
    mqtt.sendMsg(solidStateRelay.inTopic, String(solidStateRelay.currentState));
    //mqtt.sendMsg(ledDisplay.inTopic, String(ledDisplay.currentState));
    //mqtt.sendMsg(ledDisplay.inIntensityTopic, String(ledDisplay.intensity));
}

void mqttPublishLow()
{
    mqtt.sendMsg(tempHumidSensor.inTempTopic, String(tempHumidSensor.tempHumid[0]));
    mqtt.sendMsg(tempHumidSensor.inHumidTopic, String(tempHumidSensor.tempHumid[1]));
    mqtt.sendMsg(esp8266.inFreeMemTopic, esp8266.mem_free);
    mqtt.sendMsg(esp8266.inCPUFreqTopic, esp8266.cpu_freq);
    mqtt.sendMsg(esp8266.inUptimeTopic, esp8266.uptime);
}

void getItemChannels(char** mqttChannelList)
{
    mqttChannelList[0] = nodeMCUDiode.outTopic;
    mqttChannelList[1] = solidStateRelay.outTopic;
    //mqttChannelList[2] = ledDisplay.outIntensityTopic;
}

void setupItems()
{
    nodeMCUDiode.setup();
    //ledDisplay.setup();
    solidStateRelay.setup();
    motionSensor.setup();
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
    //else if (strcmp(ledDisplay.outIntensityTopic, topic) == 0)
    //{
    //    String strPayload = String((char*)payload);
    //    ledDisplay.setIntensity(strPayload.toInt());
    //}
}