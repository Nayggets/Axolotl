----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/24/2025 06:25:16 PM
-- Design Name: 
-- Module Name: Registers - Behavioral
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

entity Registers is
    Port ( enable : in STD_LOGIC;
           clk  : in STD_LOGIC;
           write_enable : in STD_LOGIC;
           rd : in STD_LOGIC_VECTOR (15 downto 0);
           rd_addr : in STD_LOGIC_VECTOR (3 downto 0);
           rx : out STD_LOGIC_VECTOR (15 downto 0);
           rx_addr : in STD_LOGIC_VECTOR (3 downto 0);
           ry : out STD_LOGIC_VECTOR (15 downto 0);
           ry_addr : in STD_LOGIC_VECTOR (3 downto 0));
end Registers;

architecture Behavioral of Registers is
type registers is array(0 to 15) of std_logic_vector(15 downto 0);
signal reg : registers := (others => X"0000000000000000");
begin

process (clk)
begin
    if rising_edge(clk) and enable='1' then
        rx <= reg(TO_INTEGER(unsigned(rx_addr)));
        ry <= reg(TO_INTEGER(unsigned(ry_addr)));
        if write_enable='1' then
            reg(TO_INTEGER(unsigned(rd_addr))) <= rd;
        end if;
    end if;
end process;

end Behavioral;
