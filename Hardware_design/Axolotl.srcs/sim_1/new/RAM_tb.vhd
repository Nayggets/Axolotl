----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/11/2025 10:54:10 AM
-- Design Name: 
-- Module Name: RAM_tb - Behavioral
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

entity RAM_tb is
--  Port ( );
end RAM_tb;

architecture Behavioral of RAM_tb is
    component RAM
    Port ( rw : in STD_LOGIC;
           rst : in STD_LOGIC;
           clk : in STD_LOGIC;
           addr : in std_logic_vector(15 downto 0); 
           write_buffer : in STD_LOGIC_VECTOR (15 downto 0);
           read_buffer : out STD_LOGIC_VECTOR (15 downto 0));
    end component;
    signal rw : STD_LOGIC;
    signal rst : std_logic;
    signal clk : std_logic;
    signal addr : std_logic_vector(15 downto 0);
    signal write_buffer : STD_LOGIC_VECTOR(15 downto 0);
    signal read_buffer : STD_LOGIC_VECTOR(15 downto 0);
begin
    my_ram : RAM
    port map(
        rw => rw,
        rst => rst,
        clk => clk,
        addr => addr,
        write_buffer => write_buffer,
        read_buffer => read_buffer);
        
    clk_process : process
    begin 
        clk <= '0';
        wait for 5 ns;
        clk <= '1';
        wait for 5 ns;
    end process;
    
    test_ram : process
    begin
        rst <= '1';
        rw <= '0';
        rw <= '0';
        write_buffer <= x"0000";
        addr <= "0000000000000000";
        wait for 10 ns;
        rst <= '0';
        rw <= '1';
        for i in 0 to 65535 loop
            write_buffer <= std_logic_vector(TO_UNSIGNED(i,16));
            addr <= std_logic_vector(TO_UNSIGNED(i,16));
            wait for 10 ns;
        end loop;
        write_buffer <= x"5200";
        addr <= "1110000000000000";
        wait for 10 ns;
        addr <= "1111000000000000";
        write_buffer <= x"ff00";
        wait for 10 ns;
        rw <= '0';
        addr <= "1110000000000000";
        write_buffer <= x"5200";
        wait for 10 ns;
        addr <= "1111000000000000";
        for i in 0 to 65535 loop
            addr <= std_logic_vector(TO_UNSIGNED(i,16));
            wait for 10 ns;
        end loop;
        wait;
     end process;
        
        
    

end Behavioral;
