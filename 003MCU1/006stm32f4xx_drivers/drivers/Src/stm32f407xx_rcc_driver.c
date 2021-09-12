/*
 * stm32f407xx_rcc_driver.c
 *
 *  Created on: 21 de mai de 2021
 *      Author: igor
 */

#include "stm32f407xx.h"

uint16_t const AHB_PreScaler[8] = {2, 4, 8, 16, 128, 256, 512};
uint16_t const APB1_PreScaler[8] = {2, 4, 8, 16, 128, 256, 512};

uint32_t RCC_GetPCLK1Value(void){


	uint32_t pClk1;
	uint32_t ahbClk;
	uint32_t SystemClk;

	uint8_t rcc_cfgr_sws, rcc_cfgr_hpre, rcc_cfgr_ppre1;

	rcc_cfgr_sws = (RCC->CFGR >> 2) & 0x03;

	if(rcc_cfgr_sws == 0){
		SystemClk = 16000000;
	}else if(rcc_cfgr_sws == 1){
		SystemClk = 8000000;
	}else if(rcc_cfgr_sws == 2){
		SystemClk = RCC_GetPLLOutputClock();
	}

	rcc_cfgr_hpre = (RCC->CFGR >> 4) & 0x0F;

	if(rcc_cfgr_hpre < 8){
		ahbClk = SystemClk;
	}
	else{
		ahbClk = SystemClk / AHB_PreScaler[rcc_cfgr_hpre & 0x07];
	}

	rcc_cfgr_ppre1 = (RCC->CFGR >> 10) & 0x07;

	if(rcc_cfgr_hpre < 4){
		pClk1 = ahbClk;
	}
	else{
		pClk1 = ahbClk / APB1_PreScaler[rcc_cfgr_ppre1 & 0x03];
	}

	return pClk1;
}

uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t SystemClock=0,tmp,pclk2;
	uint8_t clk_src = ( RCC->CFGR >> 2) & 0X3;

	uint8_t ahbp,apb2p;

	if(clk_src == 0)
	{
		SystemClock = 16000000;
	}else
	{
		SystemClock = 8000000;
	}
	tmp = (RCC->CFGR >> 4 ) & 0xF;

	if(tmp < 0x08)
	{
		ahbp = 1;
	}else
	{
       ahbp = AHB_PreScaler[tmp-8];
	}

	tmp = (RCC->CFGR >> 13 ) & 0x7;
	if(tmp < 0x04)
	{
		apb2p = 1;
	}else
	{
		apb2p = APB1_PreScaler[tmp-4];
	}

	pclk2 = (SystemClock / ahbp )/ apb2p;

	return pclk2;
}



