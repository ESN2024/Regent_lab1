#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "sys/alt_sys_init.h"
#include "alt_types.h"
#include "io.h"
#include <unistd.h>

volatile __uint16_t val = 0;
volatile __uint8_t c = 0;
volatile __uint8_t d = 0;
volatile __uint8_t u = 0;
volatile __uint16_t pl;
volatile __uint16_t ph;

void irqhandler_timer (void * context){
	
		conv_bcd(val);
		
		if (val < 1000){
			val = val + 1;
		}
		else 
		{
			val = 0;
		}
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, (c<<8) | (d<<4) | u);
		
		// Clear flag interrupt
		IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0x01);
}

void conv_bcd(__uint16_t val) {
    c = val / 100;
    d = (val / 10) % 10;
    u = val % 10;
}

int main()
{
	
	IORD_ALTERA_AVALON_TIMER_CONTROL (TIMER_0_BASE);
	alt_irq_register(TIMER_0_IRQ,NULL,irqhandler_timer);
	
	pl = IORD_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE);
	//alt_printf("periodeL = %x\n", pl);
	
	ph = IORD_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE);
	//alt_printf("periodeH = %x\n", ph);
	
	while (1) 
	{		
	}
	return 0;
}