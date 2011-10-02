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
#include "Support.h"
#include "Delay.h"
#include "Ports0.h"
#include "LCD.h"
#include "UserInterface.h"

int main(void) {
	
	init_ctrl();
	
	ui_init();
	while (1) {
		ui_update();
	}
}
