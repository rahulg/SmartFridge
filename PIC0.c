/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __CPU_16F877__
#error "Please check build config! Target should be PIC16F877 controller"
#endif

#include "io16f877.h"

#include "Definitions.h"
#include "Ports0.h"
#include "Support.h"
#include "TouchPanel.h"
#include "LCD.h"

int main(void) {
	ADCON1 = 0x06;
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISE = 0x00;
	
	lcd_init();
	lcd_allon();
	delay_msec(100);
	lcd_clear();
	delay_msec(100);
	
	lcd_write_str("Hello World!");
}
