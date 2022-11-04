/*
 * Arduino Oscilloscope using a 128x64 OLED Version 1.20
 * The max realtime sampling rates are 17.2ksps with 2 channels and 307ksps with
 * a channel. The max equivalent time sampling rates is 16Msps with single
 * channel.
 * + Pulse Generator
 * + PWM DDS Function Generator (8 waveforms)
 * + Frequency Counter
 * Copyright (c) 2021, Siliconvalley4066
 */
/*
 * Arduino Oscilloscope using a graphic LCD
 * The max sampling rates are 4.3ksps with 2 channels and 8.6ksps with a
 * channel. Copyright (c) 2009, Noriaki Mitsunaga
 */

#include <../include/Adafruit-GFX-Library/Adafruit_GFX.h>

#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define DISPLAY_IS_SSD1306
#ifdef DISPLAY_IS_SSD1306
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#else
#include <../include/Adafruit_SH1106/Adafruit_SH1106.h>
Adafruit_SH1106 display(OLED_RESET);
#endif
#include <../include/FreqCount/FreqCount.h>
#include <../include/fix_fft/src/fix_fft.h>
#include <EEPROM.h>
#define FFT_N 128

#define txtLINE0 0
#define txtLINE1 8
#define txtLINE2 16
#define txtLINE3 24
#define txtLINE4 32

float waveFreq;	 // frequency (Hz)
float waveDuty;	 // duty ratio (%)
int dataMin;	 // buffer minimum value (smallest=0)
int dataMax;	 //        maximum value (largest=1023)
int dataAve;	 // 10 x average value (use 10x value to keep accuracy. so,
				 // max=10230)
int saveTimer;	 // remaining time for saving EEPROM
int timeExec;	 // approx. execution time of current range setting (ms)
extern byte duty;
extern byte p_range;
extern unsigned int count;
extern long ifreq;
extern byte wave_id;

const int LCD_WIDTH = 128;
const int LCD_HEIGHT = 64;
const int SAMPLES = 128;
const int DISPLNG = 100;
const int ad_ch0 = 0;  // Analog 0 pin for channel 0
const int ad_ch1 = 1;  // Analog 1 pin for channel 1
const long VREF[] = {
	49, 98, 244, 488,
	976};  // reference voltage 5.0V ->  50 :   1V/div range (100mV/dot)
		   //                        -> 100 : 0.5V/div
		   //                        -> 250 : 0.2V/div
		   //                        -> 500 : 100mV/div
		   //                       -> 1000 :  50mV/div
// const int MILLIVOL_per_dot[] = {100, 50, 20, 10, 5}; // mV/dot
#define CALPIN 10
#define CH0DCSW 2
#define CH1DCSW 4
const int ac_offset[] PROGMEM = {104, -204, -388, -450, -481};
const int MODE_ON = 0;
const int MODE_INV = 1;
const int MODE_OFF = 2;
const char ModesN[3][4] PROGMEM = {"ON", "INV", "OFF"};
const char *const Modes[3] PROGMEM = {ModesN[0], ModesN[1], ModesN[2]};
const int TRIG_AUTO = 0;
const int TRIG_NORM = 1;
const int TRIG_SCAN = 2;
const int TRIG_ONE = 3;
const char TRIG_ModesN[4][5] PROGMEM = {"Auto", "Norm", "Scan", "One"};
const char *const TRIG_Modes[4] PROGMEM = {TRIG_ModesN[0], TRIG_ModesN[1],
										   TRIG_ModesN[2], TRIG_ModesN[3]};
const int TRIG_E_UP = 0;
const int TRIG_E_DN = 1;
#define RATE_MIN 0
#define RATE_MAX 19
#define RATE_NUM 27
#define ITEM_MAX 29
const char RN[RATE_NUM][5] PROGMEM = {
	"33us", "49us", "100u", "200u", "500u", "580u", "800u", " 1ms", " 2ms",
	" 5ms", "10ms", "20ms", "50ms", "0.1s", "0.2s", "0.5s", " 1s ", " 2s ",
	" 5s ", " 10s", "0.6u", "1.3u", "3.1u", "6.3u", "13us", "31us", "63us"};
const char *const Rates[RATE_NUM] PROGMEM = {
	RN[0],	RN[1],	RN[2],	RN[3],	RN[4],	RN[5],	RN[6],	RN[7],	RN[8],
	RN[9],	RN[10], RN[11], RN[12], RN[13], RN[14], RN[15], RN[16], RN[17],
	RN[18], RN[19], RN[20], RN[21], RN[22], RN[23], RN[24], RN[25], RN[26]};
const unsigned long HREF[] PROGMEM = {
	33,		49,		100,	 200,	  500,	   580,		800,
	1000,	2000,	5000,	 10000,	  20000,   50000,	100000,
	200000, 500000, 1000000, 2000000, 5000000, 10000000};
#define RANGE_MIN 0
#define RANGE_MAX 4
#define VRF 5
const char RangesN[5][5] PROGMEM = {" 1V ", "0.5V", "0.2V", "0.1V", "50mV"};
const char *const Ranges[5] PROGMEM = {RangesN[0], RangesN[1], RangesN[2],
									   RangesN[3], RangesN[4]};
byte range0 = RANGE_MIN;
byte range1 = RANGE_MIN;
byte ch0_mode = MODE_ON, ch1_mode = MODE_ON, rate = 0;
byte trig_mode = TRIG_AUTO, trig_lv = 10, trig_edge = TRIG_E_UP, trig_ch = 0;
bool Start = true;	// Start sampling
byte item = 0;		// Default item
byte menu = 0;		// Default menu
short ch0_off = -200, ch1_off = 400;
byte data[2][SAMPLES];				  // keep the number of channels buffer
byte odat00, odat01, odat10, odat11;  // old data buffer for erase
byte sample = 0;					  // index for double buffer
bool fft_mode = false, pulse_mode = false, dds_mode = false,
	 fcount_mode = false;
bool full_screen = false;
byte info_mode = 3;	 // Text information display mode

/*
 * DDS Sine Generator mit ATMEGS 168
 * Timer2 generates the  31250 KHz Clock Interrupt
 *
 * KHM 2009 /  Martin Nawrath
 * Kunsthochschule fuer Medien Koeln
 * Academy of Media Arts Cologne
 */

extern const unsigned char sine256[], saw256[], revsaw256[], triangle[],
	noise[];
extern const unsigned char sinc5[], sinc10[], sine2harmonic[], sine3harmonic[];
extern const unsigned char trapezoid[], chainsaw[];
unsigned char *wp;
const unsigned char *const wavetable[] PROGMEM = {
	sine256, saw256, revsaw256, triangle, noise, sinc5, trapezoid, chainsaw};
const char WnameN[][5] PROGMEM = {"Sine", "Saw",  "RSaw", "Tri",
								  "Nois", "Sinc", "Trpz", "Csaw"};
const char *const Wavename[] PROGMEM = {WnameN[0], WnameN[1], WnameN[2],
										WnameN[3], WnameN[4], WnameN[5],
										WnameN[6], WnameN[7]};
long ifreq = 12255;	 // frequency * 100 for 0.01Hz resolution
byte wave_id = 0;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define DDSPin 11

const double refclk = 31372.549;  // =16MHz / 510

// variables used inside interrupt service declared as voilatile
volatile byte icnt;				 // var inside interrupt
volatile byte icnt1;			 // var inside interrupt
volatile byte c4ms;				 // counter incremented all 4ms
volatile unsigned long phaccu;	 // pahse accumulator
volatile unsigned long tword_m;	 // dds tuning word m

void dds_setup() {
	pinMode(DDSPin, OUTPUT);  // pin11= PWM  output / frequency output
	Setup_timer2();
	// disable interrupts to avoid timing distortion
	//  cbi (TIMSK0,TOIE0);             // disable Timer0 !!! delay() is now not
	//  available
	sbi(TIMSK2, TOIE2);	 // enable Timer2 Interrupt
	tword_m =
		pow(2, 32) * ifreq * 0.01 / refclk;	 // calulate DDS new tuning word
	wp = (unsigned char *)pgm_read_word(&wavetable[wave_id]);
}

void dds_close() {
	pinMode(DDSPin, INPUT_PULLUP);	// pin11= PWM output / frequency output
	TCCR2A &= 0b00111100;			// disconnect DDSPin, Mode 0 idle
	TCCR2B &= 0b11111000;			// stop clock of DDS wave generator
	//  sbi (TIMSK0,TOIE0);             // enable Timer0 !!! delay() is now
	//  available
	cbi(TIMSK2, TOIE2);	 // disable Timer2 Interrupt
}

