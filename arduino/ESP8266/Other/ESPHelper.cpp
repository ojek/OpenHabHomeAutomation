#include <Wire.h>

class ESPHelper
{
  public:
    void setup()
    {
      Wire.begin(4,5);
    }
};
