/*
 * stm32f407xx_spi_driver.c
 *
 *  Created on: 3 de mai de 2021
 *      Author: igor
 */

#include "stm32f407xx.h"

static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle);

// Peripheral clock setup
void SPI_PeriClockControl(SPI_RegDef_t *pSPIx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
			if(pSPIx == SPI1)
				SPI1_PCLK_EN();
			else if(pSPIx == SPI2)
				SPI2_PCLK_EN();
			else if(pSPIx == SPI3)
				SPI3_PCLK_EN();
		}
		else{
			if(pSPIx == SPI1)
				SPI1_PCLK_DI();
			else if(pSPIx == SPI2)
				SPI2_PCLK_DI();
			else if(pSPIx == SPI3)
				SPI3_PCLK_DI();
		}
}

// Init and De-init
void SPI_Init(SPI_Handle_t *pSPIHandle){
	uint32_t tempreg =0;

	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);

	// 1. Configure the device mode
	tempreg |= pSPIHandle->SPIConfig.SPI_DeviceMode << SPI_CR1_MSTR;

	// 2. Configure the bus config
	if(pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_FD){
		// Nothing to do
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_HD){
		tempreg |= 1 << 15;
	}else if (pSPIHandle->SPIConfig.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY){
		tempreg |= 1 << 10;
	}

	// 3. Configure the spi clock speed
	tempreg |= pSPIHandle->SPIConfig.SPI_SclkSpeed << SPI_CR1_BR;

	// 4. Configure the DFF
	tempreg |= pSPIHandle->SPIConfig.SPI_DFF << SPI_CR1_DFF;

	// 5. Configure the CPOL
	tempreg |= pSPIHandle->SPIConfig.SPI_CPOL << SPI_CR1_CPOL;

	// 6. Configure the CPHA
	tempreg |= pSPIHandle->SPIConfig.SPI_CPHA << SPI_CR1_CPHA;

	// 7. Configure the SSM
	tempreg |= pSPIHandle->SPIConfig.SPI_SSM << SPI_CR1_SSM;

	// Saving tempreg to CR1
	pSPIHandle->pSPIx->CR1 = tempreg;

}
void SPI_DeInit(SPI_RegDef_t *pSPIx){

}

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName){
	if(pSPIx->SR & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

// Data send and receive (blocking call)
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len){
	while(Len > 0){
		// 1. Wait until TXE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET);

		// 2. Check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF)){
			// 16 bit DFF
			pSPIx->DR = *((uint16_t *)pTxBuffer);
			Len -= 2;
			(uint16_t *)pTxBuffer++;
		}else{
			// 8 bit DFF
			pSPIx->DR = *pTxBuffer;
			Len--;
			pTxBuffer++;
		}
	}
}
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){
	while(Len > 0){
		// 1. Wait until RXNE is set
		while(SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET);

		// 2. Check the DFF bit in CR1
		if(pSPIx->CR1 & (1 << SPI_CR1_DFF)){
			// 16 bit DFF
			*((uint16_t *)pRxBuffer) = pSPIx->DR;
			Len -= 2;
			(uint16_t *)pRxBuffer++;
		}else{
			// 8 bit DFF
			*pRxBuffer = pSPIx->DR;
			Len--;
			pRxBuffer++;
		}
	}
}

// Send and receive (interrupt based)

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pTxBuffer, uint32_t Len){

	uint8_t state = pSPIHandle->TxState;

	if(state != SPI_BUSY_IN_TX){
		// 1. Save the Tx buffer address and Len information in some global variables.
		pSPIHandle->pTxBuffer = pTxBuffer;
		pSPIHandle->TxLen = Len;
		// 2. Mark the SPI state as busy in transmission so that no other code can
		//    take over same SPI peripheral until transmission is over.
		pSPIHandle->TxState = SPI_BUSY_IN_TX;
		// 3. Enable the TXEIE control bit to get interrupt whenever TXE flag is
		//    set in SR.
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
		// 4. Data transmission will be handled by the ISR code ( will implement later ).
	}

	return state;
}
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len){

	uint8_t state = pSPIHandle->RxState;

	if(state != SPI_BUSY_IN_RX){
		// 1. Save the Tx buffer address and Len information in some global variables.
		pSPIHandle->pRxBuffer = pRxBuffer;
		pSPIHandle->RxLen = Len;
		// 2. Mark the SPI state as busy in transmission so that no other code can
		//    take over same SPI peripheral until transmission is over.
		pSPIHandle->RxState = SPI_BUSY_IN_RX;
		// 3. Enable the RXEIE control bit to get interrupt whenever RXE flag is
		//    set in SR.
		pSPIHandle->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
		// 4. Data transmission will be handled by the ISR code ( will implement later ).
	}
	return state;
}

