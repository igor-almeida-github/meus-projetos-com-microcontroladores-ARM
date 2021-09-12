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

#define CAPTURE_BUFFER_EMPTY 0
#define CAPTURE_BUFFER_FULL  2

#define TRUE  1
#define FALSE 0


/************************************************************************************
 *                           FUNC. PROT.                                            *
 ************************************************************************************/

void Error_handler(void);
void LED_Init(void);
void SystemClock_Config(uint8_t clock_freq);
void SystemClock_Config_HSE(uint8_t clock_freq);
void TIMER2_Init(void);
void LSE_Configuration(void);

#endif /* INC_MAIN_H_ */
