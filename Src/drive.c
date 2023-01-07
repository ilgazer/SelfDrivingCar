
#include "drive.h"

static uint8_t mode;
int joystick_x_calib = -1;
int joystick_y_calib = -1;

static uint8_t mode;
void set_mode(uint8_t to_mode) {
	mode = to_mode;
	drive();
}
void drive_override() {
	if (joystick_x_calib == -1) {
		joystick_y_calib = ADC1->JDR1;
		joystick_x_calib = ADC1->JDR2;
	}

	uint32_t joystick_y = ADC1->JDR1;
	uint32_t joystick_x = ADC1->JDR2;

	if (joystick_y < 4096 / 3) {
		set_led_direction(LED_LEFT);
	} else if (joystick_y > 8192 / 3) {
		set_led_direction(LED_RIGHT);
	} else if (joystick_x < 4096 / 3) {
		set_led_direction(LED_FORWARD);
	} else if (joystick_x > 8192 / 3) {
		set_led_direction(LED_BACK);
	} else {
		set_led_direction(LED_STOP);
	}

	set_speed(joystick_x - joystick_x_calib);
	set_direction(joystick_y - joystick_y_calib);
}
void drive_hard_stop() {
	stop();
	set_led_direction(LED_STOP);
	uint32_t joystick_y = ADC1->JDR1;
	uint32_t joystick_x = ADC1->JDR2;

	if ((joystick_y > joystick_y_calib - 100)
			&& (joystick_y < joystick_y_calib + 100)
			&& (joystick_x > joystick_x_calib - 100)
			&& (joystick_x < joystick_x_calib + 100)

			) {
		set_mode(MANUAL_OVERRIDE);
		enable();
	}
}
void drive_manual() {
	if (1) { //check distance here
		drive_override();
	} else {
		drive_hard_stop();
		set_mode(HARD_STOP);
	}

}
void drive() {
	switch (mode) {
	case MANUAL:
		drive_manual();
		break;
	case MANUAL_OVERRIDE:
		drive_override();
		break;
	case HARD_STOP:
		drive_hard_stop();
		break;
	}
}
