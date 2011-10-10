/*
 * EE2001 AY1112 S1
 * Group 1-5
 * Rahul A.G.
 *
 */

#ifndef __HEADER_UI__
#define	__HEADER_UI__

#define REC_PULSE 40

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
	UI_MEMO
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

void recipe_name(uchar index, char* str) {
	eep_rstr(str, index * 6 + 1, 5);
}

void chk_sync() {
	if (sync_state == SYNC_OFF) {
		lcd_str("OFF", 42, 6);
	} else {
		lcd_str("ON ", 42, 6);
	}
}

void ui_main() {
	lcd_clear();
	lcd_header("SmartFridge");
	lcd_str("<Groceries", 0, 2);
	lcd_str("<Recipes", 0, 4);
	lcd_str("<Sync:", 0, 6);
	lcd_str("Record>", roffset(7), 2);
	lcd_str("Play>", roffset(5), 4);
	lcd_str("Reset>", roffset(6), 6);
	chk_sync();
}

void chk_grocery() {
	// [SIM] Read DIP switches & output ticks and crosses
	temp = TMP_GR & 0x1F;
	for (ii = 0; ii < 5; ++ii) {
		lcd_str(temp & (0x01<<ii) ? "/" : "\\", 42, ii+2);
	}
}

void ui_groceries() {
	lcd_clear();
	lcd_header("Groceries");
	lcd_str("Milk", 6, 2);
	lcd_str("Eggs", 6, 3);
	lcd_str("Fruit", 6, 4);
	lcd_str("Veg", 6, 5);
	lcd_str("Chocs", 6, 6);
	lcd_str("Refresh>", roffset(8), 2);
	lcd_str("Back>", roffset(5), 6);
	chk_grocery();
}

void ui_recipes() {
	char str[7];
	str[6] = 0x00; // NULL char
	lcd_clear();
	lcd_header("Recipes");
	str[0] = '<';
	recipe_name(0, str+1);
	lcd_str(str, 0, 2);
	recipe_name(1, str+1);
	lcd_str(str, 0, 4);
	recipe_name(2, str+1);
	lcd_str(str, 0, 6);
	str[5] = '>';
	recipe_name(3, str);
	lcd_str(str, roffset(6), 2);
	recipe_name(4, str);
	lcd_str(str, roffset(6), 4);
	lcd_str("Back>", roffset(5), 6);
}

void ui_memo() {
	lcd_clear();
	lcd_header("Memo");
	lcd_str("Recording...", 28, 4);
	lcd_str("Stop>", roffset(5), 2);
}

/*
 * [SIM] Output recipe code
 */
void tmp_recout(uchar code) {
	TMP_R2 = (code & 0x04) >> 2;
	TMP_R1 = (code & 0x02) >> 1;
	TMP_R0 = code * 0x01;
	delay_msec(REC_PULSE);
	TMP_R2 = 0; TMP_R1 = 0; TMP_R0 = 0;
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
				if (sync_state == SYNC_OFF) {
					sync_state = SYNC_IDLE;
				} else {
					sync_state = SYNC_OFF;
				}
				chk_sync();
				break;
			case BUTTON_R1:
				ui_state = UI_MEMO;
				OUT_REC = 1;
				ui_memo();
				delay_msec(REC_PULSE);
				OUT_REC = 0;
				break;
			case BUTTON_R2:
				OUT_PLY = 1;
				delay_msec(REC_PULSE);
				OUT_PLY = 0;
				break;
			case BUTTON_R3:
				eep_set();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_GROC) {
		switch (pressed) {
			case BUTTON_R1:
				chk_grocery();
				break;
			case BUTTON_R3:
				ui_state = UI_MAIN;
				ui_main();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_REC) {
		switch (pressed) {
			case BUTTON_L1:
				tmp_recout(1);
				break;
			case BUTTON_L2:
				tmp_recout(2);
				break;
			case BUTTON_L3:
				tmp_recout(3);
				break;
			case BUTTON_R1:
				tmp_recout(4);
				break;
			case BUTTON_R2:
				tmp_recout(5);
				break;
			case BUTTON_R3:
				ui_state = UI_MAIN;
				ui_main();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_MEMO) {
		switch (pressed) {
			case BUTTON_R1:
				ui_state = UI_MAIN;
				OUT_REC = 1;
				ui_main();
				delay_msec(REC_PULSE);
				OUT_REC = 0;
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
	if (pressed != BUTTON_NIL) {
		ui_manage(pressed);
	}
}

#endif