
module lab1_sys (
	clk_clk,
	pio_0_led_export,
	pio_1_bp_export,
	reset_reset_n);	

	input		clk_clk;
	output	[7:0]	pio_0_led_export;
	input	[7:0]	pio_1_bp_export;
	input		reset_reset_n;
endmodule
