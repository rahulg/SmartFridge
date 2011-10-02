/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_UI__
#define	__HEADER_UI__

#define roffset(len) (128-(6*len))

typedef enum {
	BUTTON_L1,
	BUTTON_L2,
	BUTTON_L3,
	BUTTON_R1,
	BUTTON_R2,
	BUTTON_R3,
	BUTTON_NIL
} button;

typedef enum {
	UI_MAIN,
	UI_GROC,
	UI_REC,
	UI_SYNC
} uistate;

uistate ui_state = UI_MAIN;

button button_poll() {
	if (BTN_L1) {
		while (BTN_L1);
		return BUTTON_L1;
	} else if (BTN_L2) {
		while (BTN_L2);
		return BUTTON_L2;
	} else if (BTN_L3) {
		while (BTN_L3);
		return BUTTON_L3;
	} else if (BTN_R1) {
		while (BTN_R1);
		return BUTTON_R1;
	} else if (BTN_R2) {
		while (BTN_R2);
		return BUTTON_R2;
	} else if (BTN_R3) {
		while (BTN_R3);
		return BUTTON_R3;
	} else {
		return BUTTON_NIL;
	}
}

void ui_main() {
	lcd_clear();
	lcd_header("SmartFridge");
	lcd_str("<Groceries", 0, 2);
	lcd_str("<Recipes", 0, 4);
	lcd_str("<Sync", 0, 6);
}

void ui_groceries() {
	uchar i;
	lcd_clear();
	lcd_header("Groceries");
	lcd_str("Milk", 6, 2);
	lcd_str("Eggs", 6, 3);
	lcd_str("Fruit", 6, 4);
	lcd_str("Veg", 6, 5);
	lcd_str("Chocs", 6, 6);
	lcd_str("Back>", roffset(5), 6);
	for (i = 0; i < 5; ++i) {
		lcd_str(i%2?"/":"\\", 42, i+2);
	}
}

void ui_recipes() {
	lcd_clear();
	lcd_header("Recipes");
	lcd_str("<R1", 0, 2);
	lcd_str("<R2", 0, 4);
	lcd_str("<R3", 0, 6);
	lcd_str("R4>", roffset(3), 2);
	lcd_str("R5>", roffset(3), 4);
	lcd_str("Back>", roffset(5), 6);
}

void ui_sync() {
	lcd_clear();
	lcd_header("Sync");
	// TODO: initiate UART sync here
	lcd_str("Back>", roffset(5), 6);
}

void ui_manage(button pressed) {
	if (ui_state == UI_MAIN) {
		switch (pressed) {
			case BUTTON_L1:
				ui_state = UI_GROC;
				ui_groceries();
				break;
			case BUTTON_L2:
				ui_state = UI_REC;
				ui_recipes();
				break;
			case BUTTON_L3:
				ui_state = UI_SYNC;
				ui_sync();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_GROC) {
		switch (pressed) {
			case BUTTON_R3:
				ui_state = UI_MAIN;
				ui_main();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_REC) {
		// TODO: implement recipe selection
		switch (pressed) {
			case BUTTON_R3:
				ui_state = UI_MAIN;
				ui_main();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_SYNC) {
		switch (pressed) {
			case BUTTON_R3:
				ui_state = UI_MAIN;
				ui_main();
				break;
			default:
				break;
		}
	} else {
		ui_state = UI_MAIN;
		ui_main();
	}
}

void ui_init() {
	lcd_init();
	ui_state = UI_MAIN;
	ui_main();
}

void ui_update() {
	button pressed = BUTTON_NIL;
	pressed = button_poll();
	ui_manage(pressed);
}

#endif
