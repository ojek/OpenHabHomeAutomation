#include <Wire.h>
#include <math.h> 
// No active state
#define BH1750_POWER_DOWN 0x00

// Wating for measurment command
#define BH1750_POWER_ON 0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET 0x07

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE  0x10

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE_2  0x11

// Start measurement at 4lx resolution. Measurement time is approx 16ms.
#define BH1750_CONTINUOUS_LOW_RES_MODE  0x13

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE  0x20

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE_2  0x21

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_LOW_RES_MODE  0x23

class LuminositySensor
{
    //May want to change the mode in BH1750_Init()
    //Connections: D1 => SCL; D2 => SDA;
    //Power: 3.3v, typical 120uA, max 190uA

    int BH1750address = 0x23; //i2c address. Default.
    byte buff[2];
    
    int BH1750_Read(int address)
    {
      int i=0;
      Wire.beginTransmission(address);
      Wire.requestFrom(address, 2);
      while(Wire.available())
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
      Wire.write(BH1750_CONTINUOUS_HIGH_RES_MODE_2);//1lx reolution 120ms
      Wire.endTransmission();
    }

  public:
    char* outTopic = "openhab/out/LuminositySensor/state";
    char* inTopic = "openhab/in/LuminositySensor/state";

    void loop(double* val)
    {
      int i;
      BH1750_Init(BH1750address);
      delay(120);
      
      if(2==BH1750_Read(BH1750address))
      {
        *val=((buff[0]<<8)|buff[1])/1.2;
      }
    }
};
