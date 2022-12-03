#include <Arduino.h>
#include <WiFiManager.h>
#include <PubSubClient.h>

WiFiManager &getWifiManager();
PubSubClient &getPubSubClient();
String getMACAddress();

void setUpWifiManager()
{
	auto &wm = getWifiManager();
	wm.setCaptivePortalEnable(true);
	wm.setEnableConfigPortal(true);
	wm.setHttpPort(8888);
	wm.setConfigPortalTimeout(120);
}

void reconnectWifi()
{
	auto &wm = getWifiManager();
	if (WiFi.status() != WL_CONNECTED) {
		Serial.println("WIFI is not connected");
		if (!wm.autoConnect()) {
			Serial.println("restart");
			ESP.restart();
		}
	}
}

WiFiManager &getWifiManager()
{
	static WiFiManager wifiManager;
	return wifiManager;
}

void setPubSubClientServer()
{
#ifdef MQTT_HOST
	getPubSubClient().setServer(MQTT_HOST, 1883);
#endif
}

void setPubSubClientServer(const char *domain, uint16_t port)
{
	getPubSubClient().setServer(domain, port);
}

PubSubClient &getPubSubClient()
{
	static WiFiClient wifiClient;
	static PubSubClient pubSubClient(wifiClient);
	return pubSubClient;
}

bool reconnectPubSubClient()
{
	auto &pubSubClient = getPubSubClient();
	if (pubSubClient.connected()) {
		return true;
	}
	if (pubSubClient.connect(getMACAddress().c_str())) {
		return true;
	} else {
		Serial.println("PubSubClient connection failed");
		return false;
	}
}

String getMACAddress()
{
	String macAddr = WiFi.macAddress();
	macAddr.replace(":", "");
	return macAddr;
}
