#include <Arduino.h>
#include <Motor.h>

#define RF 0
#define RB 1
#define LF 2
#define LB 3
#define W 4

uint32_t __delay = 500;
uint8_t res = 8;

namespace Motor {

bool forwardR = false;
bool forwardL = false;
unsigned long __timer_R = 0;
unsigned long __timer_L = 0;

void Init(int freq) {
	ledcSetup(RF, freq, res);
	ledcSetup(RB, freq, res);
	ledcSetup(LF, freq, res);
	ledcSetup(LB, freq, res);
	ledcSetup(W, freq, res);

	ledcAttachPin(21, RF);
	ledcAttachPin(19, RB);
	ledcAttachPin(18, LF);
	ledcAttachPin(5, LB);
	ledcAttachPin(17, W);
}

void force_all_off() {
	ledcWrite(RF, 0);
	ledcWrite(RB, 0);
	ledcWrite(LF, 0);
	ledcWrite(LB, 0);
	ledcWrite(W, 0);
}

void SetSpeedR(int8_t dc) {	 // -128 - 127
	// Serial.printf("R: %d\n", dc);
	if (dc < -STICK_SPAZE) {
		ledcWrite(RF, 0);

		if (forwardR) {
			Serial.println("delaying R");
			__timer_R = millis();
			forwardR = false;
		} else if (__timer_R > 0) {
			if (millis() > __timer_R + __delay) {
				__timer_R = 0;
				Serial.println("delay R complete");
			}
		} else {
			ledcWrite(RB, dc * -2);
		}

	} else if (dc > STICK_SPAZE) {
		ledcWrite(RB, 0);

		if (!forwardR) {
			Serial.println("delaying R");
			__timer_R = millis();
			forwardR = true;
		} else if (__timer_R > 0) {
			if (millis() > __timer_R + __delay) {
				__timer_R = 0;
				Serial.println("delay R complete");
			}
		} else {
			ledcWrite(RF, dc * 2);
		}

	} else {
		ledcWrite(RF, 0);
		ledcWrite(RB, 0);
	}
}

void SetSpeedL(int8_t dc) {	 // -128 - 127
	// Serial.printf("R: %d\n", dc);
	if (dc < -STICK_SPAZE) {
		ledcWrite(LF, 0);

		if (forwardL) {
			Serial.println("delaying L");
			__timer_L = millis();
			forwardL = false;
		} else if (__timer_L > 0) {
			if (millis() > __timer_L + __delay) {
				__timer_L = 0;
				Serial.println("delay L complete");
			}
		} else {
			ledcWrite(LB, dc * -2);
		}

	} else if (dc > STICK_SPAZE) {
		ledcWrite(LB, 0);

		if (!forwardL) {
			Serial.println("delaying L");
			__timer_L = millis();
			forwardL = true;
		} else if (__timer_L > 0) {
			if (millis() > __timer_L + __delay) {
				__timer_L = 0;
				Serial.println("delay L complete");
			}
		} else {
			ledcWrite(LF, dc * 2);
		}

	} else {
		ledcWrite(LF, 0);
		ledcWrite(LB, 0);
	}
}

void SetSpeedW(uint8_t dc) { ledcWrite(W, dc); }

uint8_t speedLevel = 0;	 // 0 to 9
void increaseWeaponSpeedLevel() {
	if (speedLevel < 9) {
		speedLevel++;
	}

	SetSpeedW(255 / (11 - speedLevel));
}

void decreaseWeaponSpeedLevel() {
	if (speedLevel > 0) {
		speedLevel--;
	}

	if (speedLevel == 0)
		SetSpeedW(0);
	else
		SetSpeedW(255 / (11 - speedLevel));
}

}  // namespace Motor
