/*
 * stm32f407xx_i2c_driver.c
 *
 *  Created on: 11 de mai de 2021
 *      Author: igor
 */

#include "stm32f407xx.h"

// ******************************* Private Helper functions **************************************

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= 1 << I2C_CR1_START;
}

static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr, uint8_t ReadOrWrite){
	pI2Cx->DR = (SlaveAddr << 1) | ReadOrWrite;
}


static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx){
	uint32_t dummyRead = pI2Cx->SR1;
	dummyRead = pI2Cx->SR2;
	(void)dummyRead;
}

static void I2C_ClearSTOPFFlag(I2C_RegDef_t *pI2Cx){
	// Read SR1 and Write to CR1
	uint32_t dummyRead = pI2Cx->SR1;
	pI2Cx->CR1 |= 0x00;
	(void)dummyRead;
}

// ************************ API ****************************************************

uint32_t RCC_GetPLLOutputClock(void){
	// To be done
	return 0;
}

void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx){
	pI2Cx->CR1 |= 1 << I2C_CR1_STOP;
}



uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName){
	if(pI2Cx->SR1 & FlagName){
		return FLAG_SET;
	}
	return FLAG_RESET;
}

void I2C_ManageAcking(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi){
	if(EnOrDi == I2C_ACK_ENABLE)
		pI2Cx->CR1 |= (1 << I2C_CR1_ACK);
	else{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_ACK);
	}
}


// Peripheral Enable/Disable
void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnOrDi){
	if(EnOrDi == ENABLE){
		pI2Cx->CR1 |= (1 << I2C_CR1_PE);
	}
	else{
		pI2Cx->CR1 &= ~(1 << I2C_CR1_PE);
	}
}

// Peripheral clock setup
void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pI2Cx == I2C1){
			I2C1_PCLK_EN();
		}
		else if(pI2Cx == I2C2){
			I2C2_PCLK_EN();
		}
		else if(pI2Cx == I2C3){
			I2C3_PCLK_EN();
		}
	}
	else{
		if(pI2Cx == I2C1){
			I2C1_PCLK_DI();
		}
		else if(pI2Cx == I2C2){
			I2C2_PCLK_DI();
		}
		else if(pI2Cx == I2C3){
			I2C3_PCLK_DI();
		}
	}
}

// Init and De-init
void I2C_Init(I2C_Handle_t *pI2CHandle){

	// Enable the clock
	I2C_PeriClockControl(pI2CHandle->pI2Cx, ENABLE);

	// Peripheral clock frequency - Freq field of CR2
	uint32_t tempreg = RCC_GetPCLK1Value()/1000000;
	pI2CHandle->pI2Cx->CR2 = tempreg;

	// Device own address
	tempreg = pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	tempreg |= 1 << 14;  // Manual says bit 14 must be kept at 1
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	// CCR calculations
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){
		// standard mode
		ccr_value = RCC_GetPCLK1Value() / (2 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		tempreg |= ccr_value & 0xFFF;
	}
	else{
		// fast mode
		tempreg |= (1 << 15);  // Fast mode configure
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14);  // Fm mode duty cycle
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2){
			ccr_value = RCC_GetPCLK1Value() / (3 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}
		else{
			ccr_value = RCC_GetPCLK1Value() / (25 * pI2CHandle->I2C_Config.I2C_SCLSpeed);
		}
		tempreg |= ccr_value & 0xFFF;
	}
	pI2CHandle->pI2Cx->CCR = tempreg;

	// TRISE Configuration
	uint8_t trise;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCL_SPEED_SM){
		// standard mode
		trise = (RCC_GetPCLK1Value() / 1000000) + 1;
	}
	else{
		// fast mode
		trise = (RCC_GetPCLK1Value() * 3 / 10000000) + 1;
	}
	pI2CHandle->pI2Cx->TRISE = (trise & 0x3F);
}

void I2C_DeInit(I2C_RegDef_t *pI2Cx){

}

