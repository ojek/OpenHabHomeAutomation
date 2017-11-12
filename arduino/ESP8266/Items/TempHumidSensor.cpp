#include "DHT.h"
#define DHTPIN 2 // what digital pin the DHT22 is conected to (D4)
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

class TempHumidSensor
{
  //3.3-5.5V DC. Typical: 5V
  //1-1.5 mA Typical in between
  //Collecting period: 2s

  DHT dht = DHT(DHTPIN, DHTTYPE); //4 - DHT pin (D2), I2C Bus SDA (data)
  float humidity;
  float temperature;
  
  public:
    char* outTempTopic = "openhab/out/TemperatureSensor/state";
    char* inTempTopic = "openhab/in/TemperatureSensor/state";
    char* outHumidTopic = "openhab/out/HumiditySensor/state";
    char* inHumidTopic = "openhab/in/HumiditySensor/state";
    float tempHumid[2] = {0,0};

    void loop()
    {
      float temp,humid;
      temp = dht.readTemperature();
      humid = dht.readHumidity();
      if (temp != NULL && humid != NULL && temp > 0 && humid > 0)
      {
        tempHumid[0] = temp;
        tempHumid[1] = humid;
      }
    }
};
