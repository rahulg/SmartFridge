/*
 * EE2001 AY1112 S1
 * Group 1-5
 * A. G. Rahul
 *
 */

#ifndef __CPU_16F877__
#error "Please check build config! Target should be PIC16F877 controller"
#endif

#include "io16f877.h"

#include "Definitions.h"
#include "Ports0.h"
#include "Support.h"
#include "TouchPanel.h"

int main(void) {
	tmr1_init();
	return 0;
}
