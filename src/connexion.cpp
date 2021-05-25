#include "connexion.h"

String Connexion::translateEncryptionType(wifi_auth_mode_t encryptionType){
	switch (encryptionType){
		case (WIFI_AUTH_OPEN):
			return "Open";
		case (WIFI_AUTH_WEP):
			return "WEP";
		case (WIFI_AUTH_WPA_PSK):
			return "WPA_PSK";
		case (WIFI_AUTH_WPA2_PSK):
			return "WPA2_PSK";
		case (WIFI_AUTH_WPA_WPA2_PSK):
			return "WPA_WPA2_PSK";
		case (WIFI_AUTH_WPA2_ENTERPRISE):
			return "WPA2_ENTERPRISE";
		case (WIFI_AUTH_MAX):
			return "WIFI_AUTH_MAX";
	}
	return "";
}

String Connexion::getStatus(wl_status_t status){
	switch(status){
		case WL_IDLE_STATUS :
			return "WL_IDLE_STATUS";
		case WL_NO_SSID_AVAIL:
			return "WL_NO_SSID_AVAIL";
		case WL_SCAN_COMPLETED:
			return "WL_SCAN_COMPLETED";
		case WL_CONNECTED:
			return "WL_CONNECTED";
		case WL_CONNECT_FAILED:
			return "WL_CONNECT_FAILED";
		case WL_CONNECTION_LOST:
			return "WL_CONNECTION_LOST";
		case WL_DISCONNECTED:
			return "WL_DISCONNECTED";
	}
	return "";
}

void Connexion::connectToNetwork(){
	WiFi.begin(ssid, psswd);
	while (WiFi.status() != WL_CONNECTED){
		delay(5000);
		String s = "Connexion au réseau ";
		s += ssid;
		Serial.println(s+"...");
	}

	Serial.println("Connecté");
}

void Connexion::disconnect(){
	Serial.println("Déconnexion du wifi");
	WiFi.disconnect(true);
}

String Connexion::getIP(){
	return WiFi.localIP().toString();
}

bool Connexion::isConnected(){return WiFi.status() == WL_CONNECTED;}