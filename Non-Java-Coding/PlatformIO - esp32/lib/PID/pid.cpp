#include "pid.hpp"

#include <Arduino.h>
#include <PID_v1.h>
#include <driver/adc.h>
#include <driver/dac.h>

const int PIN_ADC1_0 = GPIO_NUM_36;
const int PIN_ADC1_1 = GPIO_NUM_37;
const int PIN_DAC1_0 = GPIO_NUM_25;

double Soll_Wert, Ist_Wert, Regler_Wert;
double Kp = 150, Ki = 20, Kd = 0;
PID myPID(&Ist_Wert, &Regler_Wert, &Soll_Wert, Kp, Ki, Kd, DIRECT);

void pid_setup() {
	Serial.begin(115200);
	Serial.println("PID-Regler");

	// Eingänge
	pinMode(PIN_ADC1_0, INPUT);
	pinMode(PIN_ADC1_1, INPUT);
	adc1_config_channel_atten(
		ADC1_CHANNEL_0, ADC_ATTEN_11db);  // Eingangsspannungsbereich 0-2.6V
	adc1_config_channel_atten(
		ADC1_CHANNEL_1, ADC_ATTEN_11db);  // Eingangsspannungsbereich 0-2.6V
	adc1_config_width(ADC_WIDTH_12Bit);	  // 12-Bit Auflösung

	// Regler Ausgang
	pinMode(PIN_DAC1_0, OUTPUT);
	// dac_output_voltage(DAC_CHANNEL_1, 255);
	dac_output_enable(DAC_CHANNEL_1);

	Ist_Wert = analogRead(PIN_ADC1_0);
	Soll_Wert = analogRead(PIN_ADC1_1);
	myPID.SetMode(AUTOMATIC);
	myPID.SetSampleTime(1);
	// myPID.SetOutputLimits(0, 4095);
}

void pid_loop() {
	Ist_Wert = analogRead(PIN_ADC1_0);
	Soll_Wert = analogRead(PIN_ADC1_1);

	Serial.printf("Ist: %.0f; Soll: %.0f; Regler: %.0f\n", Ist_Wert, Soll_Wert,
				  Regler_Wert);

	myPID.Compute();

	// Regler_Wert = map(Regler_Wert, 0, 4095, 0, 255);
	dacWrite(PIN_DAC1_0, Regler_Wert);
}