/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __HEADER_PORTS0__
#define	__HEADER_PORTS0__

#include "ADC.h"

/*
 * Pin Allocations: LCD
 */
#define LCD_DAT PORTB
#define LCD_CS1 RC0
#define LCD_CS2 RC1
#define LCD_RES RC2
#define LCD_RW  RC3
#define LCD_RS  RD0
#define LCD_EN  RD1

/*
 * Control Registers
 */
void init_ctrl() {
	TRISA = 0x0F;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
}

#endif
