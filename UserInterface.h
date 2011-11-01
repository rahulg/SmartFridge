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
	UI_MEMO,
	UI_DEBUG
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
	char value[3] = { 0, 0, 0 };
	
	state = 0;
	check_eggs();
	value[0] = ' ';
	value[1] = (state % 10) + 0x30;
	lcd_str(value, 42, 3);
	
	state = 0;
	check_milk();
	if (state < 75) {
		value[0] = (state / 10) + 0x30;
		value[1] = (state % 10) + 0x30;
	} else {
		value[0] = 'O';
		value[1] = 'K';
	}
	lcd_str(value, 42, 2);
	
	state = 0;
	check_fruit();
	if (state < 75) {
		value[0] = (state / 10) + 0x30;
		value[1] = (state % 10) + 0x30;
	} else {
		value[0] = 'O';
		value[1] = 'K';
	}
	lcd_str(value, 42, 4);
	
	state = 0;
	check_veg();
	if (state < 75) {
		value[0] = (state / 10) + 0x30;
		value[1] = (state % 10) + 0x30;
	} else {
		value[0] = 'O';
		value[1] = 'K';
	}
	lcd_str(value, 42, 5);
	
	state = 0;
	check_choc();
	lcd_str(state ? "/" : "\\", 42, 6);
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

void chk_recipe(uchar recipe) {
	uchar tmp1, tmp2 = 42;
	char outp[2] = {0, 0};
	tmp1 = recipe_check(recipe);
	outp[0] = tmp1 ? '/' : '\\';
	
	switch (recipe) {
		case 0:
			tmp1 = 2;
			break;
		case 1:
			tmp1 = 4;
			break;
		case 2:
			tmp1 = 6;
			break;
		case 3:
			tmp1 = 2;
			tmp2 = roffset(8);
			break;
		case 4:
			tmp1 = 4;
			tmp2 = roffset(8);
			break;
		default:
			break;
	}
	
	lcd_str(outp, tmp2, tmp1);
}

void ui_memo() {
	lcd_clear();
	lcd_header("Memo");
	lcd_str("Recording...", 28, 4);
	lcd_str("Stop>", roffset(5), 2);
}

void ui_debug_refresh() {
	
	uint sensor_val;
	char* hexstr = "0123456789ABCDEF";
	char show[6] = {'0', 'x', ' ', ' ', ' ', 0x00};
	
	lcd_clear();
	
	sensor_val = SNS_MLK;
	show[2] = hexstr[(sensor_val&0xF00) >>8];
	show[3] = hexstr[(sensor_val&0x0F0) >>4];
	show[4] = hexstr[(sensor_val&0x00F)];
	lcd_str(show, roffset(5), 2);
	
	sensor_val = SNS_FRU;
	show[2] = hexstr[(sensor_val&0xF00) >>8];
	show[3] = hexstr[(sensor_val&0x0F0) >>4];
	show[4] = hexstr[(sensor_val&0x00F)];
	lcd_str(show, roffset(5), 3);
	
	sensor_val = SNS_VEG;
	show[2] = hexstr[(sensor_val&0xF00) >>8];
	show[3] = hexstr[(sensor_val&0x0F0) >>4];
	show[4] = hexstr[(sensor_val&0x00F)];
	lcd_str(show, roffset(5), 4);
	
	sensor_val = SNS_EG1;
	show[2] = hexstr[(sensor_val&0xF00) >>8];
	show[3] = hexstr[(sensor_val&0x0F0) >>4];
	show[4] = hexstr[(sensor_val&0x00F)];
	lcd_str(show, roffset(5), 5);
	
	sensor_val = SNS_EG2;
	show[2] = hexstr[(sensor_val&0xF00) >>8];
	show[3] = hexstr[(sensor_val&0x0F0) >>4];
	show[4] = hexstr[(sensor_val&0x00F)];
	lcd_str(show, roffset(5), 6);
}

void ui_debug() {
	lcd_header("Debug");
	lcd_str("Milk", 0, 2);
	lcd_str("Fruit", 0, 3);
	lcd_str("Vegetables", 0, 4);
	lcd_str("Egg 1", 0, 5);
	lcd_str("Egg 2", 0, 6);
	
	ui_debug_refresh();
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
				VOI_MOD = 0;
				VOI_RPS = MODE_REC;
				VOI_ENA = 1;
				ui_memo();
				break;
			case BUTTON_R2:
				VOI_MOD = 0;
				VOI_RPS = MODE_PLY;
				VOI_ENA = 1;
				delay_msec(REC_PULSE);
				VOI_ENA = 1;
				break;
			case BUTTON_R3:
				eep_set();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_GROC) {
		switch (pressed) {
			case BUTTON_L1:
				ui_state = UI_DEBUG;
				ui_debug();
				break;
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
				chk_recipe(0);
				break;
			case BUTTON_L2:
				chk_recipe(1);
				break;
			case BUTTON_L3:
				chk_recipe(2);
				break;
			case BUTTON_R1:
				chk_recipe(3);
				break;
			case BUTTON_R2:
				chk_recipe(4);
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
				VOI_ENA = 0;
				ui_main();
				break;
			default:
				break;
		}
	} else if (ui_state == UI_DEBUG) {
		switch (pressed) {
			case BUTTON_R1:
				ui_debug_refresh();
				break;
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
	if (pressed != BUTTON_NIL) {
		ui_manage(pressed);
	}
}

#endif
