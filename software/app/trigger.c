#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "sys/alt_sys_init.h"
#include "alt_types.h"
#include "io.h"
#include <unistd.h>

volatile int time = 200000;
volatile int data = 0x00;
volatile int val;

static void irqhandler_btn (void * context, alt_u32 id)
{
	val = IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BP_BASE);
	
	data=0x01;
        for(int i=1;i<=8;i++)
	{
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_LED_BASE,data);//data
		usleep(time);		
		data= data << 1;
	}
	data=0x00;
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_LED_BASE,data);


   	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BP_BASE,0x80);
}

int main()
{
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BP_BASE, 0b10000000);

	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BP_BASE, 0b10000000);

	alt_irq_register(PIO_1_BP_IRQ, NULL, (void *) irqhandler_btn);

	while(1)
	{
	}
	return 0;
}