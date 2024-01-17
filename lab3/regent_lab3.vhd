library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity regent_lab3 is port(
	clk,reset,btn : 	in std_logic;
	i2c_scl,i2c_sda : inout std_logic;
	i2c_mode : 			out std_logic := '1';
	seg :			 		out std_logic_vector(20 downto 0));
end entity;

architecture arch of regent_lab3 is
	
	component lab3_sys is
		  port (
				clk_clk          : in    std_logic                     := 'X'; -- clk
            i2c_scl_pad_io   : inout std_logic                     := 'X'; -- scl_pad_io
            i2c_sda_pad_io   : inout std_logic                     := 'X'; -- sda_pad_io
            pio_0_seg_export : out   std_logic_vector(11 downto 0);        -- export
            pio_1_btn_export : in    std_logic                     := 'X'; -- export
            reset_reset_n    : in    std_logic                     := 'X'  -- reset_n
		  );
	 end component lab3_sys;
	 
	component bin_to_7seg is                                         
		port(
		
			inp : in std_logic_vector(3 downto 0); -- input
			outp : out std_logic_vector(6 downto 0) -- output

		);
   end component bin_to_7seg;
	
	
	signal seg_out : std_logic_vector(11 downto 0);
	begin
	
		u0 : component lab3_sys
		  port map (
				clk_clk          => clk,          			--       clk.clk
				pio_0_seg_export => seg_out,  				-- pio_0_seg.export
				i2c_scl_pad_io   => i2c_scl,   				--       i2c.scl_pad_io
            i2c_sda_pad_io   => i2c_sda,  				--          .sda_pad_io
            pio_1_btn_export => btn, 						-- pio_1_btn.export
				reset_reset_n    => reset     				--     reset.reset_n
		  );
			  
		u1 : component bin_to_7seg
		port map (
			inp => seg_out(3 downto 0),
			outp => seg(6 downto 0)
		);
		
		u2 : component bin_to_7seg
		port map (
			inp => seg_out(7 downto 4),
			outp => seg(13 downto 7)
		);
		
		u3 : component bin_to_7seg
		port map (
			inp => seg_out(11 downto 8),
			outp => seg(20 downto 14)
		);

end architecture;