void dds_loop() {
	double dfreq;
	update_ifrq(0);
	if (c4ms > 50) {  // timer / wait for a 200m second
		c4ms = 0;
		dfreq = (double)ifreq * 0.01;			// adjust output frequency
		cbi(TIMSK2, TOIE2);						// disble Timer2 Interrupt
		tword_m = pow(2, 32) * dfreq / refclk;	// calulate DDS new tuning word
		sbi(TIMSK2, TOIE2);						// enable Timer2 Interrupt
	}
}

void rotate_wave(bool fwd) {
	if (fwd) {
		wave_id = (wave_id + 1) % (sizeof(wavetable) / sizeof(&sine256));
	} else {
		if (wave_id > 1)
			--wave_id;
		else
			wave_id = (sizeof(wavetable) / sizeof(&sine256)) - 1;
	}
	wp = (unsigned char *)pgm_read_word(&wavetable[wave_id]);
}
//******************************************************************
// timer2 setup
// set prscaler to 1, PWM mode to phase correct PWM,  16000000/510 = 31372.55 Hz
// clock
void Setup_timer2() {
	// Timer2 Clock Prescaler to : 1
	sbi(TCCR2B, CS20);
	cbi(TCCR2B, CS21);
	cbi(TCCR2B, CS22);

	// Timer2 PWM Mode set to Phase Correct PWM
	cbi(TCCR2A, COM2A0);  // clear Compare Match
	sbi(TCCR2A, COM2A1);

	sbi(TCCR2A, WGM20);	 // Mode 1  / Phase Correct PWM
	cbi(TCCR2A, WGM21);
	cbi(TCCR2B, WGM22);
}

//******************************************************************
// Timer2 Interrupt Service at 31372,550 KHz = 32uSec
// this is the timebase REFCLOCK for the DDS generator
// FOUT = (M (REFCLK)) / (2 exp 32)
// runtime : 8 microseconds ( inclusive push and pop)
ISR(TIMER2_OVF_vect) {
	phaccu = phaccu + tword_m;	// soft DDS, phase accu with 32 bits
	icnt = phaccu >>
		   24;	// use upper 8 bits for phase accu as frequency information
				// read value fron ROM sine table and send to PWM DAC
	OCR2A = pgm_read_byte(wp + icnt);
	if (icnt1++ >= 125) {  // increment variable c4ms all 4 milliseconds
		c4ms++;
		icnt1 = 0;
	}
}

void update_ifrq(long diff) {
	long newFreq;
	int fast;
	if (diff != 0) {
		if (abs(diff) > 3) {
			fast = ifreq / 40;
		} else if (abs(diff) > 2) {
			fast = ifreq / 300;
		} else if (abs(diff) > 1) {
			fast = 25;
		} else {
			fast = 1;
		}
		if (fast < 1) fast = 1;
		newFreq = ifreq + fast * diff;
	} else {
		newFreq = ifreq;
	}
	newFreq = constrain(newFreq, 1, 999999);
	if (newFreq != ifreq) {
		ifreq = newFreq;
		dds_loop();
	}
}

void disp_dds_freq(void) {
	display.setTextColor(WHITE, BLACK);
	display.setCursor(72, 56);
	display.print((double)ifreq * 0.01, 2);
	display.print(F("Hz"));
}

void disp_dds_wave(void) {
	char str[5];
	display.print(strcpy_P(str, (char *)pgm_read_word(&(Wavename[wave_id]))));
}

/*
 * Copyright (c) 2020, radiopench http://radiopench.blog96.fc2.com/
 */

// int dataMin;                   // buffer minimum value (smallest=0)
// int dataMax;                   //        maximum value (largest=1023)
// int dataAve;                   // 10 x average value (use 10x value to keep
// accuracy. so, max=10230) int dataRms;                   // 10x rms. value

void dataAnalize() {  // 波形の分析 get various information from wave form
	long d;
	long sum = 0;
	byte *waveBuff = data[sample + 0];

	// search max and min value
	dataMin = 255;						 // min value initialize to big number
	dataMax = 0;						 // max value initialize to small number
	for (int i = 0; i < SAMPLES; i++) {	 // serach max min value
		d = waveBuff[i];
		sum = sum + d;
		if (d < dataMin) {	// update min
			dataMin = d;
		}
		if (d > dataMax) {	// updata max
			dataMax = d;
		}
	}

	// calculate average
	dataAve = (10 * sum + (SAMPLES / 2)) /
			  SAMPLES;	// Average value calculation (calculated by 10 times to
						// improve accuracy)

	// 実効値の計算 rms value calc.
	//  sum = 0;
	//  for (int i = 0; i < SAMPLES; i++) {     // バッファ全体に対し to all
	//  buffer
	//    d = waveBuff[i] - (dataAve + 5) / 10;  //
	//    オーバーフロー防止のため生の値で計算(10倍しない） sum += d * d; //
	//    二乗和を積分
	//  }
	//  dataRms = sqrt(sum / SAMPLES);          // 実効値の10倍の値 get rms
	//  value
}

void freqDuty() {  // 周波数とデューティ比を求める detect frequency and duty
				   // cycle value from waveform data
	int swingCenter;	 // center of wave (half of p-p)
	float p0 = 0;		 // 1-st posi edge
	float p1 = 0;		 // total length of cycles
	float p2 = 0;		 // total length of pulse high time
	float pFine = 0;	 // fine position (0-1.0)
	float lastPosiEdge;	 // last positive edge position

	float pPeriod;	// pulse period
	float pWidth;	// pulse width

	int p1Count = 0;  // wave cycle count
	int p2Count = 0;  // High time count

	boolean a0Detected = false;
	//  boolean b0Detected = false;
	boolean posiSerch = true;  // true when serching posi edge

	swingCenter = (3 * (dataMin + dataMax)) / 2;  // calculate wave center value

	for (int i = 1; i < SAMPLES - 2; i++) {	 // scan all over the buffer
		if (posiSerch == true) {			 // posi slope (frequency serch)
			if ((sum3(i) <= swingCenter) &&
				(sum3(i + 1) >
				 swingCenter)) {  // if across the center when rising (+-3data
								  // used to eliminate noize)
				pFine =
					(float)(swingCenter - sum3(i)) /
					((swingCenter - sum3(i)) +
					 (sum3(i + 1) - swingCenter));	// fine cross point calc.
				if (a0Detected == false) {			// if 1-st cross
					a0Detected = true;				// set find flag
					p0 = i + pFine;	 // save this position as startposition
				} else {
					p1 = i + pFine -
						 p0;  // record length (length of n*cycle time)
					p1Count++;
				}
				lastPosiEdge = i + pFine;  // record location for Pw calcration
				posiSerch = false;
			}
		} else {  // nega slope serch (duration serch)
			if ((sum3(i) >= swingCenter) &&
				(sum3(i + 1) <
				 swingCenter)) {  // if across the center when falling (+-3data
								  // used to eliminate noize)
				pFine = (float)(sum3(i) - swingCenter) /
						((sum3(i) - swingCenter) + (swingCenter - sum3(i + 1)));
				if (a0Detected == true) {
					p2 = p2 +
						 (i + pFine - lastPosiEdge);  // calucurate pulse width
													  // and accumurate it
					p2Count++;
				}
				posiSerch = true;
			}
		}
	}

	if (p1Count > 0 && p2Count > 0) {
		pPeriod = p1 / p1Count;	 // pulse period
		pWidth = p2 / p2Count;	 // pulse width
	} else {
		pPeriod = 1.0e+37;	// set huge period to get 0Hz
		pWidth = 0;			// pulse width
	}

	float fhref;
	if (rate > RATE_MAX) {	// Equivalent Time sampling
		fhref = ethref();
	} else {
		fhref = (float)pgm_read_dword(HREF + rate);
	}
	waveFreq = 10.0e6 / (fhref * pPeriod);	// frequency
	waveDuty = 100.0 * pWidth / pPeriod;	// duty ratio
}

int sum3(int k) {  // Sum of before and after and own value
	byte *waveBuff = data[sample + 0];
	int m = waveBuff[k - 1] + waveBuff[k] + waveBuff[k + 1];
	return m;
}

float ethref() {
	float href = 0.625;	 // micro second
	if (rate == RATE_MAX + 2)
		href *= 2.0;
	else if (rate == RATE_MAX + 3)
		href *= 5.0;
	else if (rate == RATE_MAX + 4)
		href *= 10.0;
	else if (rate == RATE_MAX + 5)
		href *= 20.0;
	else if (rate == RATE_MAX + 6)
		href *= 50.0;
	else if (rate == RATE_MAX + 7)
		href *= 100.0;
	return href;
}

#define PWMPin 10

byte duty = 128;  // duty ratio
byte p_range = 0;
unsigned int count;
const int range_min[5] PROGMEM = {1, 8192, 8192, 16384, 16384};
const int range_div[5] PROGMEM = {1, 8, 64, 256, 1024};

