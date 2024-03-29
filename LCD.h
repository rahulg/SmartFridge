/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 * Thanks to
 * http://radzio.dxp.pl/ks0108/
 * http://joekwuen.blogspot.com/2011/01/project-pic-lcd-module.html
 *
 */

#ifndef __HEADER_LCD__
#define __HEADER_LCD__

#define LDATA 1
#define INSTR 0

uchar lcd_y = 0;
uchar lcd_x = 0;

void lcd_write(uchar data, uchar di, uchar cs1, uchar cs2) {
	TMR1ON = 0;
	
	// Initialise
	LCD_CS1 = LOW;
	LCD_CS2 = LOW;
	LCD_EN = LOW;
	LCD_RW = LOW;
	
	// Internal chip selects
	if (cs1)
		LCD_CS1 = HIGH;
	if (cs2)
		LCD_CS2 = HIGH;
	
	// Data / Instruction
	if (di)
		LCD_RS = HIGH;
	else
		LCD_RS = LOW;
	
	LCD_DAT = data;
	
	// falling edge will latch data in register
	LCD_EN = HIGH;
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	LCD_EN = LOW;
	
	TMR1ON = 1;
}

void lcd_init() {
	TMR1ON = 0;
	GIE = 0;
	
	// Reset LCD
	LCD_CS1 = HIGH;
	LCD_CS2 = HIGH;
	LCD_RES = LOW;
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	asm("nop; nop; nop; nop; nop;");
	LCD_RES = HIGH;
	
	// Display ON
	lcd_write(0x3F, INSTR, 1, 1);
	
	// Start on line 0
	lcd_write(0xC0, INSTR, 1, 1);
	
	GIE = 1;
	TMR1ON = 1;
}

void lcd_clear() {
	uchar x, y = 0;
	
	// Zero out all pages
	for (x = 0; x < 8; ++x) {
		lcd_write((x & 0x07) | 0xB8, INSTR, 1, 1);
		lcd_write(0x40, INSTR, 1, 1);
		for (y = 0; y < 64; ++y) {
			lcd_write(0x00, LDATA, 1, 1);
		}
	}
}

/* DISABLED
void lcd_allon() {
	uchar x, y = 0;
	
	// Fill all pages
	for (x = 0; x < 8; ++x) {
		lcd_write((x & 0x07) | 0xB8, INSTR, 1, 1);
		lcd_write(0x40, INSTR, 1, 1);
		for (y = 0; y < 64; ++y) {
			lcd_write(0xFF, LDATA, 1, 1);
		}
	}
}
 */

void lcd_set_page(uchar x, uchar y, uchar data) {
	
	uchar cs1, cs2;
	
	// Chip selects based on x-coord
	if (y < 64) {
		cs1 = 1;
		cs2 = 0;
	} else {
		cs1 = 0;
		cs2 = 1;
		y -= 64;
	}
	
	lcd_write(y + 0x40, INSTR, cs1, cs2);
	lcd_write(x + 0xB8, INSTR, cs1, cs2);
	lcd_write(data, LDATA, cs1, cs2);
	
}

