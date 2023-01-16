#ifndef _ANALOG_SENSORS_H
#define _ANALOG_SENSORS_H

void initialize_sensors();
void refresh_sensors();
void refresh_ldr_calib();
uint16_t get_joystick_x();
uint16_t get_joystick_y();
uint16_t get_ldr_direction();


#endif