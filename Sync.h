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
#define DC2 0x12
#define SYN 0x16

typedef enum {
	SYNC_OFF,
	SYNC_IDLE,
	SYNC_WCMD,
	SYNC_WDAT,
	SYNC_WACK
} syncstate;

volatile syncstate sync_state;
uchar data_bytes = 0;
uchar recipe_data[7];

void sync_init() {
	uart_init();
	sync_state = SYNC_OFF;
}

void sync_update() {
	
	uchar addr;
	uchar inp_buf = RCREG;
	
	if (sync_state == SYNC_OFF) {
		return;
	}
	
	if (sync_state == SYNC_IDLE) {
		
		if (inp_buf == SYN) {
			TXREG = SYN;
			return;
		} else if (inp_buf == ENQ) {
			TXREG = ACK;
			sync_state = SYNC_WCMD;
			return;
		}
		
	}  else if (inp_buf == EOT ||
				(sync_state == SYNC_WACK && inp_buf == ACK)) {
		TXREG = EOT;
		sync_state = SYNC_IDLE;
		return;
		
	} else if (sync_state == SYNC_WCMD) {
		
		if (inp_buf == DC1) {
			TXREG = 0x80 | (PORTA & 0x1F); // TODO: load low grocery state
			sync_state = SYNC_WACK;
			return;
		} else if (inp_buf == DC2) {
			TXREG = DC2;
			data_bytes = 0;
			sync_state = SYNC_WDAT;
			return;
		}
		
	} else if (sync_state == SYNC_WDAT) {
		
		recipe_data[data_bytes] = inp_buf;
		TXREG = ACK;
		
		if (data_bytes == 6) {
			sync_state = SYNC_WACK;
			addr = (recipe_data[0] & 0x7F) * 6;
			eep_write(addr, (recipe_data[1] & 0x7F));
			eep_write(addr+1, recipe_data[2]);
			eep_write(addr+2, recipe_data[3]);
			eep_write(addr+3, recipe_data[4]);
			eep_write(addr+4, recipe_data[5]);
			eep_write(addr+5, recipe_data[6]);
		}
		
		++data_bytes;
		return;
		
	}
	
}

#endif
