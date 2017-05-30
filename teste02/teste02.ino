#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
 
// Update these with values suitable for your network.
int luz1 = 6;
int luz2 = 8;

byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192,168,1,122);
IPAddress server(34,200,51,91); // IP DO BROKER

String a;

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

int service(byte* payload, unsigned int length){
  a = "";
  for(int i=0;i<length;i++){
    a += ((char)payload[i]);
  }
  
  if(a == "on"){
    return 1;
  } else{
    return 0;
  }
  
}

void callback(char* topic, byte* payload, unsigned int length) {
  //Serial.print("Message arrived [");
  //Serial.print(topic);
  //for(int j = 0;j<sizeof(topic)-2; j++){
  //  Serial.print(topic[j]);
  //}
  //Serial.print("] ");
  //for (int i=0;i<length;i++) {
  //  Serial.print((char)payload[i]);
  //}
  //Serial.print(topic);
  if (strcmp(topic, "luz1") == 0){
    //Serial.print("Luz 1 ligada");
    if(service(payload, length) == 1){
      digitalWrite(luz1, HIGH);
      mqttClient.publish("r/luz1","1");
    }else{
      digitalWrite(luz1, LOW);
      mqttClient.publish("r/luz1","0");
    }
  }else if(strcmp(topic, "luz2") == 0){
    if(service(payload, length) == 1){
      digitalWrite(luz2, HIGH);
      mqttClient.publish("r/luz2","1");
    }else{
      digitalWrite(luz2, LOW);
      mqttClient.publish("r/luz2","0");
    }
  }
  Serial.println();
}


 

 
void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("897", "sdnlditz", "iyLDGNSrLU4U")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //mqttClient.publish("outTopic","hello world");
      // ... and resubscribe
      mqttClient.subscribe("#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
 
void setup()
{

  pinMode(luz1, OUTPUT);
  pinMode(luz2, OUTPUT);
  digitalWrite(luz1, HIGH);
  digitalWrite(luz2, HIGH); 
  Serial.begin(9600);
 
  mqttClient.setServer(server, 10611);
  mqttClient.setCallback(callback);
 
  Ethernet.begin(mac, ip);
  // Allow the hardware to sort itself out
  delay(1500);
}
 
void loop()
{
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}