void pulse_init() {
	int divide;
	p_range = constrain(p_range, 0, 4);
	divide = pgm_read_word(&range_div[p_range]);
	//  count = (unsigned int)(16000000.0 / 1000.0 / divide - 1);

	// TCCR1A: COM1A1, COM1A0, COM1B1, COM1B0, -, -, WGM11, 1GM10
	// OC1A set on compare match, clear at BOTTOM (COM1A = 0b01)
	// OC1B clear on compare match, set at BOTTOM (COM1B = 0b10)
	// OCR1A Fast PWM Mode, TOP値=OCR1A (WGM11:10 = 0b11)
	TCCR1A = _BV(COM1B1) | _BV(WGM11) |
			 _BV(WGM10);  // Fast PWM mode - compare to OCR1A

	// TCCR1B: ICNC1, ICES1, -, WGM13, WGM12, CS12, CS11, CS10
	// OCR1A Fast PWM Mode (WGM13:12 = 0b11)
	// CS12:10 001:ck/1, 010:ck/8, 011:ck/64, 100:ck/256, 101:ck/1024
	//  TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // 001:ck/1 for example
	//  TCCR1B = 0b00011001;  // ck/1
	//  TCCR1B = 0b00011010;  // ck/8
	//  TCCR1B = 0b00011011;  // ck/64
	//  TCCR1B = 0b00011100;  // ck/256
	//  TCCR1B = 0b00011101;  // ck/1024
	setCounter(divide);	 // set TCCR1B
	TCNT1 = 0x0000;		 // initialize TCNT1
	OCR1A = count;		 // set pulse period
	OCR1B = (unsigned int)(((long)count * duty) >> 8);
	pinMode(PWMPin, OUTPUT);
}

void update_frq(char diff) {
	int divide, fast;
	long newCount;

	if (abs(diff) > 3) {
		fast = 512;
	} else if (abs(diff) > 2) {
		fast = 128;
	} else if (abs(diff) > 1) {
		fast = 25;
	} else {
		fast = 1;
	}
	newCount = (long)count + fast * diff;

	if (newCount < pgm_read_word(&range_min[p_range])) {
		if (p_range < 1) {
			newCount = 1;
		} else {
			--p_range;
			newCount = 65535;
		}
	} else if (newCount > 65535) {
		if (p_range < 4) {
			++p_range;
			newCount = pgm_read_word(&range_min[p_range]);
		} else {
			newCount = 65535;
		}
	}
	divide = pgm_read_word(&range_div[p_range]);
	setCounter(divide);
	count = newCount;
	// set TOP value
	OCR1A = count;
	// set Duty ratio
	OCR1B = (unsigned int)(((long)count * duty) >> 8);
}

void disp_pulse_frq(void) {
	float pulse_frq;  // 0.238Hz <= pulse_frq <= 8MHz
	int divide = pgm_read_word(&range_div[p_range]);
	pulse_frq = 16000000.0 / (((long)count + 1) * divide);
	display.setTextColor(WHITE, BLACK);
	display.setCursor(72, 56);
	if (pulse_frq < 10.0) {
		display.print(pulse_frq, 5);
	} else if (pulse_frq < 100.0) {
		display.print(pulse_frq, 4);
	} else if (pulse_frq < 1000.0) {
		display.print(pulse_frq, 3);
	} else if (pulse_frq < 10000.0) {
		display.print(pulse_frq, 2);
	} else if (pulse_frq < 100000.0) {
		display.print(pulse_frq, 1);
	} else {
		display.print(pulse_frq, 0);
	}
	display.print(F("Hz"));
	display.setCursor(72, 48);
	//  display.print(duty*100.0/256.0, 1); display.print('%');
	display.print(duty * 0.390625, 1);
	display.print('%');
}

void setCounter(int divide) {
	if (divide == 1) {
		TCCR1B = 0b00011001;  // ck/1 > 244.1Hz
	} else if (divide == 8) {
		TCCR1B = 0b00011010;  // ck/8 > 30.5Hz
	} else if (divide == 64) {
		TCCR1B = 0b00011011;  // ck/64 > 3.81Hz
	} else if (divide == 256) {
		TCCR1B = 0b00011100;  // ck/256 > 0.954Hz
	} else if (divide == 1024) {
		TCCR1B = 0b00011101;  // ck/1024 > 0.238Hz
	} else {
		TCCR1B = 0b00011000;  // no clock
	}
}

void pulse_start() {
	setCounter(
		pgm_read_word(&range_div[p_range]));  // start clock of pulse generator
	TCCR1A = _BV(COM1B1) | _BV(WGM11) |
			 _BV(WGM10);  // Fast PWM mode - compare to OCR1A
	pinMode(PWMPin, OUTPUT);
}

void pulse_close() {
	setCounter(0);	// stop clock of pulse generator
	TCCR1A = 0x00;	// disconnect PWMPin, Mode 0 idle
	pinMode(PWMPin, INPUT_PULLUP);
}

void trigger_level(byte tglv) {
	pinMode(3, OUTPUT);

	// TCCR2A: COM2A1, COM2A0, COM2B1, COM2B0, -, -, WGM21, WGM20
	// OC2A No connection, normal port            (COM2A = 0b00)
	// OC2B clear on compare match, set at BOTTOM (COM2B = 0b10)
	// OCR2A Fast PWM Mode, TOP=OCR2A (WGM21:20 = 0b11)
	TCCR2A = _BV(COM2B1) | _BV(WGM21) |
			 _BV(WGM20);  // Fast PWM mode - compare to OCR2A
						  // TCCR2B: FOC2A, FOC2B, -, -, WGM22, CS22, CS21, CS20
						  // OCR2A Fast PWM Mode (WGM22 = 0b0)
	// CS22:20 001:ck/1, 010:ck/8, 011:ck/64, 100:ck/256, 101:ck/1024
	//  TCNT2 = 0;            // initialize TCNT2
	TCCR2B = 0b00000001;  // ck/1, TOP=255
	// Duty ratio
	OCR2B = tglv;
}

void setup() {
	pinMode(2, INPUT_PULLUP);  // CH1 DC/AC
	//  pinMode(3, OUTPUT);                   // Trigger level PWM out
	pinMode(4, INPUT_PULLUP);  // CH2 DC/AC
	//  pinMode(5, INPUT);                    // Frequency Counter in
	//  pinMode(6, INPUT);                    // Trigger level AC input
	pinMode(7, INPUT_PULLUP);		  // up
	pinMode(8, INPUT_PULLUP);		  // down
	pinMode(9, INPUT_PULLUP);		  // right
	pinMode(10, OUTPUT);			  // PWM out
	pinMode(11, OUTPUT);			  // DDS out
	pinMode(12, INPUT_PULLUP);		  // left
	DIDR0 = _BV(ADC1D) | _BV(ADC0D);  // disable digital input buffer of A0-A1
#ifdef DISPLAY_IS_SSD1306
	display.begin(SSD1306_SWITCHCAPVCC,
				  0x3C);  // select 3C or 3D (set your OLED I2C address)
#else
	display.begin(SH1106_SWITCHCAPVCC, 0x3C);  // initialise the library
#endif

	//  Serial.begin(115200);
	loadEEPROM();  // read last settings from EEPROM
				   //  set_default();
	menu = item >> 3;
	display.clearDisplay();
	//  DrawGrid();
	//  DrawText();
	//  display.display();
	(void)analogRead(ad_ch0);	   // read and neglect to setup ADC
	if (pulse_mode) pulse_init();  // calibration pulse output
	if (dds_mode) dds_setup();
}

byte lastsw = 255;
unsigned long vtime;

void CheckSW() {
	static unsigned long Millis = 0;
	unsigned long ms;
	byte sw;

	ms = millis();
	if ((ms - Millis) < 200) return;
	Millis = ms;

	/* SW10 Menu
	 * SW9  CH1 range down
	 * SW8  CH2 range down
	 * SW7  TIME/DIV slow
	 * SW6  TRIG_MODE down
	 * SW5  Send
	 * SW4  TRIG_MODE up
	 * SW3  TIME/DIV fast
	 * SW2  CH2 range up
	 * SW1  CH1 range up
	 * SW0  Start/Hold
	 */
	if (digitalRead(9) == LOW && digitalRead(12) == LOW) {
		sw = 11;  // both button press
	} else if (digitalRead(7) == LOW && digitalRead(8) == LOW) {
		sw = 12;  // both button press
	} else if (digitalRead(8) == LOW) {
		sw = 10;  // down
	} else if (digitalRead(9) == LOW) {
		sw = 3;	 // right
	} else if (digitalRead(12) == LOW) {
		sw = 7;	 // left
	} else if (digitalRead(7) == LOW) {
		sw = 0;	 // up
	} else {
		lastsw = 255;
		return;
	}
	if (sw != lastsw) vtime = ms;
	saveTimer = 5000;  // set EEPROM save timer to 5 secnd
	if (sw == 12) {
		full_screen = !full_screen;
		display.fillRect(DISPLNG + 1, 0, 27, 64,
						 BLACK);  // clear text area that will be drawn below
	} else {
		switch (menu) {
			case 0:
				menu0_sw(sw);
				break;
			case 1:
				menu1_sw(sw);
				break;
			case 2:
				menu2_sw(sw);
				break;
			case 3:
				menu3_sw(sw);
				break;
			default:
				break;
		}
		DrawText();
		display.display();
	}
	lastsw = sw;
}

