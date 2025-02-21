library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

entity Or_tb is

end entity;


architecture Behavioral of Or_tb is
    signal a : STD_LOGIC_VECTOR(15 downto 0);
    signal b : STD_LOGIC_VECTOR(15 downto 0);
    signal c : STD_LOGIC_VECTOR(15 downto 0);
begin
    
    inst_Or : entity work.myOr
        port map( a => a,
                  b => b,
                  c => c);

    test_process : process
    begin
        a <= "1110000000000000";
        b <= "1011111111111111";
        wait;
    end process;

end architecture;