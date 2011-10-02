/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_UART__
#define	__HEADER_UART__

void uart_init() {
	// RC7 as input, RC6 as output
	TRISC = TRISC | 0x80;
	TRISC = TRISC & 0xBF
	
	BRGH = 0; // Low Speed
	SPBRG = 0x81; // 0x81 = 2400, 0x1F = 9600
	
	// Asynch mode
	SYNC = 0;
	SPEN = 1;
	
	// Disable 9-bit mode
	TX9 = 0;
	RX9 = 0;
	TX9D = 0;
	RX9D = 0;
	
	TRMT = 1; // Set TSR empty
	
	TXEN = 1; // Enable TX
	CREN = 1; // Enable RX
	
	TXIE = 0; // Disable TX interrupt
	RCIE = 1; // Enable RX interrupt
	PEIE = 1; // Enable peripheral interrupts
	GIE = 1; // Enable interrupts
}

#endif
