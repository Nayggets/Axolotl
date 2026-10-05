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
    Port ( writeBack : in STD_LOGIC;
           rd : in STD_LOGIC_VECTOR (15 downto 0);
           r1_addr : in STD_LOGIC_VECTOR (3 downto 0);
           r2_addr : in STD_LOGIC_VECTOR (3 downto 0);
           rd_addr : in STD_LOGIC_VECTOR (3 downto 0);
           wr_rv : in STD_LOGIC;
           rv_in : in STD_LOGIC_VECTOR (15 downto 0);
           rv_out : out STD_LOGIC_VECTOR(15 downto 0);
           r1 : out STD_LOGIC_VECTOR (15 downto 0); 
           r2 : out STD_LOGIC_VECTOR (15 downto 0);
           rd_out : out STD_LOGIC_VECTOR (15 downto 0);
           writeBackFinish : out STD_LOGIC);

end Registers;

architecture Behavioral of Registers is
type registers is array(0 to 15) of std_logic_vector(15 downto 0);
signal reg : registers := (others => X"0000000000000000");
begin


 r1 <= reg(TO_INTEGER(unsigned(r1_addr)));
 r2 <= reg(TO_INTEGER(unsigned(r2_addr)));
 rd_out <= reg(TO_INTEGER(unsigned(rd_addr)));
 
 process(writeBack)
 begin 
    if falling_edge(writeBack) then
        writeBackFinish <= '0';  
    elsif rising_edge(writeBack) then
        reg(TO_INTEGER(unsigned(rd_addr))) <= rd;
        if wr_rv='1' then
            reg(1) <= rv_in;
        end if;
        writeBackFinish <= '1';
    end if;
end process;

end Behavioral;
