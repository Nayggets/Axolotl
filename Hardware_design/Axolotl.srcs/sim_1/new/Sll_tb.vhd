
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

entity Sll_tb is

end entity;


architecture Behavioral of Sll_tb is
    signal a : STD_LOGIC_VECTOR(15 downto 0);
    signal b : STD_LOGIC_VECTOR(15 downto 0);
    signal c : STD_LOGIC_VECTOR(15 downto 0);
begin
    inst_Sll : entity work.mySll
        port map( a => a,
                  b => b,
                  c => c);

    test_process : process
    begin
        a <= "1110000000000000";
        b <= "0000000000000001";
        wait;
    end process;

end architecture;