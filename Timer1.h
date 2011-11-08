/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_TMR1__
#define	__HEADER_TMR1__

void timer1_init() {
	//Timer clock source is the internal clock.
	TMR1CS=0;
	
	// set prescalar value of 1:8 i.e. timer1 count=8x200ns=1600nS.
	T1CKPS1=1;
	T1CKPS0=1;
	
	GIE = 1; //global interrupt enabled.
	PEIE = 1; //peripheral interrupt enabled.
	TMR1IE = 1; //enable timer1 interrupt.
}

void timer1_load() {
	TMR1ON = 0;
	TMR1IF = 0;
	
	TMR1H = 0x00;
	TMR1L = 0x00;
	
	TMR1ON = 1;
}

#endif
