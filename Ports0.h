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
 * Pin Allocations: Digital IO
 */
#define TCH_P4D	RA0
#define TCH_P3D	RA1
#define TCH_P2D	RA2
#define TCH_P1D	RA3

/*
 * Pin Allocations: ADC
 */
#define TCH_P4A	adc_read(0,LOWRES)
#define TCH_P3A	adc_read(1,LOWRES)

/*
 * TRIS
 */
#define TCH_TRS	TRISA

#endif
