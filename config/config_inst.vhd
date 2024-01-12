	component config is
		port (
			clk_clk          : in  std_logic                    := 'X';             -- clk
			pio_0_led_export : out std_logic_vector(7 downto 0);                    -- export
			pio_1_bp_export  : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			reset_reset_n    : in  std_logic                    := 'X'              -- reset_n
		);
	end component config;

	u0 : component config
		port map (
			clk_clk          => CONNECTED_TO_clk_clk,          --       clk.clk
			pio_0_led_export => CONNECTED_TO_pio_0_led_export, -- pio_0_led.export
			pio_1_bp_export  => CONNECTED_TO_pio_1_bp_export,  --  pio_1_bp.export
			reset_reset_n    => CONNECTED_TO_reset_reset_n     --     reset.reset_n
		);

