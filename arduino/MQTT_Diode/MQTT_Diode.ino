/*

 It connects to an MQTT server then:
  - on 0 switches off relay
  - on 1 switches on relay
  - on 2 switches the state of the relay

  - sends 0 on off relay
  - sends 1 on on relay

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 The current state is stored in EEPROM and restored on bootup

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "multimedia_";
const char* password = "1111111111";
const char* mqtt_server = "192.168.0.5";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const char* diodeOutTopic = "openhab/out/Diode2/command";
const char* diodeInTopic = "openhab/in/Diode2/command";
const char* lightSensorOutTopic = "openhab/out/LightSensor/state";
const char* lightSensorInTopic = "openhab/in/LightSensor/state";
const char* helloMsg = "Diode has connected!";

int diode_pin = 16;

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if (strcmp(diodeOutTopic, topic) == 0){
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '0') {
      digitalWrite(diode_pin, LOW);   // Turn the LED on (Note that LOW is the voltage level
      Serial.println("diode_pin -> LOW");
    } else {
      digitalWrite(diode_pin, HIGH);   // Turn the LED on (Note that LOW is the voltage level
      Serial.println("diode_pin -> HIGH");
    }
  }
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  digitalWrite(diode_pin, LOW);
  delay(500);
  digitalWrite(diode_pin, HIGH);
  delay(500);
  digitalWrite(diode_pin, LOW);
  delay(500);
  digitalWrite(diode_pin, HIGH);
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      client.publish(inTopic, helloMsg); // Once connected, publish an announcement...
      client.subscribe(outTopic); // ... and resubscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  pinMode(diode_pin, OUTPUT);     // Initialize the relay pin as an output
  
  digitalWrite(diode_pin, LOW);          // Blink to indicate setup
  delay(500);
  digitalWrite(diode_pin, HIGH);
  delay(500);
  
  Serial.begin(115200);
  setup_wifi();                   // Connect to wifi 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
