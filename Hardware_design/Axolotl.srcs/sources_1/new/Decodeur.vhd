----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/24/2025 08:33:13 PM
-- Design Name: 
-- Module Name: Decodeur - Behavioral
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

entity Decodeur is
    Port ( Instruction : in STD_LOGIC_VECTOR (15 downto 0);
           clk : in STD_LOGIC;
           enable : in STD_LOGIC;
           AluOp : out STD_LOGIC_VECTOR (2 downto 0);
           AluEnable : out STD_LOGIC;
           immediate : out STD_LOGIC_VECTOR (7 downto 0);
           reg_write : out STD_LOGIC;
           rd_select : out STD_LOGIC_VECTOR (3 downto 0);
           rx_select : out STD_LOGIC_VECTOR (3 downto 0);
           ry_select : out STD_LOGIC_VECTOR (3 downto 0));
end Decodeur;

architecture Behavioral of Decodeur is

begin
   
process(clk)
begin
    if rising_edge(clk) and enable='1' then
        AluOp <= Instruction(14 downto 12);
        AluEnable <= not Instruction(15);
        ry_select <= Instruction(3 downto 0);
        rx_select <= Instruction(7 downto 4);
        rd_select <= Instruction(11 downto 8);
        if instruction(15 downto 12)="1010" or instruction(15 downto 12)="1011" then
            AluEnable <= '0';
        else
            AluEnable <= '1';
        end if;
        if instruction(15)='0' then 
            reg_write <= '1';
            immediate <= (others => '0');
        elsif instruction(15 downto 12)="1000" or instruction(15 downto 12)="1001" then
            reg_write <= '1';
            immediate <= Instruction(7 downto 0);
        else
            immediate <= (others => '0');
            reg_write <= '0';
        end if;
    end if;
end process;
end Behavioral;
