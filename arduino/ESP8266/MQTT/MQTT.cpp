#include <PubSubClient.h>
WiFiClient espClient;
PubSubClient client(espClient);

class MQTT
{
    const char* mqtt_server = "192.168.0.5";
    const char* client_name = "ESP8266Client";
    #define MQTT_CHANNEL_COUNT 99
    char* mqttChannelList[MQTT_CHANNEL_COUNT];
    
    void setServer()
    {
        client.setServer(mqtt_server, 1883);
    }

    void subscribe(char* topic)
    {
        client.subscribe(topic);
    }
    
    void setCallback(MQTT_CALLBACK_SIGNATURE)
    {
        client.setCallback(callback);
    }
        
    void reconnect(char* mqttChannelList[MQTT_CHANNEL_COUNT]) 
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
        for (int i = 0; i < MQTT_CHANNEL_COUNT; i++) {
            if (mqttChannelList[i] != NULL && strlen(mqttChannelList[i]) > 0)
            {
                client.subscribe(mqttChannelList[i]); 
            }
            else
            {
                return;
            }
        }
    }

    public:
        void setup(char* mqttChannelList[], MQTT_CALLBACK_SIGNATURE)
        {
            setServer();
            client.setCallback(callback);
            mqttChannelList = mqttChannelList;
        }

        void loop()
        {
            if (!client.connected()) {
                reconnect(mqttChannelList);
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
