/******************************************************************
 * Driver for SPI2 in stm32f103c8t6
 * for forward interfacing with enc28j60
 ******************************************************************/
 
/*
 * 12 - NSS
 * 13 - SCK
 * 14 - MISO
 * 15 - MOSI
 */
 void SPI2_Init(void);
 
 void SPI2_Transmit(uint8_t ch);
 
 uint8_t SPI2_Receive(void);