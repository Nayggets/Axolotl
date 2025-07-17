----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 03/18/2025 07:30:34 PM
-- Design Name: 
-- Module Name: Processor - Behavioral
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

entity Processor is
    Port ( clk : in STD_LOGIC;
           instruction : in STD_LOGIC_VECTOR (15 downto 0);
           enable : in STD_LOGIC);
end Processor;

architecture Behavioral of Processor is
    signal AluOp : STD_LOGIC_VECTOR(2 downto 0);
    signal AluEnable : STD_LOGIC;
    signal immediate : STD_LOGIC_VECTOR(7 downto 0);
    signal reg_write : STD_LOGIC;
    signal rd_select : STD_LOGIC_VECTOR (3 downto 0);
    signal rx_select : STD_LOGIC_VECTOR (3 downto 0);
    signal ry_select : STD_LOGIC_VECTOR (3 downto 0);
begin
    uut_decoder : entity work.Decodeur port map(
           Instruction => instruction,
           clk => clk,
           enable => enable,
           AluOp => AluOp,
           AluEnable => AluEnable,
           immediate => immediate,
           reg_write => reg_write,
           rd_select => rd_select,
           rx_select => rx_select,
           ry_select => ry_select
    );

end Behavioral;
