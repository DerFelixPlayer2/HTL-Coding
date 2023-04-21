#include "mqtt_util.hpp"

const char* topic = "DIC/Button";
const char* mqttServer = "broker.hivemq.com";

WiFiClient wifi;
PubSubClient client(wifi);

void mqtt_setup() {
	Serial.begin(9600);

	WiFi.begin("LoLGamer17", "Home.Net");

	Serial.print("Connecting to WiFi");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("\nWiFi connected");

	client.setCallback(onReceiveMessage);
	client.setServer(mqttServer, 1883);

	xTaskCreatePinnedToCore(sender, "sender", 10000, NULL, 1, NULL, 1);
}

void mqtt_loop() {
	if (!client.connected()) {
		mqtt_reconnect();
	}

	// client.publish(topic, Serial.readString().c_str());

	client.loop();
}

void mqtt_reconnect() {
	while (!client.connected()) {
		Serial.println("Attempting MQTT connection...");

		String clientId = "ESP32Client-";
		clientId += String(random(0xffff), HEX);

		if (client.connect(clientId.c_str())) {
			Serial.println("Connected");
			client.subscribe(topic);
		} else {
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			delay(5000);
		}
	}
}

void onReceiveMessage(char* topic, byte* payload, unsigned int length) {
	if (length == 0) return;

	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");

	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}

	Serial.println();
}

void sender(void* param) {
	while (true) {
		const auto msg = Serial.readString();
		if (msg.length() > 0) {
			client.publish(topic, msg.c_str(), true);
		}
		vTaskDelay(500);
	}
	vTaskDelete(NULL);
}