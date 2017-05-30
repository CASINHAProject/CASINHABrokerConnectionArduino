#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
byte mac[]    = {  0xDE, 0xED, 0xBA, 0xFE, 0xFE, 0xED };
IPAddress ip(192,168,1,122);

IPAddress server(34,200,51,91); // IP DO BROKER
int server_port = 10611; // PORTA DO BROKER

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

EthernetClient ethClient;
PubSubClient client(server, server_port, callback, ethClient);

void setup()
{
  Ethernet.begin(mac, ip);
  // Note - the default maximum packet size is 128 bytes. If the
  // combined length of clientId, username and password exceed this,
  // you will need to increase the value of MQTT_MAX_PACKET_SIZE in
  // PubSubClient.h
  Serial.begin(9600);
}

void mypombs(){
  if (client.connect("897", "sdnlditz", "iyLDGNSrLU4U")) {
    client.publish("outTopic","hello world");
    
    Serial.print("Conectado");
  }
}

void loop()
{
  
  client.loop();
  if(client.connected()!=true){
    mypombs();
  }
  client.subscribe("inTopic");
  client.print();
  //Serial.print(client);
    //
   
  
}