void lcd_char(uchar data) {
	
	uchar i;
	uchar glyph[5] = {0,0,0,0,0};
	
	// Insufficient RAM to use a LUT
	// too much work to write to data EEPROM each time
	// Find: MOTHEROFALLSWITCH for end.
	// Forward slash remapped to tick, backslash remapped to cross
	switch(data)
	{
		case ' ':
			glyph[0] = 0x00;
			glyph[1] = 0x00;
			glyph[2] = 0x00;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case '!':
			glyph[0] = 0x00;
			glyph[1] = 0x00;
			glyph[2] = 0x5F;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case '#':
			glyph[0] = 0x14;
			glyph[1] = 0x3E;
			glyph[2] = 0x14;
			glyph[3] = 0x3E;
			glyph[4] = 0x14;
			break;
		case '$':
			glyph[0] = 0x24;
			glyph[1] = 0x2A;
			glyph[2] = 0x7F;
			glyph[3] = 0x2A;
			glyph[4] = 0x12;
			break;
		case '%':
			glyph[0] = 0x43;
			glyph[1] = 0x33;
			glyph[2] = 0x08;
			glyph[3] = 0x66;
			glyph[4] = 0x61;
			break;
		case '&':
			glyph[0] = 0x36;
			glyph[1] = 0x49;
			glyph[2] = 0x55;
			glyph[3] = 0x22;
			glyph[4] = 0x50;
			break;
		case '(':
			glyph[0] = 0x00;
			glyph[1] = 0x1C;
			glyph[2] = 0x22;
			glyph[3] = 0x41;
			glyph[4] = 0x00;
			break;
		case ')':
			glyph[0] = 0x00;
			glyph[1] = 0x41;
			glyph[2] = 0x22;
			glyph[3] = 0x1C;
			glyph[4] = 0x00;
			break;
		case '*':
			glyph[0] = 0x14;
			glyph[1] = 0x08;
			glyph[2] = 0x3E;
			glyph[3] = 0x08;
			glyph[4] = 0x14;
			break;
		case '+':
			glyph[0] = 0x08;
			glyph[1] = 0x08;
			glyph[2] = 0x3E;
			glyph[3] = 0x08;
			glyph[4] = 0x08;
			break;
		case ',':
			glyph[0] = 0x00;
			glyph[1] = 0x50;
			glyph[2] = 0x30;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case '-':
			glyph[0] = 0x08;
			glyph[1] = 0x08;
			glyph[2] = 0x08;
			glyph[3] = 0x08;
			glyph[4] = 0x08;
			break;
		case '.':
			glyph[0] = 0x00;
			glyph[1] = 0x60;
			glyph[2] = 0x60;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case '/':
			glyph[0] = 0x10;
			glyph[1] = 0x20;
			glyph[2] = 0x10;
			glyph[3] = 0x08;
			glyph[4] = 0x04;
			break;
		case '0':
			glyph[0] = 0x3E;
			glyph[1] = 0x51;
			glyph[2] = 0x49;
			glyph[3] = 0x45;
			glyph[4] = 0x3E;
			break;
		case '1':
			glyph[0] = 0x00;
			glyph[1] = 0x04;
			glyph[2] = 0x02;
			glyph[3] = 0x7F;
			glyph[4] = 0x00;
			break;
		case '2':
			glyph[0] = 0x42;
			glyph[1] = 0x61;
			glyph[2] = 0x51;
			glyph[3] = 0x49;
			glyph[4] = 0x46;
			break;
		case '3':
			glyph[0] = 0x22;
			glyph[1] = 0x41;
			glyph[2] = 0x49;
			glyph[3] = 0x49;
			glyph[4] = 0x36;
			break;
		case '4':
			glyph[0] = 0x18;
			glyph[1] = 0x14;
			glyph[2] = 0x12;
			glyph[3] = 0x7F;
			glyph[4] = 0x10;
			break;
		case '5':
			glyph[0] = 0x27;
			glyph[1] = 0x45;
			glyph[2] = 0x45;
			glyph[3] = 0x45;
			glyph[4] = 0x39;
			break;
		case '6':
			glyph[0] = 0x3E;
			glyph[1] = 0x49;
			glyph[2] = 0x49;
			glyph[3] = 0x49;
			glyph[4] = 0x32;
			break;
		case '7':
			glyph[0] = 0x01;
			glyph[1] = 0x01;
			glyph[2] = 0x71;
			glyph[3] = 0x09;
			glyph[4] = 0x07;
			break;
		case '8':
			glyph[0] = 0x36;
			glyph[1] = 0x49;
			glyph[2] = 0x49;
			glyph[3] = 0x49;
			glyph[4] = 0x36;
			break;
		case '9':
			glyph[0] = 0x26;
			glyph[1] = 0x49;
			glyph[2] = 0x49;
			glyph[3] = 0x49;
			glyph[4] = 0x3E;
			break;
		case ':':
			glyph[0] = 0x00;
			glyph[1] = 0x36;
			glyph[2] = 0x36;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case ';':
			glyph[0] = 0x00;
			glyph[1] = 0x56;
			glyph[2] = 0x36;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case '<':
			glyph[0] = 0x08;
			glyph[1] = 0x14;
			glyph[2] = 0x22;
			glyph[3] = 0x41;
			glyph[4] = 0x00;
			break;
		case '=':
			glyph[0] = 0x14;
			glyph[1] = 0x14;
			glyph[2] = 0x14;
			glyph[3] = 0x14;
			glyph[4] = 0x14;
			break;
		case '>':
			glyph[0] = 0x00;
			glyph[1] = 0x41;
			glyph[2] = 0x22;
			glyph[3] = 0x14;
			glyph[4] = 0x08;
			break;
		case '?':
			glyph[0] = 0x02;
			glyph[1] = 0x01;
			glyph[2] = 0x51;
			glyph[3] = 0x09;
			glyph[4] = 0x06;
			break;
		case '@':
			glyph[0] = 0x3E;
			glyph[1] = 0x41;
			glyph[2] = 0x59;
			glyph[3] = 0x55;
			glyph[4] = 0x5E;
			break;
		case 'A':
			glyph[0] = 0x7E;
			glyph[1] = 0x09;
			glyph[2] = 0x09;
			glyph[3] = 0x09;
			glyph[4] = 0x7E;
			break;
		case 'B':
			glyph[0] = 0x7F;
			glyph[1] = 0x49;
			glyph[2] = 0x49;
			glyph[3] = 0x49;
			glyph[4] = 0x36;
			break;
		case 'C':
			glyph[0] = 0x3E;
			glyph[1] = 0x41;
			glyph[2] = 0x41;
			glyph[3] = 0x41;
			glyph[4] = 0x22;
			break;
		case 'D':
			glyph[0] = 0x7F;
			glyph[1] = 0x41;
			glyph[2] = 0x41;
			glyph[3] = 0x41;
			glyph[4] = 0x3E;
			break;
		case 'E':
			glyph[0] = 0x7F;
			glyph[1] = 0x49;
			glyph[2] = 0x49;
			glyph[3] = 0x49;
			glyph[4] = 0x41;
			break;
		case 'F':
			glyph[0] = 0x7F;
			glyph[1] = 0x09;
			glyph[2] = 0x09;
			glyph[3] = 0x09;
			glyph[4] = 0x01;
			break;
		case 'G':
			glyph[0] = 0x3E;
			glyph[1] = 0x41;
			glyph[2] = 0x41;
			glyph[3] = 0x49;
			glyph[4] = 0x3A;
			break;
		case 'H':
			glyph[0] = 0x7F;
			glyph[1] = 0x08;
			glyph[2] = 0x08;
			glyph[3] = 0x08;
			glyph[4] = 0x7F;
			break;
		case 'I':
			glyph[0] = 0x00;
			glyph[1] = 0x41;
			glyph[2] = 0x7F;
			glyph[3] = 0x41;
			glyph[4] = 0x00;
			break;
		case 'J':
			glyph[0] = 0x30;
			glyph[1] = 0x40;
			glyph[2] = 0x40;
			glyph[3] = 0x40;
			glyph[4] = 0x3F;
			break;
		case 'K':
			glyph[0] = 0x7F;
			glyph[1] = 0x08;
			glyph[2] = 0x14;
			glyph[3] = 0x22;
			glyph[4] = 0x41;
			break;
		case 'L':
			glyph[0] = 0x7F;
			glyph[1] = 0x40;
			glyph[2] = 0x40;
			glyph[3] = 0x40;
			glyph[4] = 0x40;
			break;
		case 'M':
			glyph[0] = 0x7F;
			glyph[1] = 0x02;
			glyph[2] = 0x0C;
			glyph[3] = 0x02;
			glyph[4] = 0x7F;
			break;
		case 'N':
			glyph[0] = 0x7F;
			glyph[1] = 0x02;
			glyph[2] = 0x04;
			glyph[3] = 0x08;
			glyph[4] = 0x7F;
			break;
		case 'O':
			glyph[0] = 0x3E;
			glyph[1] = 0x41;
			glyph[2] = 0x41;
			glyph[3] = 0x41;
			glyph[4] = 0x3E;
			break;
		case 'P':
			glyph[0] = 0x7F;
			glyph[1] = 0x09;
			glyph[2] = 0x09;
			glyph[3] = 0x09;
			glyph[4] = 0x06;
			break;
		case 'Q':
			glyph[0] = 0x1E;
			glyph[1] = 0x21;
			glyph[2] = 0x21;
			glyph[3] = 0x21;
			glyph[4] = 0x5E;
			break;
		case 'R':
			glyph[0] = 0x7F;
			glyph[1] = 0x09;
			glyph[2] = 0x09;
			glyph[3] = 0x09;
			glyph[4] = 0x76;
			break;
		case 'S':
			glyph[0] = 0x26;
			glyph[1] = 0x49;
			glyph[2] = 0x49;
			glyph[3] = 0x49;
			glyph[4] = 0x32;
			break;
		case 'T':
			glyph[0] = 0x01;
			glyph[1] = 0x01;
			glyph[2] = 0x7F;
			glyph[3] = 0x01;
			glyph[4] = 0x01;
			break;
		case 'U':
			glyph[0] = 0x3F;
			glyph[1] = 0x40;
			glyph[2] = 0x40;
			glyph[3] = 0x40;
			glyph[4] = 0x3F;
			break;
		case 'V':
			glyph[0] = 0x1F;
			glyph[1] = 0x20;
			glyph[2] = 0x40;
			glyph[3] = 0x20;
			glyph[4] = 0x1F;
			break;
		case 'W':
			glyph[0] = 0x7F;
			glyph[1] = 0x20;
			glyph[2] = 0x10;
			glyph[3] = 0x20;
			glyph[4] = 0x7F;
			break;
		case 'X':
			glyph[0] = 0x41;
			glyph[1] = 0x22;
			glyph[2] = 0x1C;
			glyph[3] = 0x22;
			glyph[4] = 0x41;
			break;
		case 'Y':
			glyph[0] = 0x07;
			glyph[1] = 0x08;
			glyph[2] = 0x70;
			glyph[3] = 0x08;
			glyph[4] = 0x07;
			break;
		case 'Z':
			glyph[0] = 0x61;
			glyph[1] = 0x51;
			glyph[2] = 0x49;
			glyph[3] = 0x45;
			glyph[4] = 0x43;
			break;
		case '[':
			glyph[0] = 0x00;
			glyph[1] = 0x7F;
			glyph[2] = 0x41;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case '\\':
			glyph[0] = 0x22;
			glyph[1] = 0x14;
			glyph[2] = 0x08;
			glyph[3] = 0x14;
			glyph[4] = 0x22;
			/*
			glyph[0] = 0x02;
			glyph[1] = 0x04;
			glyph[2] = 0x08;
			glyph[3] = 0x10;
			glyph[4] = 0x20;
			 */
			break;
		case ']':
			glyph[0] = 0x00;
			glyph[1] = 0x00;
			glyph[2] = 0x41;
			glyph[3] = 0x7F;
			glyph[4] = 0x00;
			break;
		case '^':
			glyph[0] = 0x04;
			glyph[1] = 0x02;
			glyph[2] = 0x01;
			glyph[3] = 0x02;
			glyph[4] = 0x04;
			break;
		case '_':
			glyph[0] = 0x40;
			glyph[1] = 0x40;
			glyph[2] = 0x40;
			glyph[3] = 0x40;
			glyph[4] = 0x40;
			break;
		case 'a':
			glyph[0] = 0x20;
			glyph[1] = 0x54;
			glyph[2] = 0x54;
			glyph[3] = 0x54;
			glyph[4] = 0x78;
			break;
		case 'b':
			glyph[0] = 0x7F;
			glyph[1] = 0x44;
			glyph[2] = 0x44;
			glyph[3] = 0x44;
			glyph[4] = 0x38;
			break;
		case 'c':
			glyph[0] = 0x38;
			glyph[1] = 0x44;
			glyph[2] = 0x44;
			glyph[3] = 0x44;
			glyph[4] = 0x44;
			break;
		case 'd':
			glyph[0] = 0x38;
			glyph[1] = 0x44;
			glyph[2] = 0x44;
			glyph[3] = 0x44;
			glyph[4] = 0x7F;
			break;
		case 'e':
			glyph[0] = 0x38;
			glyph[1] = 0x54;
			glyph[2] = 0x54;
			glyph[3] = 0x54;
			glyph[4] = 0x18;
			break;
		case 'f':
			glyph[0] = 0x04;
			glyph[1] = 0x04;
			glyph[2] = 0x7e;
			glyph[3] = 0x05;
			glyph[4] = 0x05;
			break;
		case 'g':
			glyph[0] = 0x08;
			glyph[1] = 0x54;
			glyph[2] = 0x54;
			glyph[3] = 0x54;
			glyph[4] = 0x3c;
			break;
		case 'h':
			glyph[0] = 0x7f;
			glyph[1] = 0x08;
			glyph[2] = 0x04;
			glyph[3] = 0x04;
			glyph[4] = 0x78;
			break;
		case 'i':
			glyph[0] = 0x00;
			glyph[1] = 0x44;
			glyph[2] = 0x7D;
			glyph[3] = 0x40;
			glyph[4] = 0x00;
			break;
		case 'j':
			glyph[0] = 0x20;
			glyph[1] = 0x40;
			glyph[2] = 0x44;
			glyph[3] = 0x3d;
			glyph[4] = 0x00;
			break;
		case 'k':
			glyph[0] = 0x7f;
			glyph[1] = 0x10;
			glyph[2] = 0x28;
			glyph[3] = 0x44;
			glyph[4] = 0x00;
			break;
		case 'l':
			glyph[0] = 0x00;
			glyph[1] = 0x41;
			glyph[2] = 0x7f;
			glyph[3] = 0x40;
			glyph[4] = 0x00;
			break;
		case 'm':
			glyph[0] = 0x7c;
			glyph[1] = 0x04;
			glyph[2] = 0x78;
			glyph[3] = 0x04;
			glyph[4] = 0x78;
			break;
		case 'n':
			glyph[0] = 0x7c;
			glyph[1] = 0x08;
			glyph[2] = 0x04;
			glyph[3] = 0x04;
			glyph[4] = 0x78;
			break;
		case 'o':
			glyph[0] = 0x38;
			glyph[1] = 0x44;
			glyph[2] = 0x44;
			glyph[3] = 0x44;
			glyph[4] = 0x38;
			break;
		case 'p':
			glyph[0] = 0x7c;
			glyph[1] = 0x14;
			glyph[2] = 0x14;
			glyph[3] = 0x14;
			glyph[4] = 0x08;
			break;
		case 'q':
			glyph[0] = 0x08;
			glyph[1] = 0x14;
			glyph[2] = 0x14;
			glyph[3] = 0x14;
			glyph[4] = 0x7c;
			break;
		case 'r':
			glyph[0] = 0x00;
			glyph[1] = 0x7c;
			glyph[2] = 0x08;
			glyph[3] = 0x04;
			glyph[4] = 0x08;
			break;
		case 's':
			glyph[0] = 0x48;
			glyph[1] = 0x54;
			glyph[2] = 0x54;
			glyph[3] = 0x54;
			glyph[4] = 0x20;
			break;
		case 't':
			glyph[0] = 0x04;
			glyph[1] = 0x04;
			glyph[2] = 0x3f;
			glyph[3] = 0x44;
			glyph[4] = 0x44;
			break;
		case 'u':
			glyph[0] = 0x3c;
			glyph[1] = 0x40;
			glyph[2] = 0x40;
			glyph[3] = 0x20;
			glyph[4] = 0x7c;
			break;
		case 'v':
			glyph[0] = 0x1c;
			glyph[1] = 0x20;
			glyph[2] = 0x40;
			glyph[3] = 0x20;
			glyph[4] = 0x1c;
			break;
		case 'w':
			glyph[0] = 0x3c;
			glyph[1] = 0x40;
			glyph[2] = 0x30;
			glyph[3] = 0x40;
			glyph[4] = 0x3c;
			break;
		case 'x':
			glyph[0] = 0x44;
			glyph[1] = 0x28;
			glyph[2] = 0x10;
			glyph[3] = 0x28;
			glyph[4] = 0x44;
			break;
		case 'y':
			glyph[0] = 0x0c;
			glyph[1] = 0x50;
			glyph[2] = 0x50;
			glyph[3] = 0x50;
			glyph[4] = 0x3c;
			break;
		case 'z':
			glyph[0] = 0x44;
			glyph[1] = 0x64;
			glyph[2] = 0x54;
			glyph[3] = 0x4c;
			glyph[4] = 0x44;
			break;
		case '{':
			glyph[0] = 0x00;
			glyph[1] = 0x08;
			glyph[2] = 0x36;
			glyph[3] = 0x41;
			glyph[4] = 0x41;
			break;
		case '|':
			glyph[0] = 0x00;
			glyph[1] = 0x00;
			glyph[2] = 0x7f;
			glyph[3] = 0x00;
			glyph[4] = 0x00;
			break;
		case '}':
			glyph[0] = 0x41;
			glyph[1] = 0x41;
			glyph[2] = 0x36;
			glyph[3] = 0x08;
			glyph[4] = 0x00;
			break;
		case '~':
			glyph[0] = 0x02;
			glyph[1] = 0x01;
			glyph[2] = 0x02;
			glyph[3] = 0x04;
			glyph[4] = 0x02;
			break;
	}
	// END MOTHEROFALLSWITCH
	
	for (i = 0; i < 5; ++i) {
		lcd_set_page(lcd_y, lcd_x + i, glyph[i]);
	}
	
	lcd_set_page(lcd_y, lcd_x + 5, 0x00);
	
	// Cursor adjustments
	lcd_x += 6;
	if (lcd_x >= 128) {
		lcd_x = 0;
		++lcd_y;
		if (lcd_y >= 8) {
			lcd_y = 0;
		}
	}
	
}

void lcd_str(char* str, uchar cur_x, uchar cur_y) {
	GIE = 0;
	
	lcd_x = cur_x;
	lcd_y = cur_y;
	
	// Write chars until NULLCHAR
	while (*str) {
		lcd_char(*(str++));
	}
	
	GIE = 1;
}

/*
 * Prints a string in the middle of the top line
 */
void lcd_header(char* str) {
	GIE = 0;
	
	lcd_str(str, (128-(strlen(str)*6))/2, 0);
	
	GIE = 1;
}

#endif
