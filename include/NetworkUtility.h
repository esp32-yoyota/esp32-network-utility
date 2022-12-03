#ifndef NETWORKUTILITY_H_
#define NETWORKUTILITY_H_

#include <stdint.h>
#include <PubSubClient.h>
#include <WiFiManager.h>

void setUpWifiManager();
void reconnectWifi();
void setPubSubClientServer();
void setPubSubClientServer(const char *, uint16_t);
bool reconnectPubSubClient();
String getMACAddress();
WiFiManager &getWifiManager();
PubSubClient &getPubSubClient();

#endif /* NETWORKUTILITY_H_ */