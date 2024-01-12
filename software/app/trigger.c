#include "system.h"
#include "altera_avalon_pio_regs.h"
#include <sys/alt_irq.h>
#include "sys/alt_stdio.h"
#include <io.h>
#include <alt_types.h>
#include "sys/alt_sys_init.h"
#include <stdio.h>
#include <unistd.h>

static void irqhandler (void * context, alt_u32 id)
{
	int data=0x01;
	for(int i=1;i<=8;i++)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_LED_BASE,data);//data
			usleep(500000);		
			data= data << 1;
		}
		data=0x01;
}

main(void)
{
	alt_irq_register(PIO_1_BP_IRQ, NULL, (void*)irqhandler );
	while(1)
	{
	}
	
}