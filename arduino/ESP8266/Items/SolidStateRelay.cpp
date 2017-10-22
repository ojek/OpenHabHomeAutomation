class SolidStateRelay
{
  #define	SSR_PIN	0 //D3
  public:
    char* outTopic = "openhab/out/SolidStateRelay/command";
    char* inTopic = "openhab/in/SolidStateRelay/command";
    char* currentState;

    void setup()
    {
      pinMode(SSR_PIN, OUTPUT);
      currentState = "0";
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
