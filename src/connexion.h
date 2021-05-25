#include <WiFi.h>

class Connexion{
	private:
		const char *ssid;
		const char *psswd;
		String translateEncryptionType(wifi_auth_mode_t encryptionType);
		String getStatus(wl_status_t status);

	public :
		Connexion(const char *ssid, const char *psswd) : ssid(ssid), psswd(psswd){};
		~Connexion(){};
		void connectToNetwork();
		void disconnect();
		String getIP();
		bool isConnected();
};