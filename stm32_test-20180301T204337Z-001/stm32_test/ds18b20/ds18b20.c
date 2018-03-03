/*******************************************
 * This file is part of ds18b20 driver
 * Author: Andrey Zvolikevich
 * Date: 26.01.2018
 *******************************************/
 
 #include "ds18b20.h"
 #include <stm32f10x.h>
 
 void ds18b20_reset()
 {
	 WIRE_PUSH_LOW();
	 ds18b20_delay(RESET_PULSE);
	 WIRE_RELEASE();
	 ds18b20_delay(WAIT_AFTER_RESET);
 }
 
 uint8_t ds18b20_slavePresent()
 {
	 uint8_t present = 1;
	 WIRE_IN();
	 if (GPIOB->IDR & GPIO_IDR_IDR10) present = 1;
	 else present = 0;
	 WIRE_OUT();
	 ds18b20_delay(SLAVE_PRESENCE_RESPONSE);
	 ds18b20_delay(RECOVERY);
	 return present;
 }
 
 void ds18b20_write0()
 {
	 WIRE_PUSH_LOW();
	 ds18b20_delay(WRITE0);
	 WIRE_RELEASE();
	 ds18b20_delay(RECOVERY);
 }
 
 void ds18b20_write1()
 {
	 WIRE_PUSH_LOW();
	 ds18b20_delay(WRITE1_INIT);
	 WIRE_RELEASE();
	 ds18b20_delay(WRITE1);
	 ds18b20_delay(RECOVERY);
 }
 
 uint8_t ds18b20_readBit()
 {
	 uint8_t bit = 0;
	 WIRE_PUSH_LOW();
	 ds18b20_delay(READ_INIT);
	 WIRE_RELEASE();
	 ds18b20_delay(UNTIL_MASTER_SAMPLES);
	 WIRE_IN();
	 if (GPIOB->IDR & GPIO_IDR_IDR10) bit = 1;
	 else bit = 0;
	 ds18b20_delay(READ);
	 WIRE_OUT();
	 ds18b20_delay(RECOVERY);
	 return bit;
 }
 
 void ds18b20_SendCommand(uint8_t command)
 {
	 for (uint8_t i = 0; i < 8; i++)
	 {
		 uint8_t bit = (command >> i) & 0x1;
		 if (bit) ds18b20_write1();
		 else ds18b20_write0();
	 }
 }
 
 uint8_t ds18b20_ReadResponse()
 {
	 uint8_t byte = 0;
	 for (uint8_t i = 0; i < 8; i++)
	 {
		 byte += (ds18b20_readBit() << i);
	 }
	 return byte;
 }
 
 uint16_t ds18b20_GetTemperature()
{
	uint16_t ScratchPadTemp = 0;			//first 2 bytes from ScratcpPad
	uint8_t ScratchPad[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	ds18b20_reset();
	ds18b20_slavePresent();
	ds18b20_SendCommand(0xCC);								//Skip ROM
	ds18b20_SendCommand(0x44);								//Convert T
	
	ds18b20_delay(CONVERT_T_MAX_PRESC + 10);	//wait while ds18b20 converts temperature with maximum prescision
	
	ds18b20_reset();
	ds18b20_slavePresent();
	ds18b20_SendCommand(0xCC);								//Skip ROM
	ds18b20_SendCommand(0xBE);								//Read Scratchpad
	for (uint8_t i = 0; i < 9; i++)
	{
		ScratchPad[i] = ds18b20_ReadResponse();
	}
	
	ScratchPadTemp = ScratchPad[1];
	ScratchPadTemp = (ScratchPadTemp << 8);
	ScratchPadTemp += ScratchPad[0];
	return ScratchPadTemp;
}

uint8_t ds18b20_GetTempSign(uint16_t temp)
{
	uint8_t sign = ' ';
	if (temp & 0x8000) sign = '-';
	else sign = '+';
}

uint8_t ds18b20_GetTempInteger(uint16_t temp)
{
	uint8_t temperature = 0;
	uint8_t scratch_pad0 = (temp & 0xFF);
	uint8_t scratch_pad1 = (temp & 0xFF00) >> 8;
	for (uint8_t i = 0; i < 3; i++)
	{
		temperature += (scratch_pad1 & (0x1 << i)) << 4;
	}
	for (uint8_t i = 0; i < 4; i++)
	{
		temperature += (scratch_pad0 & (0x1 << (i + 4))) >> 4;
	}
	return temperature;
}

uint16_t ds18b20_GetTempFloat(uint16_t temp)	//bits 0 - 3
{
	uint16_t temperature = 0;
	if (temp & 0x1) temperature += 675;
	if (temp & 0x2) temperature += 1250;
	if (temp & 0x4) temperature += 2500;
	if (temp & 0x8) temperature += 5000;
	
	return temperature;
}
 