void updown_ch0range(byte sw) {
	if (sw == 3) {	// CH0 RANGE +
		if (range0 > 0) range0--;
	} else if (sw == 7) {  // CH0 RANGE -
		if (range0 < RANGE_MAX) range0++;
	}
}

void updown_ch1range(byte sw) {
	if (sw == 3) {	// CH1 RANGE +
		if (range1 > 0) range1--;
	} else if (sw == 7) {  // CH1 RANGE -
		if (range1 < RANGE_MAX) range1++;
	}
}

void updown_rate(byte sw) {
	if (sw == 3) {	// RATE FAST
		if (rate > 0 && rate != (RATE_MAX + 1))
			rate--;
		else if (rate == 0)
			rate = RATE_NUM - 1;
	} else if (sw == 7) {  // RATE SLOW
		if (rate > RATE_NUM - 2)
			rate = 0;
		else if (rate != RATE_MAX)
			rate++;
	}
}

void menu0_sw(byte sw) {
	switch (item) {
		case 0:	 // CH0 voltage range
			updown_ch0range(sw);
			break;
		case 1:	 // CH1 voltage range
			updown_ch1range(sw);
			break;
		case 2:	 // rate
			updown_rate(sw);
			break;
		case 3:	 // sampling mode
			break;
		case 4:				// trigger mode
			if (sw == 3) {	// TRIG MODE +
				if (trig_mode < TRIG_SCAN)
					trig_mode++;
				else
					trig_mode = 0;
			} else if (sw == 7) {  // TRIG MODE -
				if (trig_mode > 0)
					trig_mode--;
				else
					trig_mode = TRIG_SCAN;
			}
			//    if (trig_mode != TRIG_ONE)
			//        Start = true;
			break;
		case 5:				// trigger source and polarity
			if (sw == 3) {	// trigger + edge
				if (trig_edge == TRIG_E_UP)
					trig_edge = TRIG_E_DN;
				else
					trig_edge = TRIG_E_UP;
			} else if (sw == 7) {  // trigger - channel
				if (trig_ch == 0)
					trig_ch = 1;
				else
					trig_ch = 0;
			}
			break;
		case 6:				// trigger level
			if (sw == 3) {	// trigger level +
				if (trig_lv < 60) trig_lv++;
			} else if (sw == 7) {  // trigger level -
				if (trig_lv > 0) trig_lv--;
			}
			break;
		case 7:	 // run / hold
			if (sw == 3 || sw == 7) {
				Start = !Start;
			}
			break;
	}
	menu_updown(sw);
}

void menu1_sw(byte sw) {
	switch (item - 8) {
		case 1:				// CH0 mode
			if (sw == 3) {	// CH0 + ON/INV
				if (ch0_mode == MODE_ON)
					ch0_mode = MODE_INV;
				else
					ch0_mode = MODE_ON;
			} else if (sw == 7) {  // CH0 - ON/OFF
				if (ch0_mode == MODE_OFF)
					ch0_mode = MODE_ON;
				else
					ch0_mode = MODE_OFF;
			}
			break;
		case 2:	 // CH0 voltage range
			updown_ch0range(sw);
			break;
		case 3:				// CH0 offset
			if (sw == 3) {	// offset +
				if (ch0_off < 1023) ch0_off += 1024 / VREF[range0];
			} else if (sw == 7) {  // offset -
				if (ch0_off > -1023) ch0_off -= 1024 / VREF[range0];
			} else if (sw == 11) {				  // offset reset
				if (digitalRead(CH0DCSW) == LOW)  // DC/AC input
					ch0_off = pgm_read_dword(&ac_offset[range0]);
				else
					ch0_off = 0;
			}
			break;
		case 5:				// CH1 mode
			if (sw == 3) {	// CH1 + ON/INV
				if (ch1_mode == MODE_ON)
					ch1_mode = MODE_INV;
				else
					ch1_mode = MODE_ON;
			} else if (sw == 7) {  // CH1 - ON/OFF
				if (ch1_mode == MODE_OFF)
					ch1_mode = MODE_ON;
				else
					ch1_mode = MODE_OFF;
			}
			break;
		case 6:	 // CH1 voltage range
			updown_ch1range(sw);
			break;
		case 7:				// CH1 offset
			if (sw == 3) {	// offset +
				if (ch1_off < 1023) ch1_off += 1024 / VREF[range1];
			} else if (sw == 7) {  // offset -
				if (ch1_off > -1023) ch1_off -= 1024 / VREF[range1];
			} else if (sw == 11) {				  // offset reset
				if (digitalRead(CH1DCSW) == LOW)  // DC/AC input
					ch1_off = pgm_read_dword(&ac_offset[range1]);
				else
					ch1_off = 0;
			}
			break;
	}
	menu_updown(sw);
}

void menu2_sw(byte sw) {
	char diff;
	switch (item - 16) {
		case 0:	 // CH0 voltage range
			updown_ch0range(sw);
			break;
		case 1:	 // rate
			updown_rate(sw);
			break;
		case 2:				// FFT mode
			if (sw == 3) {	// ON
				fft_mode = true;
			} else if (sw == 7) {  // OFF
				fft_mode = false;
			}
			break;
		case 3:				// Frequency and Duty display
			if (sw == 3) {	// ON
				info_mode |= 1;
			} else if (sw == 7) {  // OFF
				info_mode &= ~1;
			}
			break;
		case 4:				// Voltage display
			if (sw == 3) {	// ON
				info_mode |= 2;
			} else if (sw == 7) {  // OFF
				info_mode &= ~2;
			}
			break;
		case 5:				// PWM
			if (sw == 3) {	// +
				update_frq(0);
				pulse_start();
				pulse_mode = true;
			} else if (sw == 7) {  // -
				pulse_close();
				pulse_mode = false;
			}
			break;
		case 6:	 // PWM Duty ratio
			diff = 1;
			if (sw == lastsw) {
				if (millis() - vtime > 5000) diff = 8;
			}
			if (sw == 3) {	// +
				if (pulse_mode) {
					if ((256 - duty) > diff) duty += diff;
				} else {
					pulse_start();
				}
				update_frq(0);
				pulse_mode = true;
			} else if (sw == 7) {  // -
				if (pulse_mode) {
					if (duty > diff) duty -= diff;
				} else {
					pulse_start();
				}
				update_frq(0);
				pulse_mode = true;
			}
			break;
		case 7:	 // PWM Frequency
			diff = sw_accel(sw);
			if (sw == 3) {	// +
				if (pulse_mode)
					update_frq(-diff);
				else {
					update_frq(0);
					pulse_start();
				}
				pulse_mode = true;
			} else if (sw == 7) {  // -
				if (pulse_mode)
					update_frq(diff);
				else {
					update_frq(0);
					pulse_start();
				}
				pulse_mode = true;
			}
			break;
	}
	menu_updown(sw);
}

void menu3_sw(byte sw) {
	char diff;
	switch (item - 24) {
		case 0:	 // CH0 voltage range
			updown_ch0range(sw);
			break;
		case 1:	 // rate
			updown_rate(sw);
			break;
		case 2:				// DDS
			if (sw == 3) {	// +
				fcount_close();
				dds_setup();
				dds_mode = true;
			} else if (sw == 7) {  // -
				dds_close();
				dds_mode = false;
			}
			break;
		case 3:				// WAVE
			if (sw == 3) {	// +
				rotate_wave(true);
			} else if (sw == 7) {  // -
				rotate_wave(false);
			}
			break;
		case 4:	 // FREQ
			diff = sw_accel(sw);
			if (sw == 3) {	// +
				update_ifrq(diff);
			} else if (sw == 7) {  // -
				update_ifrq(-diff);
			}
			break;
		case 5:									// Frequency Counter
			if (sw == 3 && rate <= RATE_MAX) {	// on
				dds_close();
				dds_mode = false;
				pulse_close();
				pulse_mode = false;
				fcount_mode = true;
				FreqCount.begin(1000);
			} else if (sw == 7) {  // off
				fcount_close();
			}
			break;
	}
	menu_updown(sw);
}

void menu_updown(byte sw) {
	if (sw == 10) {	 // MENU down SW
		increment_item();
	} else if (sw == 0) {  // Menu up SW
		decrement_item();
	}
}

byte increment_item() {
	++item;
	if (item > ITEM_MAX) item = 0;
	if (menu == 0 && item == 3) item = 4;
	if (item < 16 || item > 18) fft_mode = false;  // exit FFT mode
	menu = item >> 3;
}

