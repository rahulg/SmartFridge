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
#include "Support.h"
#include "Delay.h"
#include "ADC.h"
#include "Ports0.h"
#include "Timer1.h"
#include "LCD.h"
#include "UART.h"
#include "EEPROM.h"
#include "Grocery.h"
#include "Recipe.h"
#include "Sync.h"
#include "UserInterface.h"

/*
 * Interrupt Service Routine
 */
#pragma vector=0x04
__interrupt void isr(void)
{
	if (RCIF == 1) {
		if (OERR == 1) {
			TXREG = EOT;
			temp = RCREG;
			CREN = 0;
			CREN = 1;
		} else {
			sync_update();
		}
	}
	if (TMR1IF == 1) {
		TMR1ON = 0;
		TMR1IF = 0;
		TMR1H = 0x00;
		TMR1L = 0x00;
		
		check_milk();
		check_eggs();
		check_fruit();
		check_veg();
		check_choc();
		
		TMR1ON = 1;
	}
}

int main(void) {
	
	init_ctrl();
	adc_init();
	sync_init();
	timer1_init();
	ui_init();
	timer1_load();
	
	while (1) {
		ui_update();
	}
}
