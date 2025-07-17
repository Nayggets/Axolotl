----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/20/2025 01:42:48 PM
-- Design Name: 
-- Module Name: Not - Behavioral
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

entity myNot is
    Port ( a : in STD_LOGIC_VECTOR (15 downto 0);
           enable : in STD_LOGIC;
           c : out STD_LOGIC_VECTOR (15 downto 0));
end myNot;

architecture Behavioral of myNot is

begin
    process(enable)
    begin
        if enable='1' then
            c <= not a;
        else 
            c <= '0';
        end if;
    end process;
end Behavioral;
