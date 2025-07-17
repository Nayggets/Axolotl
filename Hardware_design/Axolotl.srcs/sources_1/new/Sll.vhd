----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/20/2025 01:42:48 PM
-- Design Name: 
-- Module Name: Sll - Behavioral
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

entity mySll is
    Port ( a : in STD_LOGIC_VECTOR (15 downto 0);
           b : in STD_LOGIC_VECTOR (15 downto 0);
           enable : in STD_LOGIC;
           c : out STD_LOGIC_VECTOR (15 downto 0));
end mySll;

architecture Behavioral of mySll is

begin
    process(enable)
    begin
        if enable='1' then
            c <= std_logic_vector(shift_left(unsigned(a),to_integer(unsigned(b))));
        else
            c <= (others => '0');
        end if;
    end process;

end Behavioral;
