/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_EEP__
#define	__HEADER_EEP__

uchar eep_read(uchar addr) {
	uchar data;
	
	EEADR = addr;
	EEPGD = 0; // Write to data EEPROM
	RD = 1; // Initiate read
	
	data = EEDATA;
	delay_msec(20);
	return data;
}

void eep_write(uchar addr, uchar data) {
	
	EEADR = addr;
	EEDATA = data;
	EEPGD = 0; // Write to data EEPROM

	WREN = 1; // Enable writes
	while (GIE) {
		GIE = 0;
	}
	// Special
	EECON2 = 0x55;
	EECON2 = 0xAA;
	WR = 1; // Initiate write
	
	while (!EEIF);
	WREN = 0;
	EEIF = 0;
	GIE = 1;
	
}

#endif
