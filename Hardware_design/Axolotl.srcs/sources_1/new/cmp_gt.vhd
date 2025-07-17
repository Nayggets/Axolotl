----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/25/2025 08:00:34 AM
-- Design Name: 
-- Module Name: cmp_gt - Behavioral
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

entity cmp_gt is
    Port ( r1 : in STD_LOGIC_VECTOR (15 downto 0);
           r2 : in STD_LOGIC_VECTOR (15 downto 0);
           enable : in STD_LOGIC;
           isGt : out STD_LOGIC);
end cmp_gt;

architecture Behavioral of cmp_gt is

begin
    process(enable)
    begin
        if enable='1' then
            if unsigned(r1) > unsigned(r2) then
                isGt <= '1';
            else 
                isGt <= '0';
            end if;
        else
            isGt <= '0';
        end if;
    end process;


end Behavioral;
