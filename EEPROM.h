/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_EEP__
#define	__HEADER_EEP__

uchar eep_read(uchar addr) {
	
	EEADR = addr;
	EEPGD = 0; // Write to data EEPROM
	RD = 1; // Initiate read
	
	return EEDATA;
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

// Glitch-prevention: same function should not be called from main+ISR
void eep_write2(uchar addr, uchar data) {
	
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

/*
 * Reads a string from data EEPROM
 */
void eep_rstr(char* str, uchar index, uchar length) {
	for (ii = 0; ii < length; ++ii) {
		str[ii] = eep_read(index+ii);
	}
}

/*
 * Wipes data EEPROM
 */
void eep_set() {
	for (ii = 0; ii < 5; ++ii) {
		eep_write2(6*ii, 0x00);
		eep_write2(6*ii +1, 'E');
		eep_write2(6*ii +2, 'm');
		eep_write2(6*ii +3, 'p');
		eep_write2(6*ii +4, 't');
		eep_write2(6*ii +5, 'y');
	}
}

#endif
