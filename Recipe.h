/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Ong Zibin
 *
 */

#ifndef __HEADER_RECIPE__
#define	__HEADER_RECIPE__

uchar recipe_check(uchar recipe) {
	uchar items = eep_read(recipe*6);
	
	if (items & 0x01 == 0x01) {
		check_milk();
		if (state < 25) {
			return 0;
		}
	}
	
	if (items & 0x02 == 0x02) {
		check_eggs();
		if (state == 0) {
			return 0;
		}
	}
	
	if (items & 0x04 == 0x04) {
		check_fruit();
		if (state < 25) {
			return 0;
		}
	}
	
	if (items & 0x08 == 0x08) {
		check_veg();
		if (state < 25) {
			return 0;
		}
	}
	
	if (items & 0x10 == 0x10) {
		check_choc();
		if (state == 0) {
			return 0;
		}
	}
	
	return 1;
}

#endif
