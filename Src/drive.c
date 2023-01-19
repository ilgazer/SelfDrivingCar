#include "drive.h"

#include <math.h>

#include "board/adc.h"
#include "leds.h"
#include "motors.h"
#include "ultrasonic.h"
#include "indicators.h"
#include "analog_sensors.h"

static uint8_t mode;

uint8_t get_mode()
{
	return mode;
}
void init_drive(uint8_t to_mode)
{
	mode = to_mode;
}
void set_state(uint8_t to_mode)
{
	mode = to_mode;
	drive();
}
void drive_manual()
{
	int speed = get_joystick_x();
	if (speed < 200 && speed > -200)
		speed = 0;
	int direction = get_joystick_y();
	if (direction < 200 && direction > -200)
		direction = 0;
	set_speed(speed * 2);
	set_direction(direction * 2);

	if (direction < -500)
	{
		set_led_direction(LED_RIGHT);
	}
	else if (500 < direction)
	{
		set_led_direction(LED_LEFT);
	}
	else if (speed < -500)
	{
		set_led_direction(LED_BACK);
	}
	else if (500 < speed)
	{
		set_led_direction(LED_FORWARD);
	}else{
		set_led_direction(LED_STOP);
	}
}
void drive_stop()
{
	set_led_direction(LED_STOP);
	stop();
}

void drive_auto()
{
	static const int LDR_SENSITIVITY = 1;
	int auto_direction = get_ldr_direction() * 4  - get_ldr_direction()*abs(get_ldr_direction())/900;
	if (auto_direction > 300)
	{
		set_direction(auto_direction  < -2000 ? -1800 : auto_direction*14/10 );
		set_led_direction(LED_LEFT);
	}
	else if (auto_direction < -300)
	{
		set_direction(auto_direction > 2000 ? 1800: auto_direction*14/10  );
		set_led_direction(LED_RIGHT);
	}
	else
	{
		set_direction(0);
		set_led_direction(LED_FORWARD);
	}
	set_speed(1700);
}
void auto_wait()
{
	refresh_ldr_calib();
	set_led_direction(LED_STOP);
	set_direction(0);
	set_speed(0);
	int x = get_joystick_x();
	if ((x) > 1500 && x > 0)
	{
		mode = AUTO;
		drive_auto();
	}
}
void auto_stop()
{
	set_led_direction(LED_STOP);
	stop();
}
void ultrasonic_stop()
{
	set_led_direction(LED_STOP);

	if (mode <= MANUAL_STOP)
	{
		mode = MANUAL_STOP;
	}
	else
	{
		mode = AUTO_STOP;
	}
}

void joystick_button_handler()
{
	if (mode == MANUAL_STOP)
	{
		set_state(MANUAL_OVERRIDE);
		enable();
	}
	else if (mode < MANUAL_STOP)
	{
		set_state(MANUAL_STOP);
	}
	else
	{
		set_state(AUTO_STOP);
	}
}

void blue_button_handler(){
	static int auto_mode = 0;
	enable();
	if (auto_mode) {
		auto_mode = 0;
		set_state(MANUAL);
	} else {
		init_drive(AUTO_WAIT);
		auto_mode = 1;
	}
}

void drive()
{
	static uint8_t disarm_manual_counter = 0;
	if ((get_distance() < 20) && (mode != MANUAL_OVERRIDE))
	{
		ultrasonic_stop();
	}
	else if ((get_distance() > 25) && (mode == MANUAL_OVERRIDE))
	{
		disarm_manual_counter += 1;
		if (disarm_manual_counter > 26)
		{
			mode = MANUAL;
			disarm_manual_counter = 0;
		}
	}
	set_indicators(mode);
	switch (mode)
	{
	case MANUAL:
		drive_manual();
		break;
	case MANUAL_OVERRIDE:
		drive_manual();
		break;
	case MANUAL_STOP:
		drive_stop();
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