// IRQ Configuration and ISR handling
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE)
	{
		if(IRQNumber <= 31)
		{
			//program ISER0 register
			*NVIC_ISER0 |= ( 1 << IRQNumber );

		}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
		{
			//program ISER1 register
			*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 64 && IRQNumber < 96 )
		{
			//program ISER2 register //64 to 95
			*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
		}
	}else
	{
		if(IRQNumber <= 31)
		{
			//program ICER0 register
			*NVIC_ICER0 |= ( 1 << IRQNumber );
		}else if(IRQNumber > 31 && IRQNumber < 64 )
		{
			//program ICER1 register
			*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
		}
		else if(IRQNumber >= 6 && IRQNumber < 96 )
		{
			//program ICER2 register
			*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
		}
	}
}
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority){

}
void SPI_IRQHandling(SPI_Handle_t *pHandle){


	// Checking if interrupt happened because of transmission buffer empty
	uint8_t txe_flag = pHandle->pSPIx->SR & (1 << SPI_SR_TXE); // tx empty
	uint8_t txeie = pHandle->pSPIx->CR2 & (1 << SPI_CR2_TXEIE);  // tx interrupt enable
	if(txeie && txe_flag){
		spi_txe_interrupt_handle(pHandle);
	}

	// Checking if interrupt happened because of reception buffer full
	uint8_t rxne_flag = pHandle->pSPIx->SR & (1 << SPI_SR_RXNE); // rx not empty
	uint8_t rxneie = pHandle->pSPIx->CR2 & (1 << SPI_CR2_RXNEIE);  // rx interrupt enable
	if(rxneie && rxne_flag){
		spi_rxne_interrupt_handle(pHandle);
	}

	// Checking if interrupt happened because of overun (reception of a new data frame while the old one hasn't been read yet)
	uint8_t ovr_flag = pHandle->pSPIx->SR & (1 << SPI_SR_OVR);
	uint8_t errie = pHandle->pSPIx->CR2 & (1 << SPI_CR2_ERRIE);
	if(errie && ovr_flag){
		spi_ovr_err_interrupt_handle(pHandle);
	}
}

// Enable or disable peripheral
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SPE);
	}else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

// SSI
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pSPIx->CR1 |= (1 << SPI_CR1_SSI);
	}else{
		pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

// SSOE
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
	}else{
		pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}

// Helper functions implementation
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle){

	// Check the DFF bit in CR1
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF)){
		// 16 bit DFF
		pSPIHandle->pSPIx->DR = *((uint16_t *)pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen -= 2;
		(uint16_t *)pSPIHandle->pTxBuffer++;
	}else{
		// 8 bit DFF
		pSPIHandle->pSPIx->DR = *(pSPIHandle->pTxBuffer);
		pSPIHandle->TxLen--;
		pSPIHandle->pTxBuffer++;
	}

	// Check if transmission has ended
	if(pSPIHandle->TxLen == 0){
		SPI_CloseTransmission(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_TX_CMPLT);
	}

}
static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle){

	// Check the DFF bit in CR1
	if(pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF)){
		// 16 bit DFF
		*((uint16_t *)pSPIHandle->pRxBuffer) = (uint16_t)pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen -= 2;
		(uint16_t *)pSPIHandle->pRxBuffer++;
	}else{
		// 8 bit DFF
		*(pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
		pSPIHandle->RxLen--;
		pSPIHandle->pRxBuffer++;
	}

	// Check if reception has ended
	if(pSPIHandle->RxLen == 0){
		SPI_CloseReception(pSPIHandle);
		SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_RX_CMPLT);
	}

}
static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle){

	// 1. clear the ovr flag
	if(pSPIHandle->TxState != SPI_BUSY_IN_TX){
		pSPIHandle->pSPIx->DR;
		pSPIHandle->pSPIx->SR;
	}
	// 2. inform the application
	SPI_ApplicationEventCallback(pSPIHandle, SPI_EVENT_OVR_ERR);

}

void SPI_ClearOVRFlag(SPI_RegDef_t *pSPIx){
	pSPIx->DR;
	pSPIx->SR;
}

// Close transmission and recepetion
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle){
	pSPIHandle->TxState = SPI_READY;
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);  // Disable transmission interrupt
	pSPIHandle->TxLen = 0;
}

void SPI_CloseReception(SPI_Handle_t *pSPIHandle){
	pSPIHandle->RxState = SPI_READY;
	pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);  // Disable reception interrupt
	pSPIHandle->RxLen = 0;
}

// weak implementations
__weak void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEv){
	// Application may implement this callback
}


