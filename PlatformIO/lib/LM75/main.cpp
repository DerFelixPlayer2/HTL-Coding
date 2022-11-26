#include "LM75.hpp"

int8_t getTemp() {
	int8_t tmp = 0;

	i2c_start(0b10010000);
	i2c_write(0x00);
	i2c_start(0b10010001);
	tmp = i2c_readNak();
	i2c_stop();

	return tmp;
}

uint8_t setOTemp(int8_t OTemp, int8_t Hyst) {
	int8_t tmp = 0;

	return tmp;
}

int LM75::main(void) {
	DDRB |= (1 << PB5);
	oled_init();
	oled_gotoxy(0, 0);

	while (1) {
		int8_t tmp = 0;
		tmp = getTemp();
		oled_gotoxy(0, 0);
		oled_write("****************");
		oled_gotoxy(0, 1);
		oled_write("*  Temperatur  *");
		oled_gotoxy(0, 2);
		oled_write("****************");
		oled_font_size(1);
		oled_gotoxy(0, 4);
		oled_write("%2i", tmp);
		oled_write("Grad C");
		oled_font_size(0);
		setOTemp(28, 26);
		_delay_ms(100);
		PORTB ^= (1 << PB5);
	}
}
