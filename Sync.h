/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_SYNC__
#define	__HEADER_SYNC__

#define ENQ 0x05
#define ACK 0x06
#define NAK 0x15
#define EOT 0x04
#define DC1 0x11
#define CAN 0x18

typedef enum {
	SYNC_IDLE,
	SYNC_WCMD,
	SYNC_WACK
} syncstate;

volatile syncstate sync_state;

void sync_init() {
	uart_init();
	sync_state = SYNC_IDLE;
}

void sync_update() {
	uchar inbuf = RCREG;
	if (sync_state == SYNC_IDLE) {
		if (inbuf == ENQ) {
			TXREG = ACK;
			sync_state = SYNC_WCMD;
		} else {
			TXREG = NAK;
			sync_state = SYNC_IDLE;
		}
	} else if (sync_state == SYNC_WCMD) {
		if (inbuf == DC1) {
			TXREG = 0x00; // TODO: load low grocery state
			sync_state = SYNC_WACK;
		} else if (inbuf == CAN) {
			TXREG = ACK;
			sync_state = SYNC_IDLE;
		} else {
			TXREG = NAK;
			sync_state = SYNC_IDLE;
		}
	} else if (sync_state == SYNC_WACK) {
		if (inbuf == ACK) {
			TXREG = EOT;
			sync_state = SYNC_IDLE;
		} else {
			TXREG = NAK;
			sync_state = SYNC_IDLE;
		}
	} else {
		sync_state = SYNC_IDLE;
	}
}

#endif
