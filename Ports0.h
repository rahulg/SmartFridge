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
#define LCD_CS1 R
#define LCD_CS2 R
#define LCD_RES R
#define LCD_RW  R
#define LCD_RS  R
#define LCD_EN  R

/*
 * TRIS
 */
#define TCH_TRS	TRISA
#define LCD_TRS TRISB

#endif
