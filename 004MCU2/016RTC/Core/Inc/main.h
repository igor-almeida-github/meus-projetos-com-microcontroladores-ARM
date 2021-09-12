

#ifndef INC_MAIN_H_
#define INC_MAIN_H_

/************************************************************************************
 *                           MACROS                                                 *
 ************************************************************************************/

#define SYS_CLOCK_FREQ_50_MHZ   50
#define SYS_CLOCK_FREQ_84_MHZ   84
#define SYS_CLOCK_FREQ_120_MHZ 120
#define SYS_CLOCK_FREQ_168_MHZ 168

#define BUTTON_PRESSED  1
#define BUTTON_PIN      GPIO_PIN_0

/************************************************************************************
 *                           FUNC. PROT.                                            *
 ************************************************************************************/

void Error_handler(void);
void SystemClock_Config_HSE(uint8_t clock_freq);
void Button_Init(void);
void UART2_Init(void);
void RTC_Init(void);
void RTC_CalendarConfig(void);
void printmsg(char *format,...);
char *getDayofweek(uint8_t number);
void RTC_AlarmConfig(void);

#endif /* INC_MAIN_H_ */
