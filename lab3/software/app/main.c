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


volatile __int8_t c = 0;
volatile __uint8_t d = 0;
volatile __uint8_t u = 0;

volatile __uint8_t axe = 1;

volatile __int16_t data;

#define slave_addr 0x1D

#define X0_addr 0x32
#define X1_addr 0x33
#define Y0_addr 0x34
#define Y1_addr 0x35
#define Z0_addr 0x36
#define Z1_addr 0x37

#define X_offset_addr 0x1E
#define Y_offset_addr 0x1F
#define Z_offset_addr 0x20

#define X_offset_value 0xC5
#define Y_offset_value 0xC4
#define Z_offset_value 0xC4

#define scale_factor 3.9



void conv_bcd(__int16_t val) {
    c = val / 100;
    d = (val / 10) % 10;
    u = val % 10;
}

__int16_t read_acc (__uint16_t addr){
	
	I2C_start(OPENCORES_I2C_0_BASE,slave_addr,0);
	I2C_write(OPENCORES_I2C_0_BASE,addr,0);		
	I2C_start(OPENCORES_I2C_0_BASE,slave_addr,1);
	return I2C_read(OPENCORES_I2C_0_BASE, 1);
}

void irqhandler_timer (void * context){
	
	switch (axe) {
		case 1:
			data = read_acc(X0_addr);
			data = data + (read_acc(X1_addr)<<8);
			alt_printf("x %x \n",data);
		break;
		
		case 2:
			data = read_acc(Y0_addr);
			data = data + (read_acc(Y1_addr)<<8);
			alt_printf("y %x \n",data);
		break;
		
		case 3:
			data = read_acc(Z0_addr);
			data = data + (read_acc(Z1_addr)<<8);
			alt_printf("z %x \n\n",data);
		break;
	}
	
	data = data * scale_factor;
	if(data & 0x8000) data = -(0xFFFF -data +1);

	conv_bcd(data);
	
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, (c<<8) | (d<<4) | u);
	
	// Clear flag interrupt
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, 0x01);
}

static void irqhandler_btn (void * context, alt_u32 id)
{
	IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE);
	
	if (axe<3)
	{
		axe++;
	}
	else
	{
		axe = 1;
	}

   	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE,0x80);
}

void set_offset (){	
	I2C_start(OPENCORES_I2C_0_BASE,slave_addr,1);
	I2C_write(OPENCORES_I2C_0_BASE,Y_offset_addr,0);	
	I2C_write(OPENCORES_I2C_0_BASE,Y_offset_value,1);
	
	I2C_start(OPENCORES_I2C_0_BASE,slave_addr,1);
	I2C_write(OPENCORES_I2C_0_BASE,Y_offset_addr,0);	
	I2C_write(OPENCORES_I2C_0_BASE,Y_offset_value,1);
	
	I2C_start(OPENCORES_I2C_0_BASE,slave_addr,1);
	I2C_write(OPENCORES_I2C_0_BASE,Z_offset_addr,0);	
	I2C_write(OPENCORES_I2C_0_BASE,Z_offset_value,1);
}

int main()
{
	I2C_init(OPENCORES_I2C_0_BASE,ALT_CPU_FREQ,400000);
	
	IORD_ALTERA_AVALON_TIMER_CONTROL (TIMER_0_BASE);
	alt_irq_register(TIMER_0_IRQ,NULL,irqhandler_timer);
	
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_1_BASE, 0b1);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_1_BASE, 0b1);
	alt_irq_register(PIO_1_IRQ, NULL, (void *) irqhandler_btn);
	
	set_offset();
		
	while(1) {
		
	}
	
	return 0;
}