#include "PubSubClient.h" // Connect and publish to the MQTT broker
#include "WiFi.h"

class MQTTPublisher{
	private :
		WiFiClient wifiClient;
		PubSubClient *client;
		String debutTopic;
		const char *mqtt_username; // MQTT username
		const char *mqtt_password;		// MQTT password
		const char *clientID;			// MQTT client ID

	public:
		MQTTPublisher(const char *serveur, String debutTopic, int port, const char *username, const char *password, const char *clientID);
		~MQTTPublisher();
		bool connectToMQTT();
		void sendData(String topic, String data);
};