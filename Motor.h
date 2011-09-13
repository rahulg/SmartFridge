/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_MOTOR__
#define	__HEADER_MOTOR__

void motor_move(uint time) {
	D_MOTOR = HIGH;
	delay_msec(time);
	D_MOTOR = LOW;
	delay_usec(2);
}

#endif
