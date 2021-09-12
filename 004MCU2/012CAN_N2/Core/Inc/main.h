

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
void CAN_Filter_Config(void);
void GPIO_Init(void);
void Send_response(void);
void LED_Manage_Output(uint8_t led_no);

#endif /* INC_MAIN_H_ */
