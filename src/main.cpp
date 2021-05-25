#include "connexion.h"
#include "mqtt_publisher.h"
#include "CO2Sensor.h"
#include <Wire.h>
#include "SHTSensor.h"

#define LED GPIO_NUM_2

//Constantes wifi
const char *ssid = ""
const char *password = "";

//Paramètre serveur MQTT
const char *mqtt_server = "";
String debutTopic = "home/eai/horloge/" ;
int port = 1883;
const char *mqtt_username = "eai-test";
const char *mqtt_password = "eai";
const char *clientID = "esp32";

Connexion conn(ssid, password);

MQTTPublisher client(mqtt_server, debutTopic, port, mqtt_username, mqtt_password, clientID);

CO2Sensor co2Sensor;

SHTSensor *captTemp;

void setup(){
	pinMode(LED, OUTPUT);
	Wire.begin();
	Serial.begin(115200);
	captTemp = new SHTSensor;
	delay(1000);
	Serial.println("Initialisation du capteur de temperature");
	while (!captTemp->init())
		Serial.println("Echec de l'initialisation du capteur de temperature");
	Serial.println("Capteur SHT initialisé");
	captTemp->setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM);
	Serial.println("Initialisation du réseau");
	conn.connectToNetwork();
	Serial.println("IP locale : " + conn.getIP());
	Serial.println("Connexion au serveur MQTT");
	if (client.connectToMQTT()){
		Serial.println("Connecté au serveur MQTT !");
		Serial.setTimeout(60 * 1000);
	}
	else{
		Serial.println("Echec de la connexion au serveur MQTT...");
	}
	delay(1000);
}

void loop(){
	digitalWrite(LED, HIGH);
	if (captTemp->readSample()){
		client.sendData("temp", String(captTemp->getTemperature(), 1));
		client.sendData("rh", String(captTemp->getHumidity(), 1));
	}
	else{
		delete captTemp;
		captTemp = new SHTSensor;
		captTemp->init();
		captTemp->setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM);
	}
	client.sendData("co2", String(co2Sensor.getData()));
	Serial.println();
	digitalWrite(LED, LOW);
	delay(1000 * 60);
}