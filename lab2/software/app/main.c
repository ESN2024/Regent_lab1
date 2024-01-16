#include "system.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_stdio.h"
#include "sys/alt_irq.h"
#include "sys/alt_sys_init.h"
#include "alt_types.h"
#include "io.h"
#include <unistd.h>

volatile __uint16_t val = 0;
volatile __uint8_t c = 0;
volatile __uint8_t d = 0;
volatile __uint8_t u = 0;

void conv_bcd(__uint16_t val) {
    c = val / 100;
    d = (val / 10) % 10;
    u = val % 10;
}

int main()
{
	while (1) 
	{
		conv_bcd(val);
		
		val = val + 1;
		IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, (c<<8) | (d<<4) | u);
		usleep(50000);
	}
	return 0;
}