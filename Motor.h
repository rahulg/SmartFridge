/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_SERVO__
#define	__HEADER_SERVO__

void servo_move(uint time) {
	D_SERVO = HIGH;
	delay_usec(time);
	D_SERVO = LOW;
	delay_usec(2);
}

#endif
