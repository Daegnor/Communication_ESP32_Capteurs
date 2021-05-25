#include "mqtt_publisher.h"

MQTTPublisher::MQTTPublisher(const char *serveur, String debutTopic, int port, const char *username, const char *password, const char *clientID) : debutTopic(debutTopic), mqtt_username(username), mqtt_password(password), clientID(clientID)
{
	client = new PubSubClient(serveur, port, wifiClient);
	client->setSocketTimeout(60 * 1000);
	client->setKeepAlive(60 * 1000);
}

MQTTPublisher::~MQTTPublisher(){
	delete client;
	delete mqtt_username;
	delete mqtt_password;
	delete clientID;
};

bool MQTTPublisher::connectToMQTT()
{
	return client->connect(clientID, mqtt_username, mqtt_password);
}

void MQTTPublisher::sendData(String topic, String data){
	Serial.println("Envoie de " + data);
	while (!client->publish(String(debutTopic+topic).c_str(), data.c_str())){
		Serial.println("Echec de l'envoie, nouvelle tentative...");
		connectToMQTT();
		delay(50);
	}
	Serial.println("Données envoyées");
}