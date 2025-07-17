----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/21/2025 02:34:10 PM
-- Design Name: 
-- Module Name: And_tb - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.numeric_std.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity And_tb is
--  Port ( );
end And_tb;

architecture Behavioral of And_tb is
    signal a : STD_LOGIC_VECTOR(15 downto 0);
    signal b : STD_LOGIC_VECTOR(15 downto 0);
    signal c : STD_LOGIC_VECTOR(15 downto 0);
begin
    inst_and : entity work.myAnd
        port map( a => a,
                  b => b,
                  c => c);

    test_process : process
    begin
        a <= "1110000000000000";
        b <= "1011111111111111";
        ASSERT( c = "1010000000000000") REPORT "Test 1 échoué : 1110000000000000 & 1011111111111111 != " & integer'image(to_integer(unsigned(c))) SEVERITY ERROR;
        REPORT "And_tb tous les tests passé" SEVERITY NOTE;
        wait;
        
    end process;
        

end Behavioral;
