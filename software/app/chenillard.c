#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include <stdio.h>
#include <unistd.h>

main(void)
{
	int data=0x01;
	while(1)
	{
		for(int i=1;i<=8;i++)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_LED_BASE,data);//data
			usleep(500000);		
			data= data << 1;
		}
		data=0x01;
	}
	
}