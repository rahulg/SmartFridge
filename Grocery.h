/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Ong Zibin
 *
 */

#ifndef __HEADER_GROCERY__
#define	__HEADER_GROCERY__

#define PERC_25 0x0FF
#define PERC_50 0x1FF
#define PERC_75 0x2FF

#define EGG_0 0x120
#define EGG_1 0x190
#define EGG_2 0x250

volatile uchar st_milk, st_eggs, st_fru, st_veg, st_choc;

void check_eggs() {
	st_eggs = 0;
	
	if (SNS_EG1 >= EGG_2) {
		st_eggs += 3;
	} else if (SNS_EG1 >= EGG_1) {
		st_eggs += 2;
	} else if (SNS_EG1 >= EGG_0) {
		st_eggs += 1;
	}
	
	if (SNS_EG2 >= EGG_2) {
		st_eggs += 3;
	} else if (SNS_EG2 >= EGG_1) {
		st_eggs += 2;
	} else if (SNS_EG2 >= EGG_0) {
		st_eggs += 1;
	}
}

void check_choc() {
	st_choc = SNS_CHO;
}

void check_fruit() {
	if (SNS_FRU >= PERC_75) {
		st_fru = 75;
	} else if (SNS_FRU >= PERC_50) {
		st_fru = 50;
	} else if (SNS_FRU >= PERC_25) {
		st_fru = 25;
	} else {
		st_fru = 0;
	}
}

void check_milk() {
	if (SNS_MLK >= PERC_75) {
		st_milk = 75;
	} else if (SNS_MLK >= PERC_50) {
		st_milk = 50;
	} else if (SNS_MLK >= PERC_25) {
		st_milk = 25;
	} else {
		st_milk = 0;
	}
}

void check_veg() {
	if (SNS_VEG >= PERC_75) {
		st_veg = 75;
	} else if (SNS_VEG >= PERC_50) {
		st_veg = 50;
	} else if (SNS_VEG >= PERC_25) {
		st_veg = 25;
	} else {
		st_veg = 0;
	}
}

#endif
