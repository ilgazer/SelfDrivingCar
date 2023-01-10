#include "drive.h"

#include "board/adc.h"
#include "leds.h"
#include "motors.h"

int joystick_x_calib = -1;
int joystick_y_calib = -1;

static uint8_t mode;

void init_mode(uint8_t to_mode) {
	mode = to_mode;
}
void set_mode(uint8_t to_mode) {
	mode = to_mode;
	drive();
}
static uint32_t joystick_x;
static uint32_t joystick_y;
void drive_override() {
	if (joystick_x_calib == -1) {
		joystick_y_calib = ADC1->JDR1;
		joystick_x_calib = ADC1->JDR2;
	}

	joystick_y = ADC1->JDR1;
	joystick_x = ADC1->JDR2;

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

	set_speed(joystick_x_calib - joystick_x);
	set_direction(joystick_y_calib - joystick_y);
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

static uint32_t LDR_right_calib = -1;
static uint32_t LDR_left_calib = -1;
void drive_auto() {
	uint32_t LDR_right = ADC1->JDR3 - LDR_right_calib;
	uint32_t LDR_left = ADC1->JDR4 - LDR_left_calib;

	int direction = (LDR_right - LDR_left) * 10;
	if (direction < -500) {
		set_direction(direction > -1500 ? direction : -1500);
		set_led_direction(LED_RIGHT);
	} else if (direction > 500) {
		set_direction(direction < 1500 ? direction : 1500);
		set_led_direction(LED_LEFT);
	} else {
		set_direction(0);
		set_led_direction(LED_FORWARD);
	}
	set_speed(2000);

}
void auto_wait() {
	if (joystick_x_calib == -1) {
		joystick_y_calib = ADC1->JDR1;
		joystick_x_calib = ADC1->JDR2;
	}
	if (LDR_left_calib == -1) {
		LDR_right_calib = ADC1->JDR3;
		LDR_left_calib = ADC1->JDR4;
	}
	uint32_t joystick_x = ADC1->JDR2;
	set_led_direction(LED_STOP);
	set_direction(0);
	set_speed(0);
	if (joystick_x < 4096 / 3) {
		mode = AUTO;
		drive_auto();
	}
}
void auto_stop() {
	stop();
	mode = AUTO_STOP;
}
void driver_stop() {
	set_led_direction(LED_STOP);
	if (mode <= HARD_STOP) {
		drive_hard_stop();
	} else {
		auto_stop();
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
	case AUTO:
		drive_auto();
		break;
	case AUTO_WAIT:
		auto_wait();
		break;
	case AUTO_STOP:
		auto_stop();
		break;
	}
}

