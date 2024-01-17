#include <stdint.h>

namespace Motor {

#define STICK_SPAZE 10

void Init(int freq = 100);

void force_all_off();

void SetSpeedR(int8_t dc);
void SetSpeedL(int8_t dc);
void SetSpeedW(uint8_t dc);

// uint8_t speedLevel;
void increaseWeaponSpeedLevel();
void decreaseWeaponSpeedLevel();

};