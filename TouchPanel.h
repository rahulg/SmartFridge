/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __HEADER_TOUCHPANEL__
#define	__HEADER_TOUCHPANEL__

#include "Definitions.h"
#include "Ports0.h"
#include "Delay.h"

#define R1MIN 0x0
#define R1MAX 0x0
#define R2MIN 0x0
#define R2MAX 0x0
#define R3MIN 0x0
#define R3MAX 0x0
#define R4MIN 0x0
#define R4MAX 0x0

#define C1MIN 0x0
#define C1MAX 0x0
#define C2MIN 0x0
#define C2MAX 0x0
#define C3MIN 0x0
#define C3MAX 0x0

void tch_init() {
	// config ADCON1
}

adc_t tch_read_x() {
	adc_t x_pos;
	
	// Set I/O mode and pull pins high/low
	TCH_TRS = (TCH_TRS & 0xF0) | 0x05;
	TCH_P4D = 1;
	TCH_P2D = 0;
	
	// stabilisation
	delay_msec(1);
	
	x_pos = (adc_t) TCH_P3A;
	
	return x_pos;
}

adc_t tch_read_y() {
	adc_t y_pos;
	
	// Set I/O mode and pull pins high/low
	TCH_TRS = (TCH_TRS & 0xF0) | 0x0A;
	TCH_P1D = 1;
	TCH_P3D = 0;
	
	// stabilisation
	delay_msec(1);
	
	y_pos = (adc_t) TCH_P4A;
	
	return y_pos;
}

int read_numpad(int digits) {
	
	int i, val=0, result;
	adc_t x, y;
	uchar xy=0;
	
	// Loop for req digits
	for (i = 0; i < digits; ++i) {
		
		do {
			
			xy=0;
			
			// Bounds-checking for row
			if (R1MIN < y && y < R1MAX) {
				xy = 0x10;
			} else if (R2MIN < y && y < R2MAX) {
				xy = 0x20;
			} else if (R3MIN < y && y < R3MAX) {
				xy = 0x30;
			} else if (R4MIN < y && y < R4MAX) {
				xy = 0x40;
			}
			
			// Bounds checking for column
			if (C1MIN < y && y < C1MAX) {
				xy &= 0x01;
			} else if (C2MIN < y && y < C2MAX) {
				xy &= 0x02;
			} else if (C3MIN < y && y < C3MAX) {
				xy &= 0x03;
			}
			
		} while (xy&0xF0 == 0 || xy&0x0F == 0);
		// loop as long as either row or col is invalid
		
		// obtain number/other from xy-coords
		switch (xy) {
			case 0x11:
				val = 1;
				break;
			case 0x12:
				val = 2;
				break;
			case 0x13:
				val = 3;
				break;
			case 0x21:
				val = 4;
				break;
			case 0x22:
				val = 5;
				break;
			case 0x23:
				val = 6;
				break;
			case 0x31:
				val = 7;
				break;
			case 0x32:
				val = 8;
				break;
			case 0x33:
				val = 9;
				break;
			case 0x41:
				val = 0; // OH NO
				break;
			case 0x42:
				val = 0;
				break;
			case 0x43:
				val = 0; // OH NO
				break;
			default:
				val = 0;
				break;
		}
		
		// append digit
		result = result * 10 + val;
	}
	
	return result;
}

#endif
