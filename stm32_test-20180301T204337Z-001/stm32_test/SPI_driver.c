#include <stm32f10x.h>
#include "SPI_driver.h"

void SPI2_Init()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	//NSS(12) -- gpio pp; SCK(13) -- altf MISO(14) -- altf  MOSI(15) -- altf
	GPIOB->CRH &= ~(GPIO_CRH_CNF12 | GPIO_CRH_CNF13 | GPIO_CRH_CNF14 | GPIO_CRH_CNF15);
	GPIOB->CRH |= GPIO_CRH_CNF13_1 | GPIO_CRH_CNF14_1 | GPIO_CRH_CNF15_1;
	GPIOB->CRH |= GPIO_CRH_MODE12_0 | GPIO_CRH_MODE13_0 | GPIO_CRH_MODE14_0 | GPIO_CRH_MODE15_0;
	
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
	SPI2->CR1 &= ~(SPI_CR1_SPE);				//disable spi during init
	SPI2->CR1 &= ~(SPI_CR1_BIDIMODE); 	//2 wires
	SPI2->CR1 &= ~(SPI_CR1_CPOL);       //Polarity cls signal CPOL = 0;
  SPI2->CR1 &= ~(SPI_CR1_CPHA);       //Phase cls signal    CPHA = 0;
	SPI2->CR1 &= ~(SPI_CR1_DFF);				//8 bit
	SPI2->CR1 |= SPI_CR1_SSM;						//nss soft
	SPI2->CR1 |= SPI_CR1_SSI;
	
	//Prescaler = 256
	SPI2->CR1 |= SPI_CR1_BR_0;
	SPI2->CR1 |= SPI_CR1_BR_1;
	SPI2->CR1 |= SPI_CR1_BR_2;
	
	SPI2->CR1 &= ~(SPI_CR1_LSBFIRST);		//first bit - most significant
	//SPI2->CR1 |= SPI_CR1_LSBFIRST;		
	SPI2->CR1 |= SPI_CR1_MSTR;					//master mode
	
	SPI2->CR1 |= SPI_CR1_SPE;						//enable spi
}

void SPI2_Transmit(uint8_t ch)
{
	while ( !(SPI2->SR & SPI_SR_TXE) );
	SPI2->DR = ch;
}

uint8_t SPI2_Receive()
{
	while (!(SPI2->SR & SPI_SR_RXNE));
	return SPI2->DR;
}

