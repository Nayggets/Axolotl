----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/11/2025 10:34:04 AM
-- Design Name: 
-- Module Name: RAM - Behavioral
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

entity RAM is
    Port ( rw : in STD_LOGIC;
           memoryAccess : in STD_LOGIC;
           rst : in STD_LOGIC;
           addr : in std_logic_vector(15 downto 0); 
           write_buffer : in STD_LOGIC_VECTOR (15 downto 0);
           read_buffer : out STD_LOGIC_VECTOR (15 downto 0);
           memoryAccessFinish : out STD_LOGIC);

end RAM;

architecture Behavioral of RAM is
type mem is array(0 to 65535) of std_logic_vector(15 downto 0);
signal ram : mem;
begin

process(rst)
begin
    if rising_edge(rst) then
            ram <= (others => (others => '0'));
    end if;
end process;

process(memoryAccess)
begin
    if falling_edge(memoryAccess) then
        memoryAccessFinish <= '0';
    elsif rising_edge(memoryAccess) then
        
        if rw='1'then
            ram(TO_INTEGER(unsigned(addr))) <= write_buffer;
        end if;
        memoryAccessFinish <= '1';
    end if;

end process;
read_buffer <= ram(TO_INTEGER(unsigned(addr)));
end Behavioral;
