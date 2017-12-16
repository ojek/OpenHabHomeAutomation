#include "DHT.h"
#include "Abstract\Item.cpp"
#define DHTPIN 2 // what digital pin the DHT22 is conected to (D4)
#define DHTTYPE DHT22   // there are multiple kinds of DHT sensors

class TempHumidSensor : public IItem
{
  //3.3-5.5V DC. Typical: 5V
  //1-1.5 mA Typical in between
  //Collecting period: 2s

  DHT dht = DHT(DHTPIN, DHTTYPE); //4 - DHT pin (D2), I2C Bus SDA (data)
  float humidity;
  float temperature;
  
  public:
    void setup(String _name, String _loopPriority)
    {
      IItem::setProps(_name, _loopPriority);
      pubChannels["temp"] = "openhab/in/"+_name+"_Temperature/state";
      pubChannels["humid"] = "openhab/in/"+_name+"_Humidity/state";
      subChannels["temp"] = "openhab/out/"+_name+"_Temperature/state";
      subChannels["humid"] = "openhab/out/"+_name+"_Humidity/state";
    }

    void loop()
    {
      float temp,humid;
      temp = dht.readTemperature();
      humid = dht.readHumidity();
      if (temp != NULL && humid != NULL && temp > 0 && humid > 0)
      {
        temperature = temp;
        humidity = humid;
      }
    }

    String command(const String* args)
    {
      if (args == NULL || args[0] == NULL) return "";
      if (args[0] == "temp") return String(temperature);
      if (args[0] == "humid") return String(humidity);
      return "";
    }
};
