----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/21/2025 09:08:50 AM
-- Design Name: 
-- Module Name: Mux16bit_8-1 - Behavioral
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

entity Mux16bit_8To1 is
    Port ( a : in STD_LOGIC_VECTOR (15 downto 0);
           b : in STD_LOGIC_VECTOR (15 downto 0);
           c : in STD_LOGIC_VECTOR (15 downto 0);
           d : in STD_LOGIC_VECTOR (15 downto 0);
           e : in STD_LOGIC_VECTOR (15 downto 0);
           f : in STD_LOGIC_VECTOR (15 downto 0);
           g : in STD_LOGIC_VECTOR (15 downto 0);
           h : in STD_LOGIC_VECTOR (15 downto 0);
           sel : in STD_LOGIC_VECTOR (2 downto 0);
           rout : out STD_LOGIC_VECTOR (15 downto 0));
end Mux16bit_8To1;

architecture Behavioral of Mux16bit_8To1 is
    
begin
with sel select
    rout <= a when "000",
            b when "001",
            c when "010",
            d when "011",
            e when "100",
            f when "101",
            g when "110",
            h when "111";
end Behavioral;
