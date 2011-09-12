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

#define TCH_FAIL 0xFF

void tch_init() {
	adc_init(0x02);
	ADC_ON = 0;
}

adc_lr_t tch_read_x() {
	adc_lr_t x_pos;
	
	// Set I/O mode and pull pins high/low
	TCH_TRS = (TCH_TRS & 0xF0) | 0x05;
	TCH_P4D = 1;
	TCH_P2D = 0;
	
	// stabilisation
	delay_msec(1);
	
	x_pos = (adc_lr_t) TCH_P3A;
	
	return x_pos;
}

adc_lr_t tch_read_y() {
	adc_lr_t y_pos;
	
	// Set I/O mode and pull pins high/low
	TCH_TRS = (TCH_TRS & 0xF0) | 0x0A;
	TCH_P1D = 1;
	TCH_P3D = 0;
	
	// stabilisation
	delay_msec(1);
	
	y_pos = (adc_lr_t) TCH_P4A;
	
	return y_pos;
}

uchar tch_read_block() {
	adc_lr_t x, y;
	uchar block = 0;
	
	x = tch_read_x();
	y = tch_read_y();
	
	if (MIN < x && x < MAX) {
		block = 0x10;
	} else if (MIN < x && x < MAX) {
		block = 0x20;
	} else if (MIN < x && x < MAX) {
		block = 0x30;
	} else if (MIN < x && x < MAX) {
		block = 0x40;
	} else if (MIN < x && x < MAX) {
		block = 0x50;
	} else {
		return TCH_FAIL;
	}
	
	if (MIN < y && y < MAX) {
		block &= 0x01;
	} else if (MIN < y && y < MAX) {
		block &= 0x02;
	} else if (MIN < y && y < MAX) {
		block &= 0x03;
	} else if (MIN < y && y < MAX) {
		block &= 0x04;
	} else {
		return TCH_FAIL;
	}
	
	return block;
}

int read_numpad(int digits) {
	
	int i, val=0, result;
	uchar block;
	
	ADC_ON = 1;
	
	// Loop for req digits
	for (i = 0; i < digits; ++i) {
		
		do {
			block = tch_read_block();
		} while (block != TCH_FAIL && 1 < block&0xF0 && block&0xF0 < 5);
		// loop as long as either row or col is invalid
		
		// obtain number/other from xy-coords
		switch (block) {
			case 0x21:
				val = 1;
				break;
			case 0x22:
				val = 4;
				break;
			case 0x23:
				val = 7;
				break;
			case 0x24:
				val = 0; // star
				break;
			case 0x31:
				val = 2;
				break;
			case 0x32:
				val = 4;
				break;
			case 0x33:
				val = 8;
				break;
			case 0x34:
				val = 0;
				break;
			case 0x41:
				val = 3;
				break;
			case 0x42:
				val = 6;
				break;
			case 0x43:
				val = 9;
				break;
			case 0x44:
				val = 0; // hex
				break;
			default:
				val = 0; // oh dear
				break;
		}
		
		// append digit
		result = result * 10 + val;
	}
	
	ADC_ON = 0;
	
	return result;
}

#endif