byte decrement_item() {
	if (item > 0)
		--item;
	else
		item = ITEM_MAX;
	if (menu == 0 && item == 3) item = 2;
	if (item < 16 || item > 18) fft_mode = false;  // exit FFT mode
	menu = item >> 3;
}

byte sw_accel(byte sw) {
	char diff = 1;
	if (sw == lastsw) {
		unsigned long curtime = millis();
		if (curtime - vtime > 6000)
			diff = 4;
		else if (curtime - vtime > 4000)
			diff = 3;
		else if (curtime - vtime > 2000)
			diff = 2;
	}
	return (diff);
}

void DrawGrid() {
	int disp_leng;
	if (full_screen)
		disp_leng = SAMPLES;
	else
		disp_leng = DISPLNG;
	for (int x = 0; x <= disp_leng; x += 2) {  // Horizontal Line
		for (int y = 0; y <= 60; y += 10) {
			display.drawPixel(x, y, WHITE);
			CheckSW();
		}
	}
	for (int x = 0; x <= disp_leng; x += 10) {	// Vertical Line
		for (int y = 0; y <= 60; y += 2) {
			display.drawPixel(x, y, WHITE);
			CheckSW();
		}
	}
}

void DrawText() {
	display.fillRect(DISPLNG + 1, 0, 27, 64,
					 BLACK);  // clear text area that will be drawn below

	switch (menu) {
		case 0:
			set_line_color(0);
			if (ch0_mode != MODE_OFF) {
				display_range(range0);
			} else {
				display.print(F("CH2"));
				display_ac(CH1DCSW);
			}
			set_line_color(1);
			if (ch1_mode != MODE_OFF && rate > 4 && rate < (RATE_MAX + 1)) {
				display_range(range1);
			} else {
				display.print(F("CH1"));
				display_ac(CH0DCSW);
			}
			set_line_color(2);
			display_rate();
			set_line_color(3);
			if (rate <= RATE_MAX)
				display.print(F("real"));
			else
				display.print(F("eqiv"));
			set_line_color(4);
			display_trig_mode();
			set_line_color(5);
			display.print(trig_ch == 0 ? F("TG1") : F("TG2"));
			display.print(trig_edge == TRIG_E_UP ? char(0x18) : char(0x19));
			set_line_color(6);
			display.print(F("Tlev"));
			set_line_color(7);
			display.print(Start ? F("RUN") : F("HOLD"));
			break;
		case 1:
			set_line_color(0);
			display.print(F("CH1"));
			display_ac(CH0DCSW);
			set_line_color(1);
			display_mode(ch0_mode);
			set_line_color(2);
			display_range(range0);
			set_line_color(3);
			display.print(F("OFS1"));
			set_line_color(4);
			display.print(F("CH2"));
			display_ac(CH1DCSW);
			set_line_color(5);
			display_mode(ch1_mode);
			set_line_color(6);
			display_range(range1);
			set_line_color(7);
			display.print(F("OFS2"));
			break;
		case 2:
			set_line_color(0);
			display_range(range0);
			set_line_color(1);
			display_rate();
			set_line_color(2);
			if (!fft_mode) {
				display.print(F("FFT"));
				set_line_color(3);
				display.print(F("FREQ"));
				set_line_color(4);
				display.print(F("VOLT"));
				set_line_color(5);
				display.print(F("PWM"));
				set_line_color(6);
				display.print(F("DUTY"));
				set_line_color(7);
				display.print(F("FREQ"));
				if (pulse_mode && (item > 20 && item < 24)) disp_pulse_frq();
			}
			break;
		case 3:
			set_line_color(0);
			display_range(range0);
			set_line_color(1);
			display_rate();
			set_line_color(2);
			display.print(F("DDS"));
			set_line_color(3);
			disp_dds_wave();
			set_line_color(4);
			display.print(F("FREQ"));
			if (dds_mode) disp_dds_freq();
			set_line_color(5);
			display.print(F("FCNT"));
			fcount_disp();
			break;
	}
	if (info_mode && Start) {
		dataAnalize();
		if (info_mode & 1) measure_frequency();
		if (info_mode & 2) measure_voltage();
	}
	if (!full_screen && !fft_mode)
		display.drawFastHLine(DISPLNG, 60 - trig_lv, 3,
							  WHITE);  // draw trig_lv tic
}

unsigned long fcount = 0;
const double freq_ratio = 20000.0 / 19987.0;

void fcount_disp() {
	if (!fcount_mode) return;
	if (FreqCount.available()) {
		fcount = FreqCount.read();
		fcount = fcount * freq_ratio;  // compensate the ceramic osc
	}
	display.setTextColor(WHITE, BLACK);
	display.setCursor(74, 48);
	display.print(fcount);
	display.print(F("Hz"));
}

void fcount_close() {
	if (!fcount_mode) return;
	fcount_mode = false;
	FreqCount.end();
}

void display_range(byte rng) {
	char str[5];
	display.print(strcpy_P(str, (char *)pgm_read_word(&(Ranges[rng]))));
}

void display_rate(void) {
	char str[5];
	display.print(strcpy_P(str, (char *)pgm_read_word(&(Rates[rate]))));
}

void display_mode(byte chmode) {
	char str[5];
	display.print(strcpy_P(str, (char *)pgm_read_word(&(Modes[chmode]))));
}

void display_trig_mode(void) {
	char str[5];
	display.print(
		strcpy_P(str, (char *)pgm_read_word(&(TRIG_Modes[trig_mode]))));
}

void display_ac(byte pin) {
	if (digitalRead(pin) == LOW) display.print('~');
}

void set_line_color(byte line) {
	if ((item & 0x7) == line)
		display.setTextColor(BLACK, WHITE);	 // highlight
	else
		display.setTextColor(WHITE, BLACK);	 // normal
	display.setCursor(DISPLNG + 3,
					  8 * line);  // locate curser for printing text
}

void DrawGrid(int x) {
	if ((x % 2) == 0)
		for (int y = 0; y <= 60; y += 10) display.drawPixel(x, y, WHITE);
	if ((x % 10) == 0)
		for (int y = 0; y <= 60; y += 2) display.drawPixel(x, y, WHITE);
}

void ClearAndDrawGraph() {
	int disp_leng;
	if (full_screen)
		disp_leng = SAMPLES - 1;
	else
		disp_leng = DISPLNG - 1;
	bool ch1_active = ch1_mode != MODE_OFF && rate > 4 && rate <= RATE_MAX;
#if 0
  for (int x=0; x<DISPLNG; x++) {
    display.drawPixel(x, 60-data[sample+0][x], WHITE);
    display.drawPixel(x, 60-data[sample+1][x], WHITE);
  }
#else
	for (int x = 0; x < disp_leng; x++) {
		if (ch0_mode != MODE_OFF)
			display.drawLine(x, 60 - data[sample + 0][x], x + 1,
							 60 - data[sample + 0][x + 1], WHITE);
		if (ch1_active)
			display.drawLine(x, 60 - data[sample + 1][x], x + 1,
							 60 - data[sample + 1][x + 1], WHITE);
		CheckSW();
	}
#endif
}

void ClearAndDrawDot(int i) {
#if 0
  for (int x=0; x<DISPLNG; x++) {
    display.drawPixel(i, 60-odat01, BLACK);
    display.drawPixel(i, 60-odat11, BLACK);
    display.drawPixel(i, 60-data[sample+0][i], WHITE);
    display.drawPixel(i, 60-data[sample+1][i], WHITE);
  }
#else
	if (i < 1) return;
	if (ch0_mode != MODE_OFF) {
		display.drawLine(i - 1, 60 - odat00, i, 60 - odat01, BLACK);
		display.drawLine(i - 1, 60 - data[0][i - 1], i, 60 - data[0][i], WHITE);
	}
	if (ch1_mode != MODE_OFF) {
		display.drawLine(i - 1, 60 - odat10, i, 60 - odat11, BLACK);
		display.drawLine(i - 1, 60 - data[1][i - 1], i, 60 - data[1][i], WHITE);
	}
#endif
	DrawGrid(i);
}

void scaleDataArray() {
	byte *pdata;
	int *idata;
	long a;

	idata = (int *)data[0];
	pdata = data[0];
	for (int i = 0; i < SAMPLES; i++) {
		a = ((*idata++ + ch0_off) * VREF[range0] + 512) >> 10;
		if (a > 60)
			a = 60;
		else if (a < 0)
			a = 0;
		if (ch0_mode == MODE_INV) a = 60 - a;
		*pdata++ = (byte)a;
	}
}

byte adRead(byte ch, byte mode, int off) {
	long a = analogRead(ch);
	a = ((a + off) * VREF[ch == ad_ch0 ? range0 : range1] + 512) >> 10;
	if (a > 60)
		a = 60;
	else if (a < 0)
		a = 0;
	if (mode == MODE_INV) return 60 - a;
	return a;
}

