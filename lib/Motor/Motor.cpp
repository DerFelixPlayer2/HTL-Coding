#include <Arduino.h>
#include <Motor.h>

#define RF 0
#define RB 1
#define LF 2
#define LB 3
#define W 4

int min_delay = 8;
int delay_multiplier = 8;
int freq = 5000;
int res = 8;

namespace Motor {

bool forward = false;

void Init() {
	ledcSetup(RF, freq, res);
	ledcSetup(RB, freq, res);
	ledcSetup(LF, freq, res);
	ledcSetup(LB, freq, res);
	ledcSetup(W, freq, res);

	ledcAttachPin(23, RF);
	ledcAttachPin(22, RF);
	ledcAttachPin(21, RB);
	ledcAttachPin(19, RB);
	ledcAttachPin(18, LF);
	ledcAttachPin(5, LF);
	ledcAttachPin(17, LB);
	ledcAttachPin(16, LB);
	ledcAttachPin(4, W);
}

void force_all_off() {
	ledcWrite(RF, 0);
	ledcWrite(RB, 0);
	ledcWrite(LF, 0);
	ledcWrite(LB, 0);
	ledcWrite(W, 0);
}

void SetSpeedR(int8_t dc) {	 // -128 - 127
	if (dc < -5) {
		ledcWrite(RF, 0);

		if (forward) {
			delay(min_delay + (delay_multiplier / freq));
			forward = false;
		}

		ledcWrite(RB, dc * -2);

	} else if (dc > 5) {
		ledcWrite(RB, 0);

		if (!forward) {
			delay(min_delay + (delay_multiplier / freq));
			forward = true;
		}

		ledcWrite(RF, dc * 2);

	} else {
		ledcWrite(RF, 0);
		ledcWrite(RB, 0);
	}
}

void SetSpeedL(int8_t dc) {	 // -128 - 127
	if (dc < -5) {
		ledcWrite(LF, 0);

		if (forward) {
			delay(min_delay + (delay_multiplier / freq));
			forward = false;
		}

		ledcWrite(LB, dc * -2);

	} else if (dc > 5) {
		ledcWrite(LB, 0);

		if (!forward) {
			delay(min_delay + (delay_multiplier / freq));
			forward = true;
		}

		ledcWrite(LF, dc * 2);

	} else {
		ledcWrite(LF, 0);
		ledcWrite(LB, 0);
	}
}

void enableWeapon() { ledcWrite(W, 255); }

void disableWeapon() { ledcWrite(W, 0); }

}  // namespace Motor
