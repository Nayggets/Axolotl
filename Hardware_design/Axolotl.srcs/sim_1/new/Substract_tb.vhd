
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;


entity Substract_tb is

end entity;


architecture Behavioral of Substract_tb is
    signal a : STD_LOGIC_VECTOR(15 downto 0);
    signal b : STD_LOGIC_VECTOR(15 downto 0);
    signal c : STD_LOGIC_VECTOR(15 downto 0);
begin
    inst_and : entity work.Substractor
        port map( a => a,
                  b => b,
                  c => c);

    test_process : process
    begin
        a <= "0110000000000000";
        b <= "0011111111111111";
        wait;
    end process;

end architecture;