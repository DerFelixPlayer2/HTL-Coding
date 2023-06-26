#include <stdint.h>

namespace Motor {

void Init();

void force_all_off();

void SetSpeedR(int8_t dc);
void SetSpeedL(int8_t dc);

void enableWeapon();
void disableWeapon();

};