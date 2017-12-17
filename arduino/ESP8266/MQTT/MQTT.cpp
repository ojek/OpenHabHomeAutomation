#include <PubSubClient.h>
#include <vector>
#include <string>

WiFiClient espClient = WiFiClient();
PubSubClient client = PubSubClient(espClient);

class MQTT
{
    const char* mqtt_server = "192.168.0.5";
    String client_name = "ESP8266_MQTT_";
    std::vector<String> mqttChannels;
    
    void reconnect() 
    {
        while (!client.connected()) {
            if (client.connect(client_name.c_str())) {
                resubscribe();
            } else {
                delay(500);
            }
        }
    }

    void resubscribe()
    {
        for (std::vector<String>::iterator mqttChannel = mqttChannels.begin(); mqttChannel != mqttChannels.end(); mqttChannel++ )
        {
            delay(10);
            client.subscribe(String(*mqttChannel).c_str()); 
            delay(10);
            client.loop();
        }
    }

    public:
        void setup(String clientID, std::vector<String> mqttChannelList, MQTT_CALLBACK_SIGNATURE)
        {
            client_name = client_name + clientID;
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
        
        void sendMsg(String topic, String message)
        {
            if (!client.connected()) {
                reconnect();
            }

            int msgLen = message.length()+1;
            char* pMsg = new char[msgLen];
            message.toCharArray(pMsg,msgLen);
            if (pMsg == NULL)
              pMsg = "";

            client.publish(topic.c_str(),pMsg);
            delete[] pMsg;
            delay(10);
            client.loop();
        }
};
