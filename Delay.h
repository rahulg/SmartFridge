/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __HEADER_DELAY__
#define	__HEADER_DELAY__

void delay_msec(int count) {
	int i, j;
	for (i = 0; i < count; ++i) {
		for (j = 0; j < 5000; ++j);
	}
}

void delay_usec(int count) {
	int i, j;
	for (i = 0; i < count; ++i) {
		for (j = 0; j < 5; ++j);
	}
}

#endif
