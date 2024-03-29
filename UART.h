/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_UART__
#define __HEADER_UART__

void uart_init() {
	// 2400 = 0, 0x81
	// 9600 = 0, 0x1F
	// 33.6 = 1, 0x24
	// 57.6 = 1, 0x14
	BRGH = 1; // Low/High Speed
	SPBRG = 0x14; // Baud rate generator
	
	// Asynch mode
	SYNC = 0;
	SPEN = 1;
	
	// Disable 9-bit mode
	TX9 = 0;
	RX9 = 0;
	TX9D = 0;
	RX9D = 0;
	
	// Set TSR empty
	TRMT = 1;
	
	// Enable TX / RX
	TXEN = 1;
	CREN = 1;
	
	TXIE = 0; // Disable TX interrupt
	RCIE = 1; // Enable RX interrupt
	PEIE = 1; // Enable peripheral interrupts
	GIE = 1; // Enable interrupts
}

#endif
