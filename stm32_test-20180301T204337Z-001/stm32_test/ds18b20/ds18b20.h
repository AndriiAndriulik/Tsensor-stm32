/*******************************************
 * This file is part of ds18b20 driver
 * Author: Andrey Zvolikevich
 * Date: 26.01.2018
 *******************************************/
 #include <stdint.h>
 
typedef enum ds18b20_timing_typedef
{
	RESET_PULSE = 490,
	WAIT_AFTER_RESET = 65,
	SLAVE_PRESENCE_RESPONSE = 480,
	RECOVERY = 2,
	WRITE0 = 90,
	WRITE1_INIT = 2,
	WRITE1 = 90,
	READ_INIT = 2,
	UNTIL_MASTER_SAMPLES = 8,
	READ = 40,
	CONVERT_T_MAX_PRESC = 750000
}ds18b20_timing;
//configure processor frequency (MHz)
#define freq 				7
#define ds18b20_delay(usec) for (uint32_t i = 0; i < freq * usec; i++)
//configure wire to output
#define WIRE_OUT()	GPIOB->CRH |= GPIO_CRH_MODE10; \
	 GPIOB->CRH |= GPIO_CRH_CNF10_0
//configure wire to output
#define WIRE_IN()		GPIOB->CRH &= ~(GPIO_CRH_MODE10); \
	 GPIOB->CRH |= GPIO_CRH_CNF10_0
//push the bus low
#define WIRE_PUSH_LOW()		GPIOB->ODR &= ~(GPIO_ODR_ODR10)
//release the bus
#define WIRE_RELEASE()		GPIOB->ODR |= GPIO_ODR_ODR10

void ds18b20_reset();
//Slave response to reset()
uint8_t ds18b20_slavePresent();

void ds18b20_write0();

void ds18b20_write1();

uint8_t ds18b20_readBit();

void ds18b20_SendCommand(uint8_t);

uint8_t ds18b20_ReadResponse();

uint16_t ds18b20_GetTemperature();

uint8_t ds18b20_GetTempSign(uint16_t temp);

uint8_t ds18b20_GetTempInteger(uint16_t temp);

uint16_t ds18b20_GetTempFloat(uint16_t temp);
