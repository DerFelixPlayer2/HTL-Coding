#include "esp_now_util.hpp"

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
esp_now_peer_info_t peerInfo;
std::string data;

void esp_now_setup() {
	Serial.begin(9600);
	WiFi.mode(WIFI_STA);
	Serial.printf("MAC-Address: %s\n", WiFi.macAddress());

	if (esp_now_init() != ESP_OK) {
		Serial.println("Error initializing ESP-NOW");
		return;
	}

	esp_now_register_send_cb(onDataSent);
	esp_now_register_recv_cb(onDataRecv);

	// Register peer
	memcpy(peerInfo.peer_addr, broadcastAddress, 6);
	peerInfo.channel = 0;
	peerInfo.encrypt = false;

	// Add peer
	if (esp_now_add_peer(&peerInfo) != ESP_OK) {
		Serial.println("Failed to add peer");
		return;
	}

	StaticJsonDocument<256> doc;
	doc["MAC"] = WiFi.macAddress();
	doc["Name"] = "H";
	doc["other"] =
		"Hello, if you can read this you probably have really good eyes or "
		"(more likely) noone is spamming the network with messages.";
	serializeJson(doc, data);
	serializeJson(doc, Serial);
	Serial.println(data.length());
}

void esp_now_loop() {
	esp_now_send(broadcastAddress, reinterpret_cast<const uint8_t *>(&data[0]),
				 data.length());
	delay(100);
}

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
	if (status != ESP_NOW_SEND_SUCCESS) Serial.println("Delivery Fail");
}

void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
	StaticJsonDocument<256> doc;
	deserializeJson(doc, data, data_len);

	if (doc["MAC"] != nullptr && doc["Name"] != nullptr) {
		Serial.print(doc["MAC"].as<String>());
		Serial.print(": ");
		Serial.println(doc["Name"].as<String>());
	}
}
