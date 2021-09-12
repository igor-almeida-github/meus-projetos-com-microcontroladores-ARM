/*
 * main.h
 *
 *  Created on: Jul 4, 2021
 *      Author: igor
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

#include "stm32f1xx.h"

/************************************************************************************
 *                           MACROS                                                 *
 ************************************************************************************/

#define SYS_CLOCK_FREQ_16_MHZ   16
#define SYS_CLOCK_FREQ_32_MHZ   32
#define SYS_CLOCK_FREQ_64_MHZ   64
#define SYS_CLOCK_FREQ_72_MHZ   72


/************************************************************************************
 *                           FUNC. PROT.                                            *
 ************************************************************************************/

void Error_handler(void);
void SystemClock_Config_HSE(uint8_t clock_freq);
void TIMER2_Init(void);
void CAN1_Init(void);
void CAN_Filter_Config(void);
void CAN1_Tx(void);

#endif /* INC_MAIN_H_ */
