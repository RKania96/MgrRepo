/*
 * mbdata.h
 *
 *  Created on: xx cze 2021
 *      Author: xx xx
 */

#ifndef MODBUS_INCLUDE_MBDATA_H_
#define MODBUS_INCLUDE_MBDATA_H_

#define NB_REG_INPUT_SIZE  25						///< Input register size
uint16_t MB_REG_INPUT_BUF[NB_REG_INPUT_SIZE];// = {10,11,12,13,14,15,16,17,18,19};		///< Input register

#define NB_REG_HOLD_SIZE  18						///< Keep register size
uint16_t MB_REG_HOLD_BUF[NB_REG_HOLD_SIZE];			///< Holding register

#endif /* MODBUS_INCLUDE_MBDATA_H_ */