int advalue(int value, long vref, byte mode, int offs) {
	if (mode == MODE_INV) value = 60 - value;
	return (((long)value << 10) - 512L) / vref - offs;
}

void loop() {
	int oad, ad;
	unsigned long auto_time;
	int trigger_ad;

	timeExec = 100;
	if (rate <= RATE_MAX) {
		if (trig_ch == ad_ch0) {
			trigger_ad = advalue(trig_lv, VREF[range0], ch0_mode, ch0_off);
		} else {
			trigger_ad = advalue(trig_lv, VREF[range1], ch1_mode, ch1_off);
		}
		ADCSRA =
			(ADCSRA & 0x07) | _BV(ADEN) | _BV(ADIF);  // Auto Trigger disable
		ADCSRB &= 0xf8;	 // Auto Trigger source free run
		auto_time = pow(10, rate / 3);
		if (rate < 7) auto_time *= 10;
		if (trig_mode != TRIG_SCAN) {
			unsigned long st = millis();
			oad = analogRead(trig_ch);
			for (;;) {
				ad = analogRead(trig_ch);

				if (trig_edge == TRIG_E_UP) {
					if (ad >= trigger_ad && trigger_ad > oad) break;
				} else {
					if (ad <= trigger_ad && trigger_ad < oad) break;
				}
				oad = ad;

				if (rate > 9) CheckSW();  // no need for fast sampling
				if (trig_mode == TRIG_SCAN) break;
				if (trig_mode == TRIG_AUTO && (millis() - st) > auto_time)
					break;
			}
		}
	}

	// sample and draw depending on the sampling rate
	if (rate <= 14 && Start) {
		if (rate == 0) {  // full speed, channel 0 only 3.25us sampling
			sample_33us();
		} else if (rate == 1) {	 // channel 0 only 5.1us sampling
			sample_51us();
		} else if (rate == 2) {	 // channel 0 only 10us sampling
			sample_100us();
		} else if (rate == 3) {	 // channel 0 only 20us sampling
			sample_200us(20);
		} else if (rate == 4) {	 // channel 0 only 49us sampling
			sample_200us(50);
		} else if (rate == 5) {	 // full speed, dual channel 58us sampling
			ADCSRA = (ADCSRA & 0xf8) |
					 0x04;	// dividing ratio = 16(0x1=2, 0x2=4, 0x3=8, 0x4=16,
							// 0x5=32, 0x6=64, 0x7=128)
			for (int i = 0; i < SAMPLES; i++) {
				data[sample + 0][i] = adRead(ad_ch0, ch0_mode, ch0_off);
				data[sample + 1][i] = adRead(ad_ch1, ch1_mode, ch1_off);
			}
		} else if (rate >= 6 &&
				   rate <= 8) {	 // dual channel 80us, 100us, 200us sampling
			sample_dual_us(pgm_read_dword(&HREF[rate]) / 10);
		} else {  // dual channel .5ms, 1ms, 2ms, 5ms, 10ms, 20ms sampling
			sample_dual_ms(pgm_read_dword(&HREF[rate]) / 10);
		}
		//    display.clearDisplay();
		if (fft_mode) {
			DrawText();
			plotFFT();
		} else {
			ClearAndDrawGraph();
			DrawGrid();
			if (!full_screen) DrawText();
		}
		CheckSW();
		display.display();
		display.clearDisplay();
	} else if (rate <= RATE_MAX && Start) {	 // 50ms - 1000ms sampling
		timeExec = 5000;
		ADCSRA = ADCSRA | 0x07;	 // dividing ratio = arduino default
		static const unsigned long r_[] PROGMEM = {50000, 100000, 200000,
												   500000, 1000000};
		unsigned long r;
		int disp_leng;
		if (full_screen)
			disp_leng = SAMPLES;
		else
			disp_leng = DISPLNG;
		//    unsigned long st0 = millis();
		unsigned long st = micros();
		for (int i = 0; i < disp_leng; i++) {
			r = pgm_read_dword(r_ + rate - 15);	 // rate may be changed in loop
			while ((st - micros()) < r) {
				CheckSW();
				if (rate < 15) break;
			}
			if (rate < 15) {  // sampling rate has been changed
				display.clearDisplay();
				break;
			}
			st += r;
			if (st - micros() > r)
				st = micros();	// sampling rate has been changed to shorter
								// interval
			if (!Start) {
				i--;
				continue;
			}
			odat00 = odat01;	  // save next previous data ch0
			odat10 = odat11;	  // save next previous data ch1
			odat01 = data[0][i];  // save previous data ch0
			odat11 = data[1][i];  // save previous data ch1
			data[sample + 0][i] = adRead(ad_ch0, ch0_mode, ch0_off);
			data[sample + 1][i] = adRead(ad_ch1, ch1_mode, ch1_off);
			ClearAndDrawDot(i);
			display.display();	// 42ms
		}
		// Serial.println(millis()-st0);
		DrawGrid();
		if (!full_screen) DrawText();
	} else if (Start) {	 // Equivalent Time sampling
		extern byte oscspeed;
		oscspeed = rate - RATE_MAX - 1;	 // 20...26 -> 0...6
		trigger_level(
			constrain(advalue(trig_lv, VREF[range0], ch0_mode, ch0_off) / 4, 0,
					  255));  // PWM triger level for ET
		modeequiv();
		display.clearDisplay();
		if (fft_mode) {
			DrawText();
			plotFFT();
		} else {  // channel 0 only
			ClearAndDrawGraph();
			DrawGrid();
			if (!full_screen) DrawText();
		}
		CheckSW();
		display.display();
	} else {
		CheckSW();
	}
	if (trig_mode == TRIG_ONE) Start = false;
	saveEEPROM();  // save settings to EEPROM if necessary
}

// Modified by Siliconvalley4066. July 23, 2021
//
// Kyutech Arduino Scope Prototype  v0.73                     Apr 10, 2019
//    (C) 2012-2019 M.Kurata Kyushu Institute of Technology
//    for Arduinos with a 5V-16MHz ATmega328.
//
//    Pin usage
//
//    A0  oscilloscope probe ch1
//    A1  oscilloscope probe ch2
//    A2
//    A3
//    A4  I2C SDA
//    A5  I2C SCL
//    A6  reserved
//    A7  reserved
//
//    D0  uart-rx
//    D1  uart-tx
//    D2  reserve
//    D3  PWM output for trigger level
//    D4  Up button
//    D5  reserve
//    D6  trigger level input
//    D7  reserve
//    D8  Down button
//    D9  Right button
//    D10 Pulse generator output
//    D11 PWM DDS output
//    D12 Left button
//    D13 LED output

byte oscspeed = 0;	 // 0..6:equiv
byte oscinput = 0;	 // input signal selection  0:CH1 1:CH2 2:DUAL
word osctdly = 800;	 // time of delayed trigger  100..30000 usec
byte at;
// static const struct eqdic_s {
//   byte   tkn;
//   byte   tdif;
// } eqdic[] = {
//   {128,  1},   // 16Msample/s  , 0.625us/div
//   {128,  2},   // 8Msample/s   , 1.25us/div
//   {128,  5},   // 3.2Msample/s , 3.125us/div
//   { 64, 10},   // 1.6Msample/s , 6.25us/div
//   { 32, 20},   // 800ksample/s , 12.5us/div
//   { 16, 50},   // 320ksample/s , 31.25us/div
//   {  8,100},   // 160ksample/s , 62.5us/div
// };
const byte tkn[] PROGMEM = {128, 128, 128, 64, 32, 16, 8};
const byte tdif[] PROGMEM = {1, 2, 5, 10, 20, 50, 100};

