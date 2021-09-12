/*
 * main.h
 *
 *  Created on: May 26, 2021
 *      Author: igor
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

/************************************************************************************
 *                           MACROS                                                 *
 ************************************************************************************/

#define SYS_CLOCK_FREQ_50_MHZ   50
#define SYS_CLOCK_FREQ_84_MHZ   84
#define SYS_CLOCK_FREQ_120_MHZ 120
#define SYS_CLOCK_FREQ_168_MHZ 168


/************************************************************************************
 *                           FUNC. PROT.                                            *
 ************************************************************************************/

void Error_handler(void);
void SystemClock_Config_HSE(uint8_t clock_freq);
void CAN1_Init(void);
void CAN1_Tx(void);
void CAN_Filter_Config(void);

#endif /* INC_MAIN_H_ */
