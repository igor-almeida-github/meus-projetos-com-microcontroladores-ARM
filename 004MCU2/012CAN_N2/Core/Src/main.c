/*
 * main.c
 *
 *  Created on: Jul 6, 2021
 *      Author: igor
 * N1 sends a message(led number) using Data Frame for every 1sec to N2
 * After the reception of message(led number) N2 has to glow the corresponding LED
 * N1 also sends a Remote frame to request 2 bytes of data for every 4secs
 * N2 upon receiving the Remote frame should send back 2 bytes of data using Data Frame
 * Use Interrupt driven Code
 */

#include "stm32f4xx_hal.h"
#include "main.h"
#include <stdio.h>
#include <string.h>



/************************************************************************************
 *                           GLOBAL VARIABLES                                       *
 ************************************************************************************/

CAN_HandleTypeDef hcan1;

/************************************************************************************
 *                             MAIN                                                 *
 ************************************************************************************/

int main(void){

	// Local variables


	// This should be the first function to be called
	HAL_Init();

	// Config. the clock
	SystemClock_Config_HSE(SYS_CLOCK_FREQ_84_MHZ);

	// Init. CAN1 peripheral
	CAN1_Init();

	// Filter config.
	CAN_Filter_Config();

	// Enable interrupt from the CAN peripheral side
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_TX_MAILBOX_EMPTY | CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_BUSOFF);

	// Move CAN from init. mode to normal mode
	HAL_CAN_Start(&hcan1);

	// Start the LEDs GPIOs
	GPIO_Init();


	for(;;){

	}
}

/************************************************************************************
 *                             FUNCTIONS                                            *
 ************************************************************************************/


void Error_handler(void){
	while(1);
}


void CAN1_Init(void){
	hcan1.Instance = CAN1;
	hcan1.Init.Mode = CAN_MODE_NORMAL;
	hcan1.Init.AutoBusOff = DISABLE;
	hcan1.Init.AutoRetransmission = ENABLE;
	hcan1.Init.AutoWakeUp = DISABLE;
	hcan1.Init.ReceiveFifoLocked = DISABLE;
	hcan1.Init.TimeTriggeredMode = DISABLE;
	hcan1.Init.TransmitFifoPriority = DISABLE;

	// CAN timings settings (1 Mbps)
	hcan1.Init.Prescaler = 3;
	hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan1.Init.TimeSeg1 = CAN_BS1_11TQ;
	hcan1.Init.TimeSeg2 = CAN_BS2_2TQ;

	// Do the Init. in the initialization mode
	if(HAL_CAN_Init(&hcan1) != HAL_OK)
		Error_handler();
}

void CAN_Filter_Config(void){
	CAN_FilterTypeDef can1_filter_init;

	// Filter accept all messages
	can1_filter_init.FilterActivation = ENABLE;
	can1_filter_init.FilterBank = 0;
	can1_filter_init.FilterFIFOAssignment = CAN_RX_FIFO0;
	can1_filter_init.FilterIdHigh = 0x0000;
	can1_filter_init.FilterIdLow = 0x0000;
	can1_filter_init.FilterMaskIdHigh = 0x0000;
	can1_filter_init.FilterMaskIdLow = 0x0000;
	can1_filter_init.FilterMode = CAN_FILTERMODE_IDMASK;
	can1_filter_init.FilterScale = CAN_FILTERSCALE_32BIT;

	if(HAL_CAN_ConfigFilter(&hcan1, &can1_filter_init) != HAL_OK)
		Error_handler();
}

void GPIO_Init(void){
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef ledgpios;
	ledgpios.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	ledgpios.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpios.Pull = GPIO_NOPULL;
	ledgpios.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOD, &ledgpios);

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

	if(RxHeader.StdId == 0x65D && RxHeader.RTR == CAN_RTR_DATA){
		// Data Frame received
		LED_Manage_Output(message[0]);
	}
	else if (RxHeader.StdId == 0x651 && RxHeader.RTR == CAN_RTR_REMOTE){
		// Remote Frame N1 to N2 (N1 is asking for data)
		Send_response();
	}
}


void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *hcan){

}

void Send_response(void){
	// Send two bytes of data back to node 1
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t TxMailbox;
	uint8_t msg[2] = {0x98, 0x99};

	TxHeader.DLC = 2;
	TxHeader.StdId = 0x651;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;

	if(HAL_CAN_AddTxMessage(&hcan1, &TxHeader, msg, &TxMailbox) != HAL_OK){
		Error_handler();
	}

}

void LED_Manage_Output(uint8_t led_no){
	switch(led_no){
		case 0:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_RESET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
			break;
	}
}


void SystemClock_Config_HSE(uint8_t clock_freq){
	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;
	uint32_t FLatency;

	// 1. Init. the oscillator
	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	osc_init.HSEState = RCC_HSE_ON;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	osc_init.PLL.PLLQ = 2;

	// 2. Init. the clock
	clk_init.ClockType = RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK |\
			 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	clk_init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	clk_init.AHBCLKDivider = RCC_SYSCLK_DIV1;
	clk_init.APB1CLKDivider = RCC_HCLK_DIV2;
	clk_init.APB2CLKDivider = RCC_HCLK_DIV2;

	// 3. Configurations that depend on clock_freq
	switch(clock_freq){
		case SYS_CLOCK_FREQ_50_MHZ:
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 100;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			FLatency = FLASH_LATENCY_1;
			break;
		case SYS_CLOCK_FREQ_84_MHZ:
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 168;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			FLatency = FLASH_LATENCY_2;
			break;
		case SYS_CLOCK_FREQ_120_MHZ:
			osc_init.PLL.PLLM = 8;
			osc_init.PLL.PLLN = 240;
			osc_init.PLL.PLLP = RCC_PLLP_DIV2;
			clk_init.APB1CLKDivider = RCC_HCLK_DIV4;
			FLatency = FLASH_LATENCY_3;
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