void modeequiv() {
	byte realnum, i, dp, admux;
	byte tokadif, toka, tokanum;
	byte ch, chnum, adch, adchT;
	word ui1, waituntil, sinterval;

	int *buf0 = (int *)data[0];
	tokanum = pgm_read_byte(tkn + oscspeed);
	waituntil = 64000;
	realnum = SAMPLES / tokanum;
	tokadif = pgm_read_byte(tdif + oscspeed);
	sinterval = tokanum * tokadif;	// 20us typical

	// ADMUX reg values
	admux = ADMUX & 0xf8;
	switch (oscinput) {
		default:
		case 0x00:
			adch = admux + 0;
			chnum = 1;
			break;	// CH1
		case 0x01:
			adch = admux + 1;
			chnum = 1;
			break;	// CH2
		case 0x02:
			adch = admux + 0;
			chnum = 2;	// CH1 Ch2 Dual
			break;
	}
	adchT = admux + 0;	// select CH1 for trigger

	sinterval--;
	at = 0;
	for (toka = 0; toka < tokanum; toka++) {
		dp = toka;
		for (ch = 0; ch < chnum; ch++) {  // for all ch (1 or 2)
			// reset and initialize timer1
			TCCR1B = 0x00;	// stop, set normal mode
			TCCR1A = 0x00;
			TIMSK1 = 0x00;	// no irq
			ICR1 = 0x0000;
			TCNT1 = 0x0000;
			TIFR1 = 0x27;  // clear flags;

			// analog comparator setting
			// The BG is the positive input.
			// The negative input is A0 pin.
			ACSR = 0x94;	// analog comparator off
			DIDR1 = 0x01;	// disable the digital input func of D6.
			ADMUX = adchT;	// select the negative input
			ADCSRA = 0x04;	// divide by 16
			ADCSRB = 0x40;	// AC multiplexer enable, ADC auto trigger source
							// free run

			// start timer1 with pre=1/1 (16MHz)
			// input capture noise canceler ON
			TCCR1B = (trig_edge == TRIG_E_DN) ? 0xc1 : 0x81;  // edge selection
			ACSR = 0x14;   // capture-on, aco to caputure timer1
			TIFR1 = 0x27;  // clear flags again

			ui1 = (tokadif * toka) + (osctdly << 4);  // delay time

			// falling edge detection(rising edge for ICES1)
			// doesn't stabilize without a 20usec wait below.
			while (TCNT1 < 320)
				;
			TIFR1 = 0x27;
			// wait until a trigger event happens
			while (true) {
				if (TIFR1 & 0x20) {
					// trigger event has happened.
					ui1 += ICR1;
					at = 0;	 // a trigger event has happened.
					break;
				}
				if (TCNT1 > waituntil) {
					ui1 += TCNT1;
					at = 1;	 // trigger failed.
					break;
				}
			}

			// at:0 -> trigger event has happened, 1 -> not happened
			ACSR = 0x94;	// disable analog comparator
			ADCSRB = 0x00;	// AC multiplexer disable, ADC auto trigger source
							// free run
			ADCSRA = 0x84;	// adc enable, 1MHz, adate off

			TCCR1B = 0x19;	// timer1 CTC-ICR1 mode pre1/1
			TCCR1A = 0x00;	//             CTC mode;
			ICR1 = ui1;
			TIFR1 = 0x27;  // clear flags

			ADMUX = adch;	// adc target is A0 pin to get trigger value;
			ADCSRB = 0x07;	// timer1 capture event;
			ADCSRA = 0xf4;	// adc auto trigger, force 1st conversion

			// wait until the 1st conversion finishes.
			while ((ADCSRA & 0x10) == 0x00)
				;

			ADMUX = adch + ch;
			ADCSRA = 0xb4;	// clear flag, 1MHz, adate on

			if (toka == 0 && ch == 0) {	 // needed only for the 1st loop
				if (at) {
					for (i = 0; i < SAMPLES; i++) buf0[i] = analogRead(ad_ch0);
					scaleDataArray();
					return;	 // when trigger failed
				}
			}

			for (i = 0; i < realnum; i++) {
				while (true) {
					if (TIFR1 & 0x20) {
						ICR1 = sinterval;
						TIFR1 = 0x27;  // clear timer1 flags;
					}
					if ((ADCSRA & 0x10) != 0x00) break;
				}
				byte *pdata = (byte *)&buf0[dp];
				*pdata++ = ADCL;
				*pdata = ADCH;
				dp += tokanum;
				ADCSRA = 0xb4;	// clear flag, 1MHz, adate on
			}
		}
	}
	scaleDataArray();
}

#define textINFO 54
void measure_frequency() {
	int x1, x2;
	freqDuty();
	display.setTextColor(WHITE, BLACK);
	display.setCursor(textINFO, txtLINE0);
	if (waveFreq < 999.5)
		display.print(waveFreq);
	else if (waveFreq < 999999.5)
		display.print(waveFreq, 0);
	else {
		display.print(waveFreq / 1000.0, 0);
		display.print('k');
	}
	display.print(F("Hz"));
	if (fft_mode) return;
	display.setCursor(textINFO + 12, txtLINE1);
	display.print(waveDuty);
	display.print('%');
}

void measure_voltage() {
	int x, dave, dmax, dmin;
	if (fft_mode) return;
	if (ch0_mode == MODE_INV) {
		dave = 60 * 10 - dataAve;
		dmax = dataMin;
		dmin = dataMax;
	} else {
		dave = dataAve;
		dmax = dataMax;
		dmin = dataMin;
	}
	float vavr =
		VRF * (((dave * 102.4) - 512.0) / VREF[range0] - ch0_off) / 1023.0;
	float vmax = VRF * advalue(dmax, VREF[range0], ch0_mode, ch0_off) / 1023.0;
	float vmin = VRF * advalue(dmin, VREF[range0], ch0_mode, ch0_off) / 1023.0;
	display.setCursor(textINFO, txtLINE2);
	display.print(F("max"));
	display.print(vmax);
	if (vmax >= 0.0) display.print('V');
	display.setCursor(textINFO, txtLINE3);
	display.print(F("avr"));
	display.print(vavr);
	if (vavr >= 0.0) display.print('V');
	display.setCursor(textINFO, txtLINE4);
	display.print(F("min"));
	display.print(vmin);
	if (vmin >= 0.0) display.print('V');
}

void sample_dual_us(unsigned int r) {  // dual channel. r > 67 (0x4)
	byte *p0, *p1;
	ADCSRA = (ADCSRA & 0xf8) | 0x04;  // dividing ratio = 16(0x1=2, 0x2=4,
									  // 0x3=8, 0x4=16, 0x5=32, 0x6=64, 0x7=128)
	p0 = data[0];
	p1 = data[1];
	unsigned long st = micros();
	for (int i = 0; i < SAMPLES; i++) {
		while (micros() - st < r)
			;
		*p0++ = adRead(ad_ch0, ch0_mode, ch0_off);
		*p1++ = adRead(ad_ch1, ch1_mode, ch1_off);
		st += r;
	}
}

void sample_dual_ms(unsigned int r) {  // dual channel. r > 500 (0x7)
									   // .5ms, 1ms or 2ms sampling
	ADCSRA = ADCSRA | 0x07;			   // dividing ratio = arduino default
	unsigned long st = micros();
	for (int i = 0; i < SAMPLES; i++) {
		while (micros() - st < r)
			;
		st += r;
		data[0][i] = adRead(ad_ch0, ch0_mode, ch0_off);
		data[1][i] = adRead(ad_ch1, ch1_mode, ch1_off);
	}
}

void sample_200us(unsigned int r) {	 // analogRead() with timing, channel 0
									 // only. 200us/div 50ksps
	int *idata;
	ADCSRA = (ADCSRA & 0xf8) | 0x04;  // dividing ratio = 8(0x1=2, 0x2=4, 0x3=8,
									  // 0x4=16, 0x5=32, 0x6=64, 0x7=128)
	idata = (int *)data[0];
	unsigned long st = micros();
	for (int i = 0; i < SAMPLES; i++) {
		while (micros() - st < r)
			;
		*idata++ = analogRead(ad_ch0);
		st += r;
	}
	scaleDataArray();
}

void sample_100us() {  // register direct with timing, channel 0 only. 100us/div
					   // 100ksps
	byte *pdata;
	byte r = 10;
	ADMUX = (ADMUX & 0xf8) + ad_ch0;
	ADCSRA = (ADCSRA & 0xf8) | 0x02;  // dividing ratio = 8(0x1=2, 0x2=4, 0x3=8,
									  // 0x4=16, 0x5=32, 0x6=64, 0x7=128)
	pdata = data[0];
	unsigned long st = micros();
	for (int i = 0; i < SAMPLES; i++) {
		while (micros() - st < r)
			;
		ADCSRA |= 0x40;	 // start the conversion(1 << ADSC)
		st += r;
		while (ADCSRA & 0x40)
			;			  // ADSC is cleared when the conversion finishes
		*pdata++ = ADCL;  // must read adch low byte first
		*pdata++ = ADCH;  // read adch high byte
	}
	scaleDataArray();
}

void sample_51us() {  // full speed, channel 0 only. 51us/div 189ksps
	byte *pdata;
	ADMUX = (ADMUX & 0xf8) + ad_ch0;
	ADCSRA = (ADCSRA & 0xf8) | 0x02;  // dividing ratio = 8(0x1=2, 0x2=4, 0x3=8,
									  // 0x4=16, 0x5=32, 0x6=64, 0x7=128)
	pdata = data[0];
	//  unsigned long st0 = micros();
	unsigned long st = micros();
	for (int i = 0; i < SAMPLES; i++) {
		ADCSRA |= 0x40;	 // start the conversion(1 << ADSC)
		while (ADCSRA & 0x40)
			;			  // ADSC is cleared when the conversion finishes
		*pdata++ = ADCL;  // must read adch low byte first
		*pdata++ = ADCH;  // read adch high byte
	}
	//  Serial.println(micros()-st0);
	scaleDataArray();
}

