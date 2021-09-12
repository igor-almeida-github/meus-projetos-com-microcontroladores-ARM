/*
 * main.c
 *
 *  Created on: Jul 4, 2021
 *      Author: igor
 *
 * N1 sends a message(led number) using Data Frame for every 1sec to N2
 * After the reception of message(led number) N2 has to glow the corresponding LED
 * N1 also sends a Remote frame to request 2 bytes of data for every 4secs
 * N2 upon receiving the Remote frame should send back 2 bytes of data using Data Frame
 * Use Interrupt driven Code
 *
 * THIS CODE RUNS ON STM32F103C8
 *
 */

#include "main.h"

/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/

TIM_HandleTypeDef timer2_handle;
CAN_HandleTypeDef hcan1;

/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/
int main(void){

	// Local variables

	// This should be the first function to be called
	HAL_Init();

	// Config. the clock
	SystemClock_Config_HSE(SYS_CLOCK_FREQ_72_MHZ);

	// Init. CAN1 peripheral
	CAN1_Init();

	// Filter config.
	CAN_Filter_Config();

	// Enable interrupt from the CAN peripheral side
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_BUSOFF);

	// Move CAN from init. mode to normal mode
	if(HAL_CAN_Start(&hcan1) != HAL_OK){
		Error_handler();
	}

	// Init Timer 2
	TIMER2_Init();

	// Start timer
	HAL_TIM_Base_Start_IT(&timer2_handle);

	for(;;);
}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	CAN1_Tx();
}

void CAN1_Init(void){
	hcan1.Instance = CAN1;
	hcan1.Init.Mode = CAN_MODE_NORMAL;
	hcan1.Init.AutoBusOff = DISABLE;
	hcan1.Init.AutoRetransmission = ENABLE;
	hcan1.Init.AutoWakeUp = DISABLE;
	hcan1.Init.ReceiveFifoLocked = DISABLE;
	hcan1.Init.TimeTriggeredMode = DISABLE;
	hcan1.Init.TransmitFifoPriority = DISABLE;  // Priority driven by the identifier of the message

	// CAN timings settings (1 Mbps)
	hcan1.Init.Prescaler = 2;
	hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan1.Init.TimeSeg1 = CAN_BS1_15TQ;
	hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;

	// Do the Init. in the initialization mode
	if(HAL_CAN_Init(&hcan1) != HAL_OK)
		Error_handler();
}

void CAN_Filter_Config(void){
	CAN_FilterTypeDef can1_filter_init;

	// The filter tells which messages will pass (if they match the filter ID at the bit positions where mask = 1
	// Configure filter receive 0x651 messages and discard 0x65D so that it won't receive It's own transmitted messages
	can1_filter_init.FilterActivation = ENABLE;
	can1_filter_init.FilterBank = 0;
	can1_filter_init.FilterFIFOAssignment = CAN_RX_FIFO0;
	can1_filter_init.FilterIdHigh = 0x0000;
	can1_filter_init.FilterIdLow = 0x0000;
	can1_filter_init.FilterMaskIdHigh = 0x01C0;
	can1_filter_init.FilterMaskIdLow = 0x0000;
	can1_filter_init.FilterMode = CAN_FILTERMODE_IDMASK;
	can1_filter_init.FilterScale = CAN_FILTERSCALE_32BIT;

	if(HAL_CAN_ConfigFilter(&hcan1, &can1_filter_init) != HAL_OK)
		Error_handler();
}

void CAN1_Tx(void){
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t TxMailbox;
	static uint8_t led_no = 0;

	TxHeader.DLC = 1;
	TxHeader.StdId = 0x65D;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;

	led_no++;
	led_no %= 4;

	if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, &led_no, &TxMailbox) != HAL_OK){
		Error_handler();
	}

	if (led_no == 3){
		// Send remote frame every 4s

		TxHeader.DLC = 2;                // N1 demanding 2 bytes of reply
		TxHeader.StdId = 0x651;
		TxHeader.IDE = CAN_ID_STD;
		TxHeader.RTR = CAN_RTR_REMOTE;

		// led_no doesn't matter because in remote frame, no message is sent
		if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, &led_no, &TxMailbox) != HAL_OK){
			Error_handler();
		}

	}

}

void HAL_CAN_TxMailbox0CompleteCallback(CAN_HandleTypeDef *hcan){

}


void HAL_CAN_TxMailbox1CompleteCallback(CAN_HandleTypeDef *hcan){

}


void HAL_CAN_TxMailbox2CompleteCallback(CAN_HandleTypeDef *hcan){

}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	CAN_RxHeaderTypeDef RxHeader;
	uint8_t message[5];

	// Read the FIFO to receive the message
	if(HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &RxHeader, message) != HAL_OK)
		Error_handler();

	if (RxHeader.StdId == 0x651 && RxHeader.RTR == CAN_RTR_DATA){
		// Data frame N2 reply to N1

	}
}


void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan){

}

void TIMER2_Init(void){

	// 1. Initialize the TIMER2 time base (1s)
	timer2_handle.Instance = TIM2;
	timer2_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	timer2_handle.Init.Period = 10000 - 1;
	timer2_handle.Init.Prescaler = 7200 - 1;

	if(HAL_TIM_Base_Init(&timer2_handle) != HAL_OK)
		Error_handler();

}

void SystemClock_Config_HSE(uint8_t clock_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t FLatency;

	// 1. Init. the oscillator
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.LSEState = RCC_LSE_OFF;
	osc_init.LSIState = RCC_LSI_OFF;
	osc_init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	// 2. Init. the clock
	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |\
			 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV1;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV1;

	// 3. Configurations that depend on clock_freq
	switch(clock_freq){
		case SYS_CLOCK_FREQ_16_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL2;
			FLatency = FLASH_LATENCY_0;
			break;
		case SYS_CLOCK_FREQ_32_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL4;
			FLatency = FLASH_LATENCY_1;
			break;
		case SYS_CLOCK_FREQ_64_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL8;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			FLatency = FLASH_LATENCY_2;
			break;
		case SYS_CLOCK_FREQ_72_MHZ:
			osc_init.PLL.PLLMUL = RCC_PLL_MUL9;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
			FLatency = FLASH_LATENCY_2;
			break;
		default:
			return;
	}

	// 4. Call the APIs
	if(HAL_RCC_OscConfig(&osc_init) != HAL_OK)
		Error_handler();
	if(HAL_RCC_ClockConfig(&clk_init, FLatency) != HAL_OK)
		Error_handler();

	// 5. Systick
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

}

void Error_handler(void){
	while(1);
}
