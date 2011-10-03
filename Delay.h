/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __HEADER_DELAY__
#define	__HEADER_DELAY__

void delay_msec(uchar count) {
	for (del1 = 0; del1 < count; ++del1) {
		for (del2 = 0; del2 < 5000; ++del2);
	}
}

void delay_usec(uchar count) {
	for (del1 = 0; del1 < count; ++del1) {
		for (del2 = 0; del2 < 5; ++del2);
	}
}

#endif
