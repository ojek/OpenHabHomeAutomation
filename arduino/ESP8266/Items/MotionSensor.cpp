class MotionSensor
{
  #define	PIR_PIN	0 //D3
  public:
    char* outTopic = "openhab/out/MotionSensor/state";
    char* inTopic = "openhab/in/MotionSensor/state";
    
    void setup()
    {
      pinMode(PIR_PIN, INPUT);
    }

    void loop(bool* isMotion)
    {
      int motion = digitalRead(PIR_PIN);
      *isMotion = (motion == HIGH);
    }
};
