#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

class MQTT
{
    const char* mqtt_server = "192.168.0.5";
    const char* client_name = "ESP8266Client";
    #define MQTT_CHANNEL_COUNT 99

    public:
        void setServer()
        {
            client.setServer(mqtt_server, 1883);
        }
        void loop(char* mqttChannelList[MQTT_CHANNEL_COUNT])
        {
            if (!client.connected()) {
                reconnect(mqttChannelList);
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
        void reconnect(char* mqttChannelList[MQTT_CHANNEL_COUNT]) 
        {
            while (!client.connected()) {
                if (client.connect(client_name)) {
                    for (int i = 0; i < MQTT_CHANNEL_COUNT; i++) {
                        if (mqttChannelList[i] != NULL && strlen(mqttChannelList[i]) > 0)
                            client.subscribe(mqttChannelList[i]); 
                    }
                } else {
                    delay(500);
                }
            }
        }
};
