#include <NetworkUtility.h>
#include <Arduino.h>
#include <unity.h>
#include <WiFiManager.h>

void setUp(void)
{
	// set stuff up here
}

void tearDown(void)
{
	// clean stuff up here
}

void testSetUpWifiManager()
{
	setUpWifiManager();
}

void testWifiReconnect()
{
	reconnectWifi();
}

void testPubsubClientSetServer()
{
	setPubSubClientServer();
}

void testPubSubClientReconnect()
{
	bool success = reconnectPubSubClient();
	TEST_ASSERT_EQUAL(true, success);
}

void testPubSubClientPublish()
{
	auto &client = getPubSubClient();
	bool success = client.publish("boot", "test");
	TEST_ASSERT_EQUAL(true, success);
}

void setup()
{
	// NOTE!!! Wait for >2 secs
	// if board doesn't support software reset via Serial.DTR/RTS
	delay(2000);
	Serial.begin(115200);
	UNITY_BEGIN(); // IMPORTANT LINE!
	RUN_TEST(testSetUpWifiManager);
	RUN_TEST(testPubsubClientSetServer);
}

uint8_t i = 0;
uint8_t max_count = 5;

void loop()
{
	if (i < max_count) {
		RUN_TEST(testWifiReconnect);
		RUN_TEST(testPubSubClientReconnect);
		RUN_TEST(testPubSubClientPublish);
		delay(500);
		i++;
	} else if (i == max_count) {
		UNITY_END(); // stop unit testing
	}
}