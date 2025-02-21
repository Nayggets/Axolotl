----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/20/2025 02:41:37 PM
-- Design Name: 
-- Module Name: ProgramCounter - Behavioral
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

entity ProgramCounter is
    Port ( load : in STD_LOGIC;
           loadValue : in STD_LOGIC_VECTOR (15 downto 0);
           clk : in STD_LOGIC;
           inc : in STD_LOGIC;
           PC : out STD_LOGIC_VECTOR (15 downto 0);
           deb : out STD_LOGIC);
end ProgramCounter;

architecture Behavioral of ProgramCounter is
    signal internal_counter : unsigned (15 downto 0);
begin
    process(clk)
    begin
        if rising_edge(clk) then
            if load='1' then
                internal_counter <= unsigned(loadValue);
            elsif inc='1' then
                if internal_counter="111111111111111111" then
                    internal_counter <= (others => '0');
                else 
                    internal_counter <= internal_counter+1;
                end if;
            end if;
        end if;
    end process;
    PC <= std_logic_vector(internal_counter);
end Behavioral;
