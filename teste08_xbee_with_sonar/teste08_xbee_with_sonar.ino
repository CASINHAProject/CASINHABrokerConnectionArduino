#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
 
// Update these with values suitable for your network.
int luz1 = 6;
int luz2 = 8;
char *s = {"l"};
char *c = {"l"};


//SoftwareSerial Xbee(0,1);

String confirmation;

byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192,168,1,122);
IPAddress server(34,200,51,91); // IP DO BROKER

String a;
String b;

EthernetClient ethClient;
PubSubClient mqttClient(ethClient);

String service(byte* payload, unsigned int length){
  a = "";
  for(int i=0;i<length;i++){
    a += ((char)payload[i]);
  }
  
  if(a == "on"){
    return "1";
  } else if (a == "off"){
    return "0";
  } else{
    return "state";
  }
  
}

int con = 0;

char *convert(int key){
  if(key){
    return {"1"};
  }
  return {"0"};
}

void callback(char* topic, byte* payload, unsigned int length) {
  if (strcmp(topic, "luz1") == 0){
     if(service(payload, length).equals("1") == true){
      c = 'l';
      Serial.println("luz1on");
      //if(con == 1){
      //  mqttClient.publish("r/luz1","1");
      //}
      
      con = 0;
    }else if(service(payload, length).equals("0") == true){
      c = 'd';
      Serial.println("luz1off");
      //mqttClient.publish("r/luz1","0");
    }else if(service(payload, length).equals("state") == true){
      mqttClient.publish("r/luz1",c);
    }
  }else if (strcmp(topic, "luz2") == 0){
     if(service(payload, length).equals("1") == true){
      s = 'l';
      Serial.println("luz2");
      //mqttClient.publish("r/luz2","1");
    }else if(service(payload, length).equals("0") == true){
      s = 'l';
      Serial.println("luz2");
      //mqttClient.publish("r/luz2","0");
    }else if(service(payload, length).equals("state") == true){
      mqttClient.publish("r/luz2",s);
    }
  }
}

 
void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    // Attempt to connect
    if (mqttClient.connect("897", "sdnlditz", "iyLDGNSrLU4U")) {
      // Once connected, publish an announcement...
      //mqttClient.publish("outTopic","hello world");
      // ... and resubscribe
      mqttClient.subscribe("#");
    } else {
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
  confirmation = "";
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
  
  if(Serial.available()){
    while(Serial.available()){
      char a = Serial.read();
      confirmation += a;
      delay(10);
    }
    //Serial.println(confirmation);
    if(confirmation.indexOf("r/sonar/") >= 0){
      Serial.println(confirmation);
      char copy[50];
      confirmation.toCharArray(copy, 60);
      mqttClient.publish("r/sonar", copy);

    }
    
  }
}
