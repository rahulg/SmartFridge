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
#include "Ports0.h"
#include "LCD.h"
#include "UART.h"
#include "UserInterface.h"

volatile syncstate sync_state = SYNC_IDLE;
volatile uchar inbuf;

/*
 * Interrupt Service Routine
 */
#pragma vector=0x04
__interrupt void isr(void)
{
	if (RCIE == 1) {
		if (sync_state == SYNC_IDLE) {
			inbuf = RCREG;
			if (inbuf == ENQ) {
				TXREG = ACK;
				sync_state = SYNC_WCMD;
			} else {
				TXREG = NAK;
				sync_state = SYNC_IDLE;
			}
		} else if (sync_state == SYNC_WCMD) {
			inbuf = RCREG;
			if (inbuf == DC1) {
				TXREG = 0x00; // TODO: load low state
				sync_state = SYNC_WACK;
			} else if (inbuf == CAN) {
				TXREG = ACK;
				sync_state = SYNC_IDLE;
			} else {
				TXREG = NAK;
				sync_state = SYNC_IDLE;
			}
		} else if (sync_state == SYNC_WACK) {
			inbuf = RCREG;
			if (inbuf == ACK) {
				TXREG = EOT;
				sync_state = SYNC_IDLE;
			} else {
				TXREG = NAK;
				sync_state = SYNC_IDLE
			}
		} else {
			sync_state = SYNC_IDLE;
		}
	}
}

int main(void) {
	
	init_ctrl();
	
	ui_init();
	while (1) {
		ui_update();
	}
}
