class MotionSensor
{
  #define	PIR_PIN	12 //D6
  public:
    char* outTopic = "openhab/out/MotionSensor/state";
    char* inTopic = "openhab/in/MotionSensor/state";
    bool isMotion;
    
    void setup()
    {
      pinMode(PIR_PIN, INPUT);
    }

    void loop()
    {
      int motion = digitalRead(PIR_PIN);
      isMotion = (motion == HIGH);
    }
};
