#include <Arduino.h>
#include <PS4Controller.h>

#include "Motor.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"

void printDeviceAddress() {
	const uint8_t* point = esp_bt_dev_get_address();

	for (int i = 0; i < 6; i++) {
		char str[3];

		sprintf(str, "%02X", (int)point[i]);
		Serial.print(str);

		if (i < 5) {
			Serial.print(":");
		}
	}
}

void onConnect() { Serial.println("\nConnected"); }

void onDisconnect() { Serial.println("Disconnected"); }

void removePairedDevices() {
	uint8_t pairedDeviceBtAddr[20][6];
	int count = esp_bt_gap_get_bond_device_num();
	esp_bt_gap_get_bond_device_list(&count, pairedDeviceBtAddr);
	for (int i = 0; i < count; i++) {
		esp_bt_gap_remove_bond_device(pairedDeviceBtAddr[i]);
	}
}

void setup() {
	Serial.begin(115200);

	Motor::Init();
	Motor::force_all_off();

	PS4.attachOnConnect(onConnect);
	PS4.attachOnDisconnect(onDisconnect);
	PS4.begin();

	removePairedDevices();
	printDeviceAddress();

	// Serial.println("\nWaiting for connection...");
}

void loop() {
	if (PS4.Cross()) {
		Motor::force_all_off();
	} else {
		Motor::SetSpeedR(PS4.RStickY());
		Motor::SetSpeedL(PS4.LStickY());
		Motor::SetSpeedW(PS4.R2Value());

		/*if (PS4.Up()) {
			Motor::increaseWeaponSpeedLevel();
		} else if (PS4.Down()) {
			Motor::decreaseWeaponSpeedLevel();
		} else if (Motor::speedLevel == 0) {
			Motor::SetSpeedW(PS4.R2Value());
		}*/
	}
}
