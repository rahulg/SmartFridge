/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __HEADER_PORTS0__
#define	__HEADER_PORTS0__

/*
 * Pin Allocations
 */
#define LCD_DAT PORTB

// Proper Alloc: RC0, RC1, RC2, RC3, RD0, RD1
#define LCD_CS1 RA5
#define LCD_CS2 RA4
#define LCD_RES RA3
#define LCD_RW  RA2
#define LCD_RS  RA1
#define LCD_EN  RA0

#define BTN_L1 RC0
#define BTN_L2 RC1
#define BTN_L3 RC2
#define BTN_R1 RC3
#define BTN_R2 RC4
#define BTN_R3 RC5

/*
 * Control Registers
 */
void init_ctrl() {
	ADCON1 = 0x06;
	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0xBF;
	TRISD = 0x00;
	TRISE = 0xFF;
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTD = 0x00;
}

#endif
