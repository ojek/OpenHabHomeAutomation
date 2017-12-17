#include "WiFi\HomeWiFi.cpp"
#include "MQTT\MQTT.cpp"
#include "Other\ESPHelper.cpp"
#include "Other\ItemFactory.cpp"
#include <string.h>
#include <vector>

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

#define ESP_ID "Bedroom_Radiator"
#define LOOP_DELAY_MS 200
#define MQTT_PUBLISH_DELAY_MS_PRIORITY_HIGH 500
#define MQTT_PUBLISH_DELAY_MS_PRIORITY_MED 5000
#define MQTT_PUBLISH_DELAY_MS_PRIORITY_LOW 60000

std::vector<String> itemNames = 
    {
        //"MotionSensor",
        //"LuminositySensor",
        //"ESP8266",
        //"TempHumidSensor",
        "SolidStateRelay",
        "PinSwitch",
    };
std::vector<IItem*> items;
std::vector<String> mqttSubscribeChannels;
ESPHelper espHelper;
MQTT mqtt;

int piorityHighTimeStamp = 0;
int piorityMedTimeStamp = 0;
int piorityLowTimeStamp = 0;

void setup()
{
    Serial.begin(115200);

    HomeWiFi wifi;
    wifi.setup_wifi();
    espHelper.setup();

    setupItems();

    mqtt.setup(ESP_ID, mqttSubscribeChannels, mqttCallback);

}

void setupItems()
{
    ItemFactory itemFactory;
    items = itemFactory.GetItems(ESP_ID, itemNames);

    for(std::vector<IItem*>::iterator it = items.begin(); it != items.end(); ++it) 
    {
        for (std::map<String, String>::iterator subChannel = (*it)->subChannels.begin(); subChannel != (*it)->subChannels.end(); subChannel++ )
        {
            mqttSubscribeChannels.push_back(subChannel->second);
        }
    }
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
        _loop("high");
        priorityHit = true;
        piorityHighTimeStamp = currentTimeStamp;
    }
    if (currentTimeStamp - piorityMedTimeStamp > MQTT_PUBLISH_DELAY_MS_PRIORITY_MED)
    {
        if (priorityHit) delay(100);
        _loop("medium");
        priorityHit = true;
        piorityMedTimeStamp = currentTimeStamp;
    }
    if (currentTimeStamp - piorityLowTimeStamp > MQTT_PUBLISH_DELAY_MS_PRIORITY_LOW)
    {
        if (priorityHit) delay(100);
        _loop("low");
        priorityHit = true;
        piorityLowTimeStamp = currentTimeStamp;
    }
}

void _loop(String priority)
{
    for(std::vector<IItem*>::iterator it = items.begin(); it != items.end(); ++it) 
    {
        if ((*it)->loopPriority == priority)
        {
            (*it)->loop();
            for (std::map<String, String>::iterator pubChannel = (*it)->pubChannels.begin(); pubChannel != (*it)->pubChannels.end(); pubChannel++ )
            {
                mqtt.sendMsg(pubChannel->second, (*it)->command(std::initializer_list<String>({pubChannel->first}).begin()));
            }
        }
    }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) 
{
    if (payload == NULL || payload[0] == NULL)
    {
        return;
    }

    for(std::vector<IItem*>::iterator it = items.begin(); it != items.end(); ++it) 
    {
        for (std::map<String, String>::iterator subChannel = (*it)->subChannels.begin(); subChannel != (*it)->subChannels.end(); subChannel++ )
        {
            (*it)->command(std::initializer_list<String>({String((char*)payload).substring(0,length)}).begin());
        }
    }
}