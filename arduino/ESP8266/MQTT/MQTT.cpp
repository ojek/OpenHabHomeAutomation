#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

class MQTT
{
    const char* mqtt_server = "192.168.0.5";
    const char* client_name = "ESP8266Client";
    char** mqttChannels;
    
    void reconnect() 
    {
        while (!client.connected()) {
            if (client.connect(client_name)) {
                resubscribe();
            } else {
                delay(500);
            }
        }
    }

    void resubscribe()
    {
        for (int i = 0; i < sizeof(mqttChannels); i++) 
        {
            if (mqttChannels[i] != NULL && strlen(mqttChannels[i]) > 0)
            {
                client.subscribe(mqttChannels[i]); 
            }
            else
            {
                return;
            }
        }
    }

    public:
        void setup(char** mqttChannelList, MQTT_CALLBACK_SIGNATURE)
        {
            client.setServer(mqtt_server, 1883);
            client.setCallback(callback);
            mqttChannels = mqttChannelList;
        }

        void loop()
        {
            if (!client.connected()) {
                reconnect();
            }
            client.loop();
        }
        
        void sendMsg(char* topic, String message, bool eraseMessage = true)
        {
            int msgLen = message.length();
            char* pMsg = new char[msgLen+1];
            if (msgLen > 0)
                strcpy(pMsg, message.c_str());
            if (pMsg == NULL || pMsg == "")
            {
              pMsg = "";
            }
            
            client.publish(topic,pMsg);
        }
};
