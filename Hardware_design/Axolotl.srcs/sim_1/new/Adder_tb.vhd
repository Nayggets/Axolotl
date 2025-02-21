----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/11/2025 02:18:22 PM
-- Design Name: 
-- Module Name: Adder_tb - Behavioral
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity Adder_tb is
--  Port ( );
end Adder_tb;

architecture Behavioral of Adder_tb is
    component Adder
    Port (
       a : in STD_LOGIC_VECTOR (15 downto 0);
       b : in STD_LOGIC_VECTOR (15 downto 0);
       c : out STD_LOGIC_VECTOR (15 downto 0);
       carry : out STD_LOGIC);
    end component;
    signal a      : std_logic_vector (15 downto 0);
    signal b      : std_logic_vector (15 downto 0);
    signal c      : std_logic_vector (15 downto 0);
    signal carry  : STD_LOGIC := '0';
begin
    inst_adder : Adder
    port map(
        a => a,
        b => b,
        c => c,
        carry => carry);
    
    test_adder_process : process
    begin
        a <= "1111111111111111";
        b <= "1111111111111111";
        wait for 5 ps;
        a <= "0000000000000001";
        b <= "0000000000000001";
        wait for 5 ps;
        a <= "0000000000000111";
        b <= "0000000000000000";
        wait for 5 ps;
        wait;
    end process;
        

end Behavioral;
