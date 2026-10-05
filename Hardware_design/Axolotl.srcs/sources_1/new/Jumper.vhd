----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/04/2025 01:48:35 PM
-- Design Name: 
-- Module Name: Jumper - Behavioral
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

entity Jumper is
    Port ( enable : in STD_LOGIC;
           shouldJump : in STD_LOGIC;
           addressToJump : in STD_LOGIC_VECTOR(15 downto 0);
           writeBackFinish : out STD_LOGIC);
end Jumper;

architecture Behavioral of Jumper is

begin


end Behavioral;
