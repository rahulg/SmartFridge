/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_TMR1__
#define	__HEADER_TMR1__

void tmr1_init() {
	//Timer clock source is the internal clock.
	TMR1CS=0;
	// set prescalar value of 1:8 i.e. timer1 count=8x200ns=1600nS.
	T1CKPS1=1;
	T1CKPS0=1;
	//Refer to the datasheet for the organization of interrupts.
	GIE=1; //global interrupt enabled.
	PEIE=1; //peripheral interrupt enabled.
	TMR1IE=1; //enable timer1 interrupt.
}

void tmr1_load(uint value) {
	TMR1ON=0; //disable timer1 before loading the values.
	TMR1IF=0; //timer1 flag cleared.
	
	TMR1H=value>>8; //load timer1 high register.
	TMR1L=value&0xFF; //load timer1 low register.
	TMR1ON=1; //enable timer1.
}

#endif
