/*
 * utils.h
 *
 *  Created on: Jan 6, 2023
 *      Author: Ilgaz
 */

#ifndef UTILS_H_
#define UTILS_H_

#define SET(REG, OFFSET) (REG) |= (1 << (OFFSET))
#define SET_BITS(REG, OFFSET, VAL, BITS) (REG) &= ~(((1 << BITS) - 1) << (OFFSET)); (REG) |= (VAL << (OFFSET))
#define RESET(REG, OFFSET) (REG) &= ~(1 << (OFFSET))
#define GET(REG, OFFSET) ((REG) | (1 << (OFFSET)))


#endif /* UTILS_H_ */
