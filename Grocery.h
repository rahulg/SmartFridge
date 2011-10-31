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

#define EGG_0 0x11E
#define EGG_1 0x1C2
#define EGG_2 0x265

void check_eggs() {
	state = 0;
	
	if (SNS_EG1 >= EGG_2) {
		state += 3;
	} else if (SNS_EG1 >= EGG_1) {
		state += 2;
	} else if (SNS_EG1 >= EGG_0) {
		state += 1;
	} else {
		state += 0;
	}
	
	if (SNS_EG2 >= EGG_2) {
		state += 3;
	} else if (SNS_EG2 >= EGG_1) {
		state += 2;
	} else if (SNS_EG2 >= EGG_0) {
		state += 1;
	} else {
		state += 0;
	}
}

void check_choc() {
	state = SNS_CHO;
}

void check_milk() {
	if (SNS_MLK >= PERC_75) {
		state = 75;
	} else if (SNS_MLK >= PERC_50) {
		state = 50;
	} else if (SNS_MLK >= PERC_25) {
		state = 25;
	} else {
		state = 0;
	}
}

void check_fruit() {
	if (SNS_FRU >= PERC_75) {
		state = 75;
	} else if (SNS_FRU >= PERC_50) {
		state = 50;
	} else if (SNS_FRU >= PERC_25) {
		state = 25;
	} else {
		state = 0;
	}
}

void check_veg() {
	if (SNS_VEG >= PERC_75) {
		state = 75;
	} else if (SNS_VEG >= PERC_50) {
		state = 50;
	} else if (SNS_VEG >= PERC_25) {
		state = 25;
	} else {
		state = 0;
	}
}

#endif
