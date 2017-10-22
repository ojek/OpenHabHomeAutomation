class MotionSensor
{
  #define	PIR_PIN	12 //D6
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
