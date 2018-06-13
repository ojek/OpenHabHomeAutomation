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
  float humidity = 0.0;
  float temperature = 0.0;
  
  public:
    void setup(String _name, String _loopPriority)
    {
      IItem::setProps(_name, _loopPriority);
      pubChannels["temp"] = "openhab/in/"+_name+"_Temperature/state";
      pubChannels["humid"] = "openhab/in/"+_name+"_Humidity/state";
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

    virtual String command(String command)
    {
      if (command == NULL || command.length() == 0) return "";
      if (command == "temp") return String(temperature);
      if (command == "humid") return String(humidity);
      return "";
    }
};
