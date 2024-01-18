#include "./ADC_16.hpp"

volatile uint16_t adcValue = 0;

ISR(ADC_vect) { adcValue = ADC; }

void ADC_16::init_adc(void) {
	DDRC &= ~(1 << PC0);	// PC0-ADC0 als Eingang
	ADMUX |= (1 << REFS0);	// AVcc als Referenz, ADC0 als Eingang
	ADCSRA |= ((1 << ADEN) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) |
			   (1 << ADPS2) | (1 << ADIE) | (1 << ADATE));
}

void ADC_16::main() {
	sei();
	init_adc();
	oled_init();
	oled_gotoxy(0, 0);

	while (1) {
		oled_write_header(" ADC Wert");
		oled_font_size(1);
		oled_gotoxy(0, 4);
		oled_write("%4i", adcValue);
		oled_font_size(0);
		_delay_ms(100);
	}
}