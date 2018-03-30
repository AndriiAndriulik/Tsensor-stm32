#include "stm32f10x.h"
#include "enc28j60.h"
#include "uip.h"
#include "uip_arp.h"
//#include <hello-world.h> // including in uip-conf.h
#include "uip-conf.h"
#include "diag/Trace.h"

void PortC_Init(void);
void PortB_Init(void);

void vTask_uIP_periodic();
void vTask_uIP();

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

#define LED_Toggle(void)	GPIOC->ODR ^= GPIO_ODR_ODR13
#define wait(ticks) for (int i = 0; i < ticks; i++)

//debug=============================================================================
#define LED_ReceivePacket(void)		LED_Toggle(); wait(5000000); LED_Toggle(); wait(5000000)
#define LED_SendPacket(void)			LED_Toggle(); wait(1000000); LED_Toggle(); \
	wait(1000000); LED_Toggle(); wait(1000000); LED_Toggle(); wait(1000000)
void showBuffer();
//debug=============================================================================

int main(void)
{
	PortC_Init();
	PortB_Init();
	LED_Toggle();	//LED off

	struct uip_eth_addr mac = { {0x54,0x55,0x58,0x10,0x00,0x29} };
	
	enc28j60_init(mac.addr);

	uip_init();
	uip_arp_init();

	httpd_init();

	uip_setethaddr(mac);

	uip_ipaddr_t ipaddr;
	uip_ipaddr(ipaddr, 192, 168, 0, 57);
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, 192, 168, 0, 1);
	uip_setdraddr(ipaddr);
	uip_ipaddr(ipaddr, 255, 255, 255, 0);
	uip_setnetmask(ipaddr);
	
	while (1)
	{
		showBuffer();
		vTask_uIP_periodic();
		vTask_uIP();
	}
}

void PortC_Init()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	GPIOC->CRH |= GPIO_CRH_MODE13_1;
}

void PortB_Init()
{
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRH |= GPIO_CRH_MODE10;
	GPIOB->CRH |= GPIO_CRH_CNF10_0;
}

void vTask_uIP_periodic() 
{
	uint32_t i;
	uint8_t delay_arp = 0;
	wait(10000);
	delay_arp++;
	for (i = 0; i < UIP_CONNS; i++)
	{
		uip_periodic(i);
		if (uip_len > 0)
		{
			uip_arp_out();
			enc28j60_send_packet((uint8_t *) uip_buf, uip_len);
			//LED_SendPacket();
		}
	}

#if UIP_UDP
	for(i = 0; i < UIP_UDP_CONNS; i++)
	{
		uip_udp_periodic(i);
		if(uip_len > 0)
		{
			uip_arp_out();
			network_send();
		}
	}
#endif /* UIP_UDP */

	if (delay_arp >= 50) 
	{ 
		delay_arp = 0;
		uip_arp_timer();
	}
}
//--------------------------------------------------------------
void vTask_uIP() 
{	
	uip_len = enc28j60_recv_packet((uint8_t *) uip_buf, UIP_BUFSIZE);
	//LED_ReceivePacket();
	if (uip_len > 0)
	{
		if (BUF->type == htons(UIP_ETHTYPE_IP)) 
		{
			uip_arp_ipin();
			uip_input();
			if (uip_len > 0)
			{
				uip_arp_out();
				enc28j60_send_packet((uint8_t *) uip_buf, uip_len);
			  //LED_SendPacket();
			}
		}
		else if (BUF->type == htons(UIP_ETHTYPE_ARP)) 
		{
			uip_arp_arpin();
			if (uip_len > 0)
			{
				enc28j60_send_packet((uint8_t *) uip_buf, uip_len);
				//LED_SendPacket();
			}
		}
	}
}

void showBuffer()
{
	/*for (uint16_t i = 0; i < UIP_BUFSIZE; i++)
	{
		uint8_t counter = 0;
		do
		{
			trace_printf("%d", uip_buf[i]);
		} while(++counter < 8);
		trace_printf("\n");
	}*/
}


