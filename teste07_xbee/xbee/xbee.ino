String received;
int rele9 = 13;

void setup(){
  pinMode(rele9, OUTPUT);
  Serial.begin(9600);
}
void loop(){
  received = "";
  if(Serial.available()){
   while(Serial.available()){
    char mesagem = Serial.read();
    received += mesagem;
    delay(10);
   }
   if(received.indexOf("luz1on") >=0){
      digitalWrite(rele9,HIGH);
      Serial.println("r/luz1/on");
   }
   if(received.indexOf("luz1off") >=0){
      digitalWrite(rele9,LOW);
      Serial.println("r/luz1/off");
   }
}
}
