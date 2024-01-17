
module lab3_sys (
	clk_clk,
	pio_0_seg_export,
	reset_reset_n,
	i2c_scl_pad_io,
	i2c_sda_pad_io,
	pio_1_btn_export);	

	input		clk_clk;
	output	[11:0]	pio_0_seg_export;
	input		reset_reset_n;
	inout		i2c_scl_pad_io;
	inout		i2c_sda_pad_io;
	input		pio_1_btn_export;
endmodule
