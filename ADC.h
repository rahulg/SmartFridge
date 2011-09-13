/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul, SK Sahoo, Henry Tan
 *
 */

#ifndef __HEADER_ADC__
#define	__HEADER_ADC__


// Include Headers
#include "Definitions.h"
#include "Delay.h"


// Key Definitions
#define ADC_ON ADON

#define LOWRES  0
#define HIGHRES 1

typedef unsigned int adc_t;
typedef unsigned char adc_lr_t;


// Code
volatile uchar _portConfig;

void adc_init(uchar portConfig) {
	TRISA = 0x00; // PORTA as output
	
	_portConfig = portConfig;
	
	// Clock selection: 32Tosc
	ADCS1 = HIGH; ADCS0 = LOW;
	
	// Turn on ADC
	ADON = HIGH;
}

adc_t adc_read(int channel, int highRes) {
	
	adc_t value;
	
	// Left-justify if lowres
	ADCON1 = (highRes ? 0x80 : 0x00) & _portConfig;
	
	switch (channel) {
		case 0:
			CHS2=0; CHS1=0; CHS0=0;
			break;
		case 1:
			CHS2=0; CHS1=0; CHS0=1;
			break;
		case 2:
			CHS2=0; CHS1=1; CHS0=0;
			break;
		case 3:
			CHS2=0; CHS1=1; CHS0=1;
			break;
		case 4:
			CHS2=1; CHS1=0; CHS0=0;
			break;
		case 5:
			CHS2=1; CHS1=0; CHS01;
			break;
		case 6:
			CHS2=1; CHS1=1; CHS0=0;
			break;
		case 7:
			CHS2=1; CHS1=1; CHS0=1;
			break;
		default:
			CHS2=0; CHS1=0; CHS0=0;
			break;
	}
	
	// Delay for acq time
	delay_usec(100);
	
	// Start AD conv & wait for it to end
	GO=1;
	while (GO);
	
	// Read the values in the register pair
	value = highRes ? (ADRESH << 8) + ADRESL : ADRESH;
	
	// Wait for 2TAD
	delay_usec(4);
	
	return value;
}

#endif
