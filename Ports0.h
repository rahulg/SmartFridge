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
// Fake Alloc: RA5, RA4, RA3, RA2, RA1, RA0
#define LCD_CS1 RC0
#define LCD_CS2 RC1
#define LCD_RES RC2
#define LCD_RW  RC3
#define LCD_RS  RD0
#define LCD_EN  RD1

#define BTN_L1 RD7
#define BTN_L2 RD5
#define BTN_L3 RD3
#define BTN_R1 RD6
#define BTN_R2 RD4
#define BTN_R3 RD2

#define OUT_REC RC4

#define TMP_GR PORTA
#define TMP_R0 RA5
#define TMP_R1 RE0
#define TMP_R2 RE1

/*
 * Control Registers
 */
void init_ctrl() {
	ADCON1 = 0x06;
	TRISA = 0x1F;
	TRISB = 0x00;
	TRISC = 0x80;
	TRISD = 0xFC;
	TRISE = 0x00;
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
}

#endif
