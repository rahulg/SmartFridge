/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __HEADER_SUPPORT__
#define	__HEADER_SUPPORT__

/*
 * atoi: offset for char to int
 * itoa: offset for int to char
 */
#define atoi(a) (a-0x30)
#define itoa(a) (a+0x30)

uchar strlen(char* str) {
	ii = 0;
	while (*str++) {
		++ii;
	}
	return ii;
}

#endif
