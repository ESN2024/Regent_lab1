	component lab3_sys is
		port (
			clk_clk          : in    std_logic                     := 'X'; -- clk
			pio_0_seg_export : out   std_logic_vector(11 downto 0);        -- export
			reset_reset_n    : in    std_logic                     := 'X'; -- reset_n
			i2c_scl_pad_io   : inout std_logic                     := 'X'; -- scl_pad_io
			i2c_sda_pad_io   : inout std_logic                     := 'X'; -- sda_pad_io
			pio_1_btn_export : in    std_logic                     := 'X'  -- export
		);
	end component lab3_sys;

	u0 : component lab3_sys
		port map (
			clk_clk          => CONNECTED_TO_clk_clk,          --       clk.clk
			pio_0_seg_export => CONNECTED_TO_pio_0_seg_export, -- pio_0_seg.export
			reset_reset_n    => CONNECTED_TO_reset_reset_n,    --     reset.reset_n
			i2c_scl_pad_io   => CONNECTED_TO_i2c_scl_pad_io,   --       i2c.scl_pad_io
			i2c_sda_pad_io   => CONNECTED_TO_i2c_sda_pad_io,   --          .sda_pad_io
			pio_1_btn_export => CONNECTED_TO_pio_1_btn_export  -- pio_1_btn.export
		);

