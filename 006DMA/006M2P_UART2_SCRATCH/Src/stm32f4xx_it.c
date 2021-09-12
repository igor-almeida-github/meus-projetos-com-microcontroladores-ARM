/*
 * stm32f4xxit.c
 *
 *  Created on: Aug 6, 2021
 *      Author: igor
 */

#include "stm32f407xx.h"

extern void enable_dma1_stream6(void);
extern void HT_Complete_callback(void);
extern void FT_Complete_callback(void);
extern void TE_Complete_callback(void);
extern void FE_Complete_callback(void);
extern void DME_Complete_callback(void);

#define is_it_HT()  (DMA1->HISR & (1 << 20))
#define is_it_FT()  (DMA1->HISR & (1 << 21))
#define is_it_TE()  (DMA1->HISR & (1 << 19))
#define is_it_FE()  (DMA1->HISR & (1 << 16))
#define is_it_DME() (DMA1->HISR & (1 << 18))


void clear_exti_pending_bit(){
	// Clear pending bit (according to the ref manual, we must set to clear)
	EXTI->PR |= (1 << EXTI_PR_PR0_Pos);
}

void EXTI0_IRQHandler(void){
	clear_exti_pending_bit();
	// Send UART request to DMA
	enable_dma1_stream6();
	USART2->CR3 |= (1 << USART_CR3_DMAT_Pos);
}

void DMA1_Stream6_IRQHandler(void){

	if(is_it_HT()){
		// Half-transfer
		DMA1->HIFCR |= (1 << 20);
		HT_Complete_callback();
	}else if(is_it_FT()){
		// Full-transfer
		DMA1->HIFCR |= (1 << 21);
		FT_Complete_callback();
	}else if(is_it_TE()){
		// Transfer error
		DMA1->HIFCR |= (1 << 19);
		TE_Complete_callback();
	}else if(is_it_FE()){
		// FIFO error
		DMA1->HIFCR |= (1 << 16);
		FE_Complete_callback();
	}else if(is_it_DME()){
		// Direct mode error
		DMA1->HIFCR |= (1 << 18);
		DME_Complete_callback();
	}
}






