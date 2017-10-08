#include <Wire.h>
#include <math.h> 

class LuminositySensor
{
    int BH1750address = 0x23; //i2c address
    byte buff[2];

    public:
        char* outTopic = "openhab/out/LuminositySensor/state";
        char* inTopic = "openhab/in/LuminositySensor/state";
        
        void setup()
        {
            Wire.begin();
        }

        char* read()
        {
            int i;
            char buf[6];
            uint16_t val=0;
            BH1750_Init(BH1750address);
            delay(200);
           
            if(2==BH1750_Read(BH1750address))
            {
              val=((buff[0]<<8)|buff[1])/1.2;
            }
            sprintf(buf, "%u", val);
            Serial.println(buf);
            return buf;
        }

        int BH1750_Read(int address) //
        {
          int i=0;
          Wire.beginTransmission(address);
          Wire.requestFrom(address, 2);
          while(Wire.available()) //
          {
            buff[i] = Wire.read();  // receive one byte
            i++;
          }
          Wire.endTransmission();
          return i;
        }
         
        void BH1750_Init(int address)
        {
          Wire.beginTransmission(address);
          Wire.write(0x10);//1lx reolution 120ms
          Wire.endTransmission();
        }
};
