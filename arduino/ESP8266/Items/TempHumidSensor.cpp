#include "DHT.h"
//#define DHTPIN 4 // what digital pin the DHT22 is conected to (D2)
//#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

class TempHumidSensor
{

  //3.3-5.5V DC. Typical: 5V
  //1-1.5 mA Typical in between
  //Collecting period: 2s

  DHT dht = DHT(4, DHT22); //4 - DHT pin (D2), I2C Bus SDA (data)
  float humidity;
  float temperature;
  
  public:
    char* outTempTopic = "openhab/out/TemperatureSensor/state";
    char* inTempTopic = "openhab/in/TemperatureSensor/state";
    char* outHumidTopic = "openhab/out/HumiditySensor/state";
    char* inHumidTopic = "openhab/in/HumiditySensor/state";

    void readTempHumid(float* tempHumid)
    {
      tempHumid[0] = dht.readTemperature();
      tempHumid[1] = dht.readHumidity();
    }
};
