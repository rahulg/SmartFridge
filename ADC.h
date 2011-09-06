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

void adc_init() {
	TRISA = 0xFF; // PORTA as input
	ADCON1 = 0x82; // Right-justified
	
	ADCS1=1;
	ADCS0=0;
	ADON=1;
}

adc_t adc_read(int channel) {
	int value;
	
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
	value = (ADRESH << 8) + ADRESL;
	
	// Wait for 2TAD
	delay_usec(4);
	
	return value;
}

#endif
