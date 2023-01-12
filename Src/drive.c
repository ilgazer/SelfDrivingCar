#include "drive.h"

#include "board/adc.h"
#include "leds.h"
#include "motors.h"
#include "ultrasonic.h"

static uint16_t joystick_x_calib = 0;
static uint16_t joystick_y_calib = 0;
static uint16_t joystick_y = 0;
static uint16_t joystick_x = 0;

static uint8_t mode;

void init_mode(uint8_t to_mode) {
	mode = to_mode;
}
void set_mode(uint8_t to_mode) {
	mode = to_mode;
	drive();
}
void drive_override() {
	if (joystick_x_calib < 1000) {
		joystick_y_calib = ADC1->JDR1;
		joystick_x_calib = ADC1->JDR2;
	}
	if (joystick_y < 4096 / 3) {
		set_led_direction(LED_RIGHT);
	} else if (joystick_y > 8192 / 3) {
		set_led_direction(LED_LEFT);
	} else if (joystick_x < 4096 / 3) {
		set_led_direction(LED_FORWARD);
	} else if (joystick_x > 8192 / 3) {
		set_led_direction(LED_BACK);
	} else {
		set_led_direction(LED_STOP);
	}

	int speed = joystick_x_calib - joystick_x ;
	if (speed < 200 && speed > -200)
		speed = 0;
	int direction = joystick_y - joystick_y_calib;
	if(direction < 200 && direction > -200)
		direction = 0;
	set_speed( speed);
	set_direction(direction);
}
void drive_hard_stop() {
	stop();
	set_led_direction(LED_STOP);

//	if ((joystick_y > joystick_y_calib - 100)
//			&& (joystick_y < joystick_y_calib + 100)
//			&& (joystick_x > joystick_x_calib - 100)
//			&& (joystick_x < joystick_x_calib + 100)
//
//			) {
//		mode = (MANUAL_OVERRIDE);
//		enable();
//	}
}
void drive_manual() {
	if (1) { //check distance here
		drive_override();
	} else {
		drive_hard_stop();
		set_mode(HARD_STOP);
	}

}

static uint32_t LDR_right_calib = 0;
static uint32_t LDR_left_calib = 0;
static uint16_t LDR_right;
static uint16_t LDR_left;
static int auto_direction;
static
void drive_auto() {

	auto_direction = ((LDR_right- LDR_right_calib) - (LDR_left- LDR_left_calib)) * 5  ;
	if (auto_direction < -500) {
		set_direction(auto_direction > -1500 ? auto_direction : -1500);
		set_led_direction(LED_RIGHT);
	} else if (auto_direction > 500) {
		set_direction(auto_direction < 1500 ? auto_direction : 1500);
		set_led_direction(LED_LEFT);
	} else {
		set_direction(0);
		set_led_direction(LED_FORWARD);
	}
	set_speed(2000);

}
void auto_wait(){
	if (joystick_x_calib < 1000) {
		joystick_y_calib = ADC1->JDR1;
		joystick_x_calib = ADC1->JDR2;
	}
	if (LDR_left_calib == 0) {
		LDR_right_calib = ADC1->JDR3;
		LDR_left_calib = ADC1->JDR4;
	}
	set_led_direction(LED_STOP);
	set_direction(0);
	set_speed(0);
	if (joystick_x < 4096 / 3) {
		mode = AUTO;
		drive_auto();
	}
}
void auto_stop(){
	set_led_direction(LED_STOP);
	stop();
	mode = AUTO_STOP;
}
void driver_stop() {
	set_led_direction(LED_STOP);

	if(mode <= HARD_STOP){
		mode = HARD_STOP;
	}else{
		mode = AUTO_STOP;
	}
}
void joystick_button_handler(){
	if(mode <= HARD_STOP){
		set_mode(HARD_STOP);
		enable();
	}else{
		set_mode(AUTO_STOP);
	}
}

void drive() {
	LDR_right = ADC1->JDR3 ;
	LDR_left = ADC1->JDR4 ;
	joystick_y = ADC1->JDR1;
	joystick_x = ADC1->JDR2;
	static uint8_t disarm_manual_counter = 0;
	if((get_distance() < 12) && (mode != MANUAL_OVERRIDE)){
		driver_stop();
	}else if((get_distance() > 12) && (mode == MANUAL_OVERRIDE)){
		disarm_manual_counter += 1;
		if(disarm_manual_counter > 4){
			mode = MANUAL;
			disarm_manual_counter = 0;
		}
	}
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

