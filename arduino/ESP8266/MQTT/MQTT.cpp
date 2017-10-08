#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

class MQTT
{
    const char* mqtt_server = "192.168.0.5";

    public:
        void setServer()
        {
            client.setServer(mqtt_server, 1883);
        }
        void loop()
        {
            if (!client.connected()) {
                reconnect();
            }
            client.loop();
        }
        void subscribe(char* topic)
        {
            client.subscribe(topic);
        }
        void sendMsg(char* topic, char* message)
        {
            client.publish(topic, message);
        }
        void setCallback(MQTT_CALLBACK_SIGNATURE)
        {
            client.setCallback(callback);
        }
    private:
        void reconnect() 
        {
        }
};
