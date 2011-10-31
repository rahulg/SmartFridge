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

#define SNS_MLK adc_read(0)
#define SNS_VEG adc_read(1)
#define SNS_FRU adc_read(2)
#define SNS_EG1 adc_read(3)
#define SNS_EG2 adc_read(4)
#define SNS_CHO RE1

#define VOI_ENA RE2
#define VOI_RPS RC4
#define VOI_MOD RC5

#define MODE_REC 1
#define MODE_PLY 0

/*
 * Control Registers
 */
void init_ctrl() {
	ADCON1 = 0x82;
	TRISA = 0xFF;
	TRISB = 0x00;
	TRISC = 0x80;
	TRISD = 0xFC;
	TRISE = 0x02;
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;
	PORTD = 0x00;
	PORTE = 0x00;
}

#endif
