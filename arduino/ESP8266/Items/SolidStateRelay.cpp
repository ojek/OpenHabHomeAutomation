class SolidStateRelay
{
  #define	SSR_PIN	12 //D6
  public:
    char* outTopic = "openhab/out/SolidStateRelay/command";
    char* inTopic = "openhab/in/SolidStateRelay/command";
    char* currentState;

    void setup()
    {
      pinMode(SSR_PIN, OUTPUT);
    }

    void on()
    {
      digitalWrite(SSR_PIN, HIGH);
      currentState = "1";
    }

    void off()
    {
      digitalWrite(SSR_PIN, LOW);
      currentState = "0";
    }
};
