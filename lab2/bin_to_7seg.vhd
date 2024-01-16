library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity bin_to_7seg is 
port(
	inp : in std_logic_vector(3 downto 0); -- input
	outp : out std_logic_vector(6 downto 0) -- output
	);
end entity;

architecture arch of bin_to_7seg is
begin

    outp <= "1000000" when inp = "0000" else
            "1111001" when inp = "0001" else
            "0100100" when inp = "0010" else
            "0110000" when inp = "0011" else
            "0011001" when inp = "0100" else
            "0010010" when inp = "0101" else
            "0000010" when inp = "0110" else
            "1111000" when inp = "0111" else
            "0000000" when inp = "1000" else
            "0010000" when inp = "1001" else
            "1111111"; 

end architecture;