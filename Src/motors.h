/*
 * motors.h
 *
 *  Created on: Jan 6, 2023
 *      Author: Ilgaz
 */

#ifndef MOTORS_H_
#define MOTORS_H_

typedef struct {
	int speed;
	int direction;
	int is_stopped;
} MotorState_t;

void init_motors();

void set_speed(int speed);

void set_direction(int direction);

void stop();

void enable();

#endif /* MOTORS_H_ */
