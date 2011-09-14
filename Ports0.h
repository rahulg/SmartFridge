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
 * Pin Allocations: Touch Panel Digital
 */
#define TCH_P4D	RA0
#define TCH_P3D	RA1
#define TCH_P2D	RA2
#define TCH_P1D	RA3

/*
 * Pin Allocations: Touch Panel ADC
 */
#define TCH_P4A	adc_read(0,LOWRES)
#define TCH_P3A	adc_read(1,LOWRES)

/*
 * Pin Allocations: LCD
 */
#define LCD_DAT PORTB
#define LCD_CS1 RA4
#define LCD_CS2 RA5
#define LCD_RES RE0
#define LCD_RW  RC4
#define LCD_RS  RE1
#define LCD_EN  RE2

/*
 * Pin Allocations
 */
#define EM_LOCK RC2
#define D_MOTOR RC0
#define D_PUSHB RC1

/*
 * TRIS
 */
#define TCH_TRS	TRISA
#define LCD_TR1 TRISB
#define LCD_TR2 TRISA
#define LCD_TR3 TRISE

#endif
