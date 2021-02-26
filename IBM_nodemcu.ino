#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define ORG "d58l72"
#define DEVICE_TYPE "NodeMcuBoard"
#define DEVICE_ID "dempDevice"
#define TOKEN "DydaPBDZu4VX!-WtIy"


#define WIFI_AP "Newton Sir"
#define WIFI_PASSWORD "Bulb'sfather"



WiFiClient wifiClient;
char server[] = ORG ".messaging.internetofthings.ibmcloud.com";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

const char publishTopic[] = "iot-2/evt/status/fmt/json";
const char responseTopic[] = "iotdm-1/response";
const char manageTopic[] = "iotdevice-1/mgmt/manage";
const char updateTopic[] = "iotdm-1/device/update";
const char rebootTopic[] = "iotdm-1/mgmt/initiate/device/reboot";
void callback(char* publishTopic, char* payload, unsigned int payloadLength);
//WiFiClient wifiClient;
PubSubClient client(wifiClient);

int publishInterval = 30000; // 30 seconds
long lastPublishMillis;

void setup() 
{
Serial.begin(115200);
InitWiFi();
delay(10);
if (!!!client.connected()) {
Serial.print("Reconnecting client to ");
Serial.println(server);
while (!!!client.connect(clientId, authMethod, token)) {
Serial.print(".");
//delay(500);
}
Serial.println();
}
}
int counter = 0;
void loop() {

// if (millis() � lastPublishMillis > publishInterval) {
String payload = "{\"d\":";
payload += counter++;
payload += "}";
/*const size_t bufferSize = 2*JSON_OBJECT_SIZE(1) + 20;
DynamicJsonBuffer jsonBuffer(bufferSize);

const char* payload = �a�;*/

Serial.print("Sending payload: ");
Serial.println(payload);
// client.publish(publishTopic, payload);
//if(client.connected())
//{
// client.publish(publishTopic, (char *)payload.c_str());
if (client.publish(publishTopic, (char *)payload.c_str())) {
Serial.println("Publish ok");
if (!!!client.connected()) {
Serial.print("Reconnecting client to ");
Serial.println(server);
while (!!!client.connect(clientId, authMethod, token)) {
Serial.print(".");
//delay(500);
}
Serial.println();
}

} else {
Serial.println("Publish failed");
if (!!!client.connected()) {
Serial.print("Reconnecting client to ");
Serial.println(server);
while (!!!client.connect(clientId, authMethod, token)) {
Serial.print(".");
//delay(500);
}
Serial.println();
}

}
}

void InitWiFi()
{
  Serial.println("Connecting to AP ...");
  // attempt to connect to WiFi network

  WiFi.begin(WIFI_AP, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to AP");
}

//void reconnect() {
//  // Loop until we're reconnected
//  while (!client.connected()) {
//    status = WiFi.status();
//    if ( status != WL_CONNECTED) {
//      WiFi.begin(WIFI_AP, WIFI_PASSWORD);
//      while (WiFi.status() != WL_CONNECTED) {
//        delay(500);
//        Serial.print(".");
//      }
//      Serial.println("Connected to AP");
//    }
//   Serial.print("connecting client to ");
//Serial.println(server);
//    // Attempt to connect (clientId, username, password)
//    if (client.connect(clientId, authMethod, token)) {
//      Serial.println( "[DONE]" );
//    } else {
//      Serial.print( "[FAILED] [ rc = " );
//      Serial.print( client.state() );
//      Serial.println( " : retrying in 5 seconds]" );
//      // Wait 5 seconds before retrying
//      delay( 5000 );
//    }
//  }
//}

void callback(char* publishTopic, char* payload, unsigned int length) {
Serial.println("callback invoked");
}
