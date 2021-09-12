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

#define BUTTON_PIN   GPIO_PIN_0


/************************************************************************************
 *                           FUNC. PROT.                                            *
 ************************************************************************************/

void Error_handler(void);
void SystemClock_Config_HSE(uint8_t clock_freq);
void UART2_Init(void);
void Button_Init(void);
void save_message_backup(uint8_t *message, uint8_t len);
void get_message_backup(uint8_t *recovered_message, uint8_t len);

#endif /* INC_MAIN_H_ */
