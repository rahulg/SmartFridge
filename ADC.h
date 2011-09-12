/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul, SK Sahoo, Henry Tan
 *
 */

#ifndef __HEADER_ADC__
#define	__HEADER_ADC__

#include "Definitions.h"
#include "Delay.h"

#define ADC_ON  ADON=1;
#define ADC_OFF ADON=0;

volatile uchar _portConfig;

void adc_init(uchar portConfig) {
	TRISA = 0x00; // PORTA as output
	
	_portConfig = portConfig;
	
	// Clock selection: 32Tosc
	ADCS1 = 1; ADCS0 = 0;
	
	// Turn on ADC
	ADON = 1;
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