void sample_33us() {  // full speed, channel 0 only ADC free run. 32.5us/div
					  // 308ksps
	byte *pdata;
	ADMUX = (ADMUX & 0xf8) + ad_ch0;
	ADCSRA = (ADCSRA & 0xf8) |
			 0x62;	// Auto Trigger Enable. dividing ratio = 4(0x1=2, 0x2=4,
					// 0x3=8, 0x4=16, 0x5=32, 0x6=64, 0x7=128)
	pdata = data[0];
	for (int i = 0; i < SAMPLES; i++) {
		while ((ADCSRA & 0x10) == 0)
			;			  // polling until adif==1
		ADCSRA |= 0x10;	  // clear adif
		*pdata++ = ADCL;  // must read adch low byte first
		*pdata++ = ADCH;  // read adch high byte
	}
	ADCSRA = ADCSRA & 0x9f;	 // stop ADC free run ADSC=0 ADATE=0
	scaleDataArray();
}

void plotFFT() {
	char *im, *re;
	int ylim = 56;

	re = (char *)data[0];
	im = (char *)data[1];  // use ch1 buffer for imaginary data
	for (int i = 0; i < FFT_N; i++) {
		int d = *re << 2;  // 0 <= data <= 60 so multiply 4
		d = d - 120;	   // center value should be 120
		*re++ = constrain(d, -128, 127);
		*im++ = 0;
	}
	re = (char *)data[0];
	im = (char *)data[1];	// use ch1 buffer for imaginary data
	fix_fft(re, im, 7, 0);	// full scale 2^7=128, FFT mode
	for (int i = 1; i < FFT_N / 2; i++) {
		int dat = sqrt(re[i] * re[i] + im[i] * im[i]);
		dat = constrain(dat, 0, ylim);
		display.drawFastVLine(i * 2, ylim - dat, dat, WHITE);
	}
	draw_scale();
}

void draw_scale() {
	int ylim = 56;
	float fhref, nyquist;
	display.setTextColor(WHITE);
	display.setCursor(0, ylim);
	display.print(F("0Hz"));
	if (rate > RATE_MAX) {
		fhref = ethref();
	} else {
		fhref = (float)pgm_read_dword(&HREF[rate]);
	}
	nyquist = 5.0e6 / fhref;  // Nyquist frequency
	if (nyquist > 999.0) {
		nyquist = nyquist / 1000.0;
		if (nyquist > 99.5) {
			display.setCursor(58, ylim);
			display.print(nyquist / 2, 0);
			display.print('k');
			display.setCursor(104, ylim);
			display.print(nyquist, 0);
		} else if (nyquist > 9.95) {
			display.setCursor(58, ylim);
			display.print(nyquist / 2, 0);
			display.print('k');
			display.setCursor(110, ylim);
			display.print(nyquist, 0);
		} else {
			display.setCursor(52, ylim);
			display.print(nyquist / 2, 1);
			display.print('k');
			display.setCursor(104, ylim);
			display.print(nyquist, 1);
		}
		display.print('k');
	} else {
		display.setCursor(58, ylim);
		display.print(nyquist / 2, 0);
		display.setCursor(110, ylim);
		display.print(nyquist, 0);
	}
}

#define EEPROM_START 64
void saveEEPROM() {	 // Save the setting value in EEPROM after waiting a while
					 // after the button operation.
	int p = EEPROM_START;
	if (saveTimer > 0) {				   // If the timer value is positive
		saveTimer = saveTimer - timeExec;  // Timer subtraction
		if (saveTimer <= 0) {			   // if time up
			EEPROM.write(p++, range0);	   // save current status to EEPROM
			EEPROM.write(p++, ch0_mode);
			EEPROM.write(p++, lowByte(ch0_off));  // save as Little endian
			EEPROM.write(p++, highByte(ch0_off));
			EEPROM.write(p++, range1);
			EEPROM.write(p++, ch1_mode);
			EEPROM.write(p++, lowByte(ch1_off));  // save as Little endian
			EEPROM.write(p++, highByte(ch1_off));
			EEPROM.write(p++, rate);
			EEPROM.write(p++, trig_mode);
			EEPROM.write(p++, trig_lv);
			EEPROM.write(p++, trig_edge);
			EEPROM.write(p++, trig_ch);
			EEPROM.write(p++, fft_mode);
			EEPROM.write(p++, info_mode);
			EEPROM.write(p++, item);
			EEPROM.write(p++, pulse_mode);
			EEPROM.write(p++, duty);
			EEPROM.write(p++, p_range);
			EEPROM.write(p++, lowByte(count));	// save as Little endian
			EEPROM.write(p++, highByte(count));
			EEPROM.write(p++, dds_mode);
			EEPROM.write(p++, wave_id);
			EEPROM.write(p++, ifreq & 0xff);
			EEPROM.write(p++, (ifreq >> 8) & 0xff);
			EEPROM.write(p++, (ifreq >> 16) & 0xff);
			EEPROM.write(p++, (ifreq >> 24) & 0xff);
		}
	}
}

void set_default() {
	range0 = RANGE_MIN;
	ch0_mode = MODE_ON;
	ch0_off = -200;
	range1 = RANGE_MIN;
	ch1_mode = MODE_ON;
	ch1_off = 400;
	rate = 5;
	trig_mode = TRIG_AUTO;
	trig_lv = 15;
	trig_edge = TRIG_E_UP;
	trig_ch = ad_ch0;
	fft_mode = false;
	info_mode = 1;	// display frequency and duty.  Voltage display is off
	item = 0;		// menu item
	pulse_mode = false;
	duty = 128;		// PWM 50%
	p_range = 0;	// PWM range
	count = 15999;	// PWM 1kHz
	dds_mode = false;
	wave_id = 0;	// sine wave
	ifreq = 12255;	// 122.55Hz
}

void loadEEPROM() {	 // Read setting values from EEPROM (abnormal values will be
					 // corrected to default)
	int p = EEPROM_START, error = 0;

	range0 = EEPROM.read(p++);	// range0
	if ((range0 < RANGE_MIN) || (range0 > RANGE_MAX)) ++error;
	ch0_mode = EEPROM.read(p++);  // ch0_mode
	if (ch0_mode > 2) ++error;
	*((byte *)&ch0_off) = EEPROM.read(p++);		 // ch0_off low
	*((byte *)&ch0_off + 1) = EEPROM.read(p++);	 // ch0_off high
	if ((ch0_off < -1024) || (ch0_off > 1023)) ++error;

	range1 = EEPROM.read(p++);	// range1
	if ((range1 < RANGE_MIN) || (range1 > RANGE_MAX)) ++error;
	ch1_mode = EEPROM.read(p++);  // ch1_mode
	if (ch1_mode > 2) ++error;
	*((byte *)&ch1_off) = EEPROM.read(p++);		 // ch1_off low
	*((byte *)&ch1_off + 1) = EEPROM.read(p++);	 // ch1_off high
	if ((ch1_off < -1024) || (ch1_off > 1023)) ++error;

	rate = EEPROM.read(p++);  // rate
	if ((rate < RATE_MIN) || (rate >= RATE_NUM)) ++error;
	//  if (ch0_mode == MODE_OFF && rate < 5) ++error;  // correct ch0_mode
	trig_mode = EEPROM.read(p++);  // trig_mode
	if (trig_mode > TRIG_SCAN) ++error;
	trig_lv = EEPROM.read(p++);	 // trig_lv
	if (trig_lv > 60) ++error;
	trig_edge = EEPROM.read(p++);  // trig_edge
	if (trig_edge > 1) ++error;
	trig_ch = EEPROM.read(p++);	 // trig_ch
	if (trig_ch > 7) ++error;
	fft_mode = EEPROM.read(p++);   // fft_mode
	info_mode = EEPROM.read(p++);  // info_mode
	if (info_mode > 3) ++error;
	item = EEPROM.read(p++);  // item
	if (item > ITEM_MAX) ++error;
	pulse_mode = EEPROM.read(p++);	// pulse_mode
	duty = EEPROM.read(p++);		// duty
	p_range = EEPROM.read(p++);		// p_range
	if (p_range > 4) ++error;
	*((byte *)&count) = EEPROM.read(p++);	   // count low
	*((byte *)&count + 1) = EEPROM.read(p++);  // count high
	dds_mode = EEPROM.read(p++);			   // DDS wave id
	wave_id = EEPROM.read(p++);				   // DDS wave id
	if (wave_id > 10) ++error;
	*((byte *)&ifreq) = EEPROM.read(p++);	   // count low
	*((byte *)&ifreq + 1) = EEPROM.read(p++);  // count
	*((byte *)&ifreq + 2) = EEPROM.read(p++);  // count
	*((byte *)&ifreq + 3) = EEPROM.read(p++);  // count high
	if (ifreq > 999999L) ++error;
	if (error > 0) set_default();
}
