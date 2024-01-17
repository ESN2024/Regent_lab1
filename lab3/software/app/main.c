#include "sys/stdio.h"
#include <unistd.h>
#include "system.h"
#include <stdlib.h>
#include <io.h>
#include <string.h>
#include "altera_avalon_pio_regs.h"
#include <alt_types.h>
#include "opencores_i2c_regs.h"
#include "opencores_i2c.h"
#include "altera_avalon_timer_regs.h"
#include "altera_avalon_timer.h"
#include "sys/alt_irq.h"
#include "sys/alt_sys_init.h"

volatile __uint16_t val = 0;
volatile __uint8_t c = 0;
volatile __uint8_t d = 0;
volatile __uint8_t u = 0;
volatile __uint16_t data;

void irqhandler_timer (void * context){
	
		conv_bcd(val);
		
		if (val < 1000){
			
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
	
	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,400000);
		
	while(1) {
		
	
		I2C_start(OPENCORES_I2C_0_BASE,0x,0);
		data =I2C_write(OPENCORES_I2C_0_BASE,0x,0);
		
		
		I2C_start(OPENCORES_I2C_0_BASE,0x,1);
		data = I2C_read(OPENCORES_I2C_0_BASE, 1);
		alt_printf("data %x\n", data);
	
	}
	
	return 0;
}