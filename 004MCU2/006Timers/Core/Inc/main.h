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
void TIMER6_Init(void);
void LED_Init(void);
void SystemClock_Config(uint8_t clock_freq);

#endif /* INC_MAIN_H_ */