// Send and receive data
void I2C_MasterSendData(I2C_RegDef_t *pI2Cx, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr){
	//1. Generate the START condition
	I2C_GenerateStartCondition(pI2Cx);

	//2. Confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled low)
	while(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_SB) == 0);

	//3. Send the address of the slave with r/nw bit set to w(0) (total 8 bits)
	I2C_ExecuteAddressPhase(pI2Cx, SlaveAddr, I2C_WRITE);

	//4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_ADDR) == 0);

	//5. Clear the ADDR flag according to its software sequence
	//   Note: Until ADDR is cleared SCL will be streched (pulled low)
	I2C_ClearADDRFlag(pI2Cx);

	//6. Send the data until Len becomes 0
	for(; Len>0; Len--){
		while(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_TXE) == 0);  // Wait until TXE is set
		pI2Cx->DR = *(pTxBuffer++);
	}

	//7. when Len becomes zero wait for TXE=1 and BTF=1 before generating the STOP condition
	//   Note: TXE=1, BTF=1, means that both SR and DR are empty and next transmission should begin
	//   when BTF=1 SCL will be streched (pulled to LOW)
	while(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_TXE) == 0);  // Wait until TXE is set
	while(I2C_GetFlagStatus(pI2Cx, I2C_FLAG_BTF) == 0);  // Wait until BTF is set

	//8. Generate STOP condition and master need not to wait for the completion of stop condition.
	//   Note: generating STOP, automatically clears the BTF
	if(Sr == I2C_DISABLE_SR)
		I2C_GenerateStopCondition(pI2Cx);
}

void I2C_MasterRecieveData(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr){
	//1. Generate the START condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//2. Confirm that start generation is completed by checking the SB flag in the SR1
	//   Note: Until SB is cleared SCL will be stretched (pulled low)
	while(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_SB) == 0);

	//3. Send the address of the slave with r/nw bit set to r(1) (total 8 bits)
	I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, SlaveAddr, I2C_READ);

	//4. Confirm that address phase is completed by checking the ADDR flag in the SR1
	while(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_ADDR) == 0);

	//5. Clear the ADDR flag according to its software sequence
	//   Note: Until ADDR is cleared SCL will be streched (pulled low)

	I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

	//5. Read Data
	while(Len > 0){

		if(Len == 1){
			// Disable Acking
			I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
			// generate STOP condition
			if(Sr == I2C_DISABLE_SR)
				I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		}

		// wait until RXNE becomes 1
		while(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_FLAG_RXNE) == 0);
		// read the data from data register in to buffer and increment the buffer address
		*(pRxBuffer++) = pI2CHandle->pI2Cx->DR;
		Len--;

	}
	//6. Re-enable acking
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE){
		I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_ENABLE);
	}
}

// Slave send and recieve data
void I2C_SlaveSendData(I2C_RegDef_t *pI2Cx, uint8_t data){
	pI2Cx->DR = data;
}
uint8_t I2C_SlaveRecieveData(I2C_RegDef_t *pI2Cx){
	return (uint8_t)pI2Cx->DR;
}

// Master end and receive data with Interrupt
uint8_t I2C_MasterSendDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr){
	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pTxBuffer = pTxBuffer;
		pI2CHandle->TxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_TX;
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);

	}

	return busystate;
}

uint8_t I2C_MasterRecieveDataIT(I2C_Handle_t *pI2CHandle, uint8_t *pRxBuffer, uint8_t Len, uint8_t SlaveAddr, uint8_t Sr){
	uint8_t busystate = pI2CHandle->TxRxState;

	if( (busystate != I2C_BUSY_IN_TX) && (busystate != I2C_BUSY_IN_RX))
	{
		pI2CHandle->pRxBuffer = pRxBuffer;
		pI2CHandle->RxLen = Len;
		pI2CHandle->TxRxState = I2C_BUSY_IN_RX;
		pI2CHandle->RxSize = Len; //Rxsize is used in the ISR code to manage the data reception
		pI2CHandle->DevAddr = SlaveAddr;
		pI2CHandle->Sr = Sr;

		//Implement code to Generate START Condition
		I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

		//Implement the code to enable ITBUFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);

		//Implement the code to enable ITEVFEN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);

		//Implement the code to enable ITERREN Control Bit
		pI2CHandle->pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);

	}

	return busystate;
}

// Enable callback events
void I2C_SlaveEnableDisableCallbackEvents(I2C_RegDef_t *pI2Cx, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		pI2Cx->CR2 |= ( 1 << I2C_CR2_ITBUFEN);
		pI2Cx->CR2 |= ( 1 << I2C_CR2_ITEVTEN);
		pI2Cx->CR2 |= ( 1 << I2C_CR2_ITERREN);
	}
	else{
		pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITBUFEN);
		pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITEVTEN);
		pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITERREN);
	}
}

