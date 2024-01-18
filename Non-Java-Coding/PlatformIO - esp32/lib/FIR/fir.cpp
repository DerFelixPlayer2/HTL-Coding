#include "fir.hpp"

// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
	Name:       FIR_Filter.ino
	Created:	25.09.2023 09:02:47
	Author:     HP\PC
*/

#include <Arduino.h>
#include <driver/adc.h>

#define FILTER_LENGTH 5

// FIR-Filter-Koeffizienten
float filterCoefficients[FILTER_LENGTH] = {0.1, 0.2, 0.4, 0.2, 0.1};

// Eingangspuffer
float inputBuffer[FILTER_LENGTH];

volatile boolean sampling = false;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

// Funktion zum Initialisieren des Filters
void initFilter() {
	for (int i = 0; i < FILTER_LENGTH; i++) {
		inputBuffer[i] = 0;
	}
}

// Funktion zum Aktualisieren des Filters
float updateFilter(float inputValue) {
	// Eingangswert in den Puffer verschieben
	for (int i = FILTER_LENGTH - 1; i > 0; i--) {
		inputBuffer[i] = inputBuffer[i - 1];
	}
	inputBuffer[0] = inputValue;

	// Filterung durchführen
	float outputValue = 0;
	for (int i = 0; i < FILTER_LENGTH; i++) {
		outputValue += filterCoefficients[i] * inputBuffer[i];
	}

	return outputValue;
}

void IRAM_ATTR onTimer() {
	portENTER_CRITICAL_ISR(&timerMux);
	sampling = true;
	portEXIT_CRITICAL_ISR(&timerMux);
}

void fir_setup() {
	// Initialisierung des Filters
	initFilter();
	// Initialisierung des ADC
	pinMode(ADC1_CHANNEL_0, INPUT);
	adc1_config_width(ADC_WIDTH_12Bit);	 // 12-Bit Auflösung
	adc1_config_channel_atten(
		ADC1_CHANNEL_0, ADC_ATTEN_11db);  // Eingangsspannungsbereich 0-2.6V

	// Timer Interrupt für 8kHz Samplingfrequenz
	hw_timer_t* timer = timerBegin(0, 80, true);
	timerAttachInterrupt(timer, &onTimer, true);
	timerAlarmWrite(timer, 50, true);  // sampling frequency 8kHz
	timerAlarmEnable(timer);
}

void fir_loop() {
	while (!sampling)
		;

	portENTER_CRITICAL(&timerMux);
	sampling = false;
	portEXIT_CRITICAL(&timerMux);

	float inputValue = analogRead(A0);				 // Eingangswert lesen
	float filteredValue = updateFilter(inputValue);	 // Filterung durchführen
	// Skaliere den gefilterten Wert auf den DAC-Bereich (0-4095)
	int dacValue = map(filteredValue, 0, 4095, 0, 255);
	dacWrite(26, dacValue);	 // Signalausgabe am DAC
}