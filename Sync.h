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
	SYNC_WDAT,
	SYNC_WACK
} syncstate;

volatile syncstate sync_state;
volatile uchar data_bytes = 0;
volatile uchar recipe_data[7];

void sync_init() {
	uart_init();
	sync_state = SYNC_IDLE;
}

void sync_update() {
	
	uchar inp_buf = RCREG;
	
	if (inp_buf == CAN || inp_buf == NAK
		|| (sync_state == SYNC_WACK && inp_buf == ACK)) {
		
		TXREG = EOT;
		data_bytes = 0;
		sync_state = SYNC_IDLE;
		return;
		
	} else if (sync_state == SYNC_IDLE) {
		
		if (inp_buf == ENQ) {
			TXREG = ACK;
			sync_state = SYNC_WCMD;
			return;
		}
		
	} else if (sync_state == SYNC_WCMD) {
		
		if (inp_buf == DC1) {
			TXREG = 0x80 | 0x00; // TODO: load low grocery state
			sync_state = SYNC_WACK;
			return;
		} else if (inp_buf == DC2) {
			TXREG = ACK;
			sync_state = SYNC_WDAT;
			return;
		}
		
	} else if (sync_state == SYNC_WDAT) {
		
		recipe_data[data_bytes++] = inp_buf;
		
		if (data_bytes == 6) {
			// write to eep now!
		}
		return;
		
	}
	TXREG = NAK;
	sync_state = SYNC_IDLE;
	
}

#endif
