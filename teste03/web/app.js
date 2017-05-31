console.log("Js carregado");

// Create a client instance
client = new Paho.MQTT.Client("m13.cloudmqtt.com", 30611,"3887"); 
//Example client = new Paho.MQTT.Client("m11.cloudmqtt.com", 32903, "web_" + parseInt(Math.random() * 100, 10));

// set callback handlers
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;
var options = {
useSSL: true,
userName: "sdnlditz",
password: "iyLDGNSrLU4U",
onSuccess:onConnect,
onFailure:doFail
}

// connect the client
client.connect(options);

// called when the client connects
function onConnect() {
// Once a connection has been made, make a subscription and send a message.
console.log("onConnect");
client.subscribe("r/luz1");
client.subscribe("r/luz2");
message1 = new Paho.MQTT.Message("state");
message1.destinationName = "luz1";
message2 = new Paho.MQTT.Message("state");
message2.destinationName = "luz2";

client.send(message1);
client.send(message2); 
}

function doFail(e){
console.log(e);
}

// called when the client loses its connection
function onConnectionLost(responseObject) {
if (responseObject.errorCode !== 0) {
  console.log("onConnectionLost:"+responseObject.errorMessage);
}
}

// called when a message arrives
function onMessageArrived(message) {
	if(message.destinationName == "r/luz1"){
		$("#luz1").html(message.payloadString);
	}else if(message.destinationName == "r/luz2"){
		$("#luz2").html(message.payloadString);
	}
	console.log("onMessageArrived:"+message.payloadString);
console.log("onMessageArrived:"+message.destinationName);
}

function l1ligar(){
	$("#luz1").html("aguarde...");
	message1 = new Paho.MQTT.Message("on");
	message1.destinationName = "luz1";
	client.send(message1);
}

function l2ligar(){
	$("#luz2").html("aguarde...");
	message1 = new Paho.MQTT.Message("on");
	message1.destinationName = "luz2";
	client.send(message1);
}

function l1desligar(){
	$("#luz1").html("aguarde...");
	message1 = new Paho.MQTT.Message("off");
	message1.destinationName = "luz1";
	client.send(message1);
}

function l2desligar(){
	$("#luz2").html("aguarde...");
	message1 = new Paho.MQTT.Message("off");
	message1.destinationName = "luz2";
	client.send(message1);
}