// Close send data and close recieve data
void I2C_CloseSendData(I2C_Handle_t *pI2CHandle){

	//Implement the code to disable ITBUFEN Control Bit
	pI2CHandle->pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITBUFEN);

	//Implement the code to disable ITEVFEN Control Bit
	pI2CHandle->pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITEVTEN);

	// Change pI2CHandle
	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->TxLen = 0;
	if(pI2CHandle->I2C_Config.I2C_ACKControl == I2C_ACK_ENABLE)
		I2C_ManageAcking(pI2CHandle->pI2Cx, ENABLE);
}

void I2C_CloseRecieveData(I2C_Handle_t *pI2CHandle){
	//Implement the code to disable ITBUFEN Control Bit
	pI2CHandle->pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITBUFEN);

	//Implement the code to disable ITEVFEN Control Bit
	pI2CHandle->pI2Cx->CR2 &= ~( 1 << I2C_CR2_ITEVTEN);

	// Change pI2CHandle
	pI2CHandle->TxRxState = I2C_READY;
	pI2CHandle->RxLen = 0;
	I2C_ManageAcking(pI2CHandle->pI2Cx, ENABLE);
}

// IRQ Configuration
void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
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

void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority){

}

// ISR handling
void I2C_EV_IRQHandling(I2C_Handle_t *pI2CHandle){
	/*
	 * Interrupt handling for both master and slave mode of a device
	 */

	// If event interrupt is not enabled, return now. ---------------------------------
	uint8_t event_interrupt_disabled = !((pI2CHandle->pI2Cx->CR2 >> I2C_CR2_ITEVTEN) & 1);
	if(event_interrupt_disabled)
		return;

	// ---------------------------------------------------------------------------------

	uint8_t buffer_interrupt_enabled  = (pI2CHandle->pI2Cx->CR2 >> I2C_CR2_ITBUFEN) & 1;
	uint8_t address_sent_or_matched   = (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_ADDR) & 1;
	uint8_t start_condition_generated = (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_SB) & 1;
	uint8_t device_in_master_mode     = (pI2CHandle->pI2Cx->SR2 >> I2C_SR2_MSL) & 1;
	uint8_t device_in_slave_mode      = !device_in_master_mode;
	uint8_t i2c_busy_in_rx            = (pI2CHandle->TxRxState == I2C_BUSY_IN_RX);
	uint8_t i2c_busy_in_tx            = (pI2CHandle->TxRxState == I2C_BUSY_IN_TX);
	uint8_t byte_transfer_finished    = (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_BTF) & 1;
	uint8_t tx_reg_empty              = (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_TXE) & 1;
	uint8_t rx_reg_not_empty          = (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_RXNE) & 1;
	uint8_t repeated_start_disabled   = pI2CHandle->Sr == I2C_DISABLE_SR;
	uint8_t stop_condition_detected   = (pI2CHandle->pI2Cx->SR1 >> I2C_SR1_STOPF) & 1;


	// 1. Handle for interrupt generated by SB event
	// Note: SB flag is only applicable in Master mode
	if(start_condition_generated){
		// SB flag is set (only happen in master mode)
		// After start condition happen, we need to execute address phase
		if(i2c_busy_in_tx)
			I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, pI2CHandle->DevAddr, I2C_WRITE);
		else if (i2c_busy_in_rx)
			I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, pI2CHandle->DevAddr, I2C_READ);
	}

	// 2. Handle for interrupt generated by ADDR event
	// Note: When master mode: Address is sent
	//       When slave mode : Address is matched with own address
	if(address_sent_or_matched){
		if(device_in_master_mode && i2c_busy_in_rx && (pI2CHandle->RxSize == 1)){
			// Disable Acking
			I2C_ManageAcking(pI2CHandle->pI2Cx, I2C_ACK_DISABLE);
		}
		//ADDR flag is set
		I2C_ClearADDRFlag(pI2CHandle->pI2Cx);
	}

	// 3. Handle for interrupt generated by BTF(Byte Transfer Finished) event
	if(byte_transfer_finished && i2c_busy_in_tx && tx_reg_empty && (pI2CHandle->TxLen == 0)){
		// BTF,TXE set and Len = 0
		// Generate stop condition
		if(repeated_start_disabled)
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
		// Reset elements of handle structure
		I2C_CloseSendData(pI2CHandle);
		// Notify application about transmission complete
		I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_TX_CMPLT);
	}

	// 4. Handle for interrupt generated by STOPF event
	// Note: Stop detection flag is applicable only in slave mode.
	if(stop_condition_detected){
		// STOPF flag is set
		// Clear the STOPF
		I2C_ClearSTOPFFlag(pI2CHandle->pI2Cx);
		// Notify the application that stop is detected
		I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_STOP);
	}

	// 5. Handle for interrupt generated by TXE event.
	if(buffer_interrupt_enabled && tx_reg_empty){
		// We have to do the data transmission
		if(device_in_master_mode && i2c_busy_in_tx && (pI2CHandle->TxLen > 0)){
			// Load the data into DR
			pI2CHandle->pI2Cx->DR = *(pI2CHandle->pTxBuffer);
			// Decrement TxLen
			pI2CHandle->TxLen--;
			// Increment Buffer address
			pI2CHandle->pTxBuffer++;
		}else if(device_in_slave_mode){
			//make sure that the slave is really in transmitter mode
			if(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_TRA))
				I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_DATA_REQ);
		}
	}

	// 6. Handle for interrupt generated by RXNE event.
	if(buffer_interrupt_enabled && rx_reg_not_empty){
		if(device_in_master_mode && i2c_busy_in_rx){
			if(pI2CHandle->RxSize == 1){
				*(pI2CHandle->pRxBuffer) = pI2CHandle->pI2Cx->DR;
				pI2CHandle->RxLen--;
			}else if(pI2CHandle->RxSize > 1){
				// Read DR
				*(pI2CHandle->pRxBuffer++) = pI2CHandle->pI2Cx->DR;
				pI2CHandle->RxLen--;
				if(pI2CHandle->RxLen == 1)
					I2C_ManageAcking(pI2CHandle->pI2Cx, DISABLE);
			}
			if(pI2CHandle->RxLen == 0){
				// Generate Stop condition
				if(repeated_start_disabled)
					I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
				// Close the I2C data reception
				I2C_CloseRecieveData(pI2CHandle);
				// Notify the application
				I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_RX_CMPLT);
			}
		}else if(device_in_slave_mode){
			//make sure that the slave is really in receiver mode
			if(!(pI2CHandle->pI2Cx->SR2 & ( 1 << I2C_SR2_TRA)))
				I2C_ApplicationEventCallback(pI2CHandle, I2C_EV_DATA_RCV);
		}
	}
}

void I2C_ER_IRQHandling(I2C_Handle_t *pI2CHandle){
	uint32_t temp1,temp2;

	    //Know the status of  ITERREN control bit in the CR2
		temp2 = (pI2CHandle->pI2Cx->CR2) & ( 1 << I2C_CR2_ITERREN);


	/***********************Check for Bus error************************************/
		temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1<< I2C_SR1_BERR);
		if(temp1  && temp2 )
		{
			//This is Bus error

			//Implement the code to clear the buss error flag
			pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_BERR);

			//Implement the code to notify the application about the error
		   I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_BERR);
		}

	/***********************Check for arbitration lost error************************************/
		temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_ARLO );
		if(temp1  && temp2)
		{
			//This is arbitration lost error

			//Implement the code to clear the arbitration lost error flag
			pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_ARLO);

			//Implement the code to notify the application about the error
			I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_ARLO);

		}

	/***********************Check for ACK failure  error************************************/

		temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_AF);
		if(temp1  && temp2)
		{
			//This is ACK failure error

		    //Implement the code to clear the ACK failure error flag
			pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_AF);

			//Implement the code to notify the application about the error
			I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_AF);
		}

	/***********************Check for Overrun/underrun error************************************/
		temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_OVR);
		if(temp1  && temp2)
		{
			//This is Overrun/underrun

		    //Implement the code to clear the Overrun/underrun error flag
			pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_OVR);

			//Implement the code to notify the application about the error
			I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_OVR);
		}

	/***********************Check for Time out error************************************/
		temp1 = (pI2CHandle->pI2Cx->SR1) & ( 1 << I2C_SR1_TIMEOUT);
		if(temp1  && temp2)
		{
			//This is Time out error

		    //Implement the code to clear the Time out error flag
			pI2CHandle->pI2Cx->SR1 &= ~( 1 << I2C_SR1_TIMEOUT);

			//Implement the code to notify the application about the error
			I2C_ApplicationEventCallback(pI2CHandle, I2C_ERROR_TIMEOUT);
		}
}


















