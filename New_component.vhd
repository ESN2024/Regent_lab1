library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity New_component is port(
	clk,reset : in std_logic;
	bp : in std_logic_vector(7 downto 0);
	led : out std_logic_vector(7 downto 0));
end entity;

architecture arch of New_component is

	component lab1_sys is
	  port (
			clk_clk          : in  std_logic                    := 'X';             -- clk
			pio_0_led_export : out std_logic_vector(7 downto 0);                    -- export
			pio_1_bp_export  : in  std_logic_vector(7 downto 0) := (others => 'X'); -- export
			reset_reset_n    : in  std_logic                    := 'X'              -- reset_n
	  );
	end component lab1_sys;

	begin
	u0 : component lab1_sys
	  port map (
			clk_clk          => clk,      --clk.clk
			pio_0_led_export => led, 		--pio_0_led.export
			pio_1_bp_export  => bp,  		--pio_1_bp.export
			reset_reset_n    => reset     --reset.reset_n
	  );
end architecture;