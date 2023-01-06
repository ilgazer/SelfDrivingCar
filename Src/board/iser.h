/*
 * iser.h
 *
 *  Created on: Jan 6, 2023
 *      Author: Ilgaz
 */

#ifndef ISER_H_
#define ISER_H_

#include "../utils.h"

#define ISER1 *((volatile uint32_t *) (0xE000E100 + 4))
#define ISER2 *((volatile uint32_t *) (0xE000E100 + 8))

#define SET_ISER(INT) SET(*((volatile uint32_t *) (0xE000E100 + ((INT) / 32))), INT % 32)

#endif /* ISER_H_ */
