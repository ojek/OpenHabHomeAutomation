#include <vector>
#include "..\Items\PinSwitch.cpp"
#include "..\Items\LuminositySensor.cpp"
#include "..\Items\TempHumidSensor.cpp"
#include "..\Items\LedDisplay.cpp"
#include "..\Items\MotionSensor.cpp"
#include "..\Items\SolidStateRelay.cpp"
#include "..\Items\ESP8266.cpp"

class ItemFactory
{
    IItem* GetItem(String espId, String name)
    {
        IItem* result;
        if (name == "MotionSensor")
        {
            result = new MotionSensor;
            result->setup(String("MotionSensor_" + espId), String("high"));
            return result;
        }
        if (name == "LuminositySensor")
        {
            result = new LuminositySensor;
            result->setup(String("LuminositySensor_" + espId), String("high"));
            return result;
        }
        if (name == "PinSwitch")
        {
            result = new PinSwitch;
            result->setup(String("PinSwitch_" + espId), String("medium"));
            return result;
        }
        if (name == "SolidStateRelay")
        {
            result = new SolidStateRelay;
            result->setup(String("SolidStateRelay_" + espId), String("medium"));
            return result;
        }
        if (name == "ESP8266")
        {
            result = new ESP_8266;
            result->setup(String("ESP8266_" + espId), String("low"));
            return result;
        }
        if (name == "TempHumidSensor")
        {
            result = new TempHumidSensor;
            result->setup(String("TempHumidSensor_" + espId), String("low"));
            return result;
        }
        return NULL;
    }

    public:

    std::vector<IItem*> GetItems(String espId, std::vector<String> names)
    {
        std::vector<IItem*> result;
        for(std::vector<String>::iterator it = names.begin(); it != names.end(); ++it) 
        {
            IItem* item = GetItem(espId, *it);
            if (item != NULL)
                result.push_back(item);
        }
        return result;
    }
};