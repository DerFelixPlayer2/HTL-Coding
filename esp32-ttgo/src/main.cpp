#include <Arduino.h>
#include <CAN.h>
#include <TFT_eSPI.h>

#include <thread>

void showMessages(char history[4][11]);
void addHistory(char message[10]);
void clear_screen();
void sender();
void receiver();

TFT_eSPI tft = TFT_eSPI();
char array[8];
uint8_t count = 0;

void setup() {
	// Init Serial
	Serial.begin(9600);
	Serial.println("\nInitializing...");

	// Init TFT
	tft.init();
	tft.setRotation(3);
	tft.fillScreen(TFT_BLACK);
	tft.setTextSize(2);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);

	// Init CAN
	if (!CAN.begin(500E3)) {
		Serial.println("Starting CAN failed!");
		exit(-1);
	}

	// Init Threads
	// std::thread in(receiver);
	// std::thread out(sender);

	Serial.println("Initialized.");
}

void loop() { receiver(); }

void sender() {
	count = Serial.readBytesUntil(13, array, 8);

	if (count > 0) {
		CAN.beginPacket(0x12);
		for (uint8_t i = 0; i < count; i++) {
			CAN.write(array[i]);
		}
		CAN.endPacket();

		char msg[10]{'<', ' ', '\0'};
		for (int i = 2; i < 10; i++) {
			msg[i] = array[i - 2];
		}
		addHistory(msg);
	}
}

void receiver() {
	if (CAN.parsePacket() != 0 && CAN.packetId() != -1 && !CAN.packetRtr()) {
		char msg[10]{'>', ' ', '\0'};
		for (int i = 2; CAN.available() && i < 10; i++) {
			char c = CAN.read();
			msg[i] = c;
		}
		addHistory(msg);
	}
}

char history[4][11]{"", "", "", ""};
void showMessages() {
	clear_screen();
	Serial.println("Showing messages...");
	for (int i = 0; i < 4; i++) {
		tft.setCursor(0, i * 16);
		for (int j = 0; j < 10; j++) {
			Serial.print(history[i][j]);
			tft.print(history[i][j]);
		}
		Serial.println();
		// Serial.printf("Message %d: %s\n", i, history[i]);
	}
}

void addHistory(char message[10]) {
	for (int i = 3; i > 0; i--) {
		for (int j = 0; j < 10; j++) {
			history[i][j] = history[i - 1][j];
		}
		history[i][10] = '\0';
	}
	for (int j = 0; j < 10; j++) {
		history[0][j] = message[j];
	}
	history[0][10] = '\0';

	showMessages();
}

void clear_screen() { tft.fillScreen(TFT_BLACK); }