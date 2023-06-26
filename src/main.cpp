#include <Arduino.h>
#include <Motor.h>
#include <PS4Controller.h>

void onData();

void setup() {
	Serial.begin(115200);

	Motor::Init();

	PS4.attachOnConnect([]() { Serial.println("\nConnected!"); });
	PS4.attach(onData);
	PS4.begin("ac:74:b1:03:38:69");
	Serial.print("Waiting for Controller to connect..");
}

void loop() {
	if (!PS4.isConnected()) {
		Serial.print(".");
		delay(500);
	} else {
	}
}

double absolute(double x) {
	if (x < 0) return -x;
	return x;
}

void onData() {
	if (PS4.Cross()) {
		Motor::force_all_off();
	} else {
		int8_t r = PS4.LStickY();
		int8_t l = PS4.LStickY();

		double factor = absolute((absolute(PS4.RStickX()) / (double)128) - 1);
		if (PS4.RStickX() < -5) {
			l *= factor;
		} else if (PS4.RStickX() > 5) {
			r *= factor;
		}

		Motor::SetSpeedR(r);
		Motor::SetSpeedL(l);

		if (PS4.Circle()) {
			Motor::disableWeapon();
		} else if (PS4.Triangle()) {
			Motor::enableWeapon();
		}
	}
}
