----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/02/2025 09:56:33 PM
-- Design Name: 
-- Module Name: ALU - Behavioral
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
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ALU is
    Port ( opcode : in STD_LOGIC_VECTOR (3 downto 0);
           execute : in STD_LOGIC;
           r1 : in STD_LOGIC_VECTOR (15 downto 0);
           r2 : in STD_LOGIC_VECTOR (15 downto 0);
           rd : in STD_LOGIC_VECTOR (15 downto 0);
           immediate : in STD_LOGIC_VECTOR (7 downto 0);
           shouldBranch : out STD_LOGIC;
           memoryAccess : out STD_LOGIC;
           loadOrStore : out STD_LOGIC;
           returnOn : out STD_LOGIC;
           result : out STD_LOGIC_VECTOR (15 downto 0);
           executeFinish : out STD_LOGIC) ;
end ALU;

architecture Behavioral of ALU is

begin 
process(execute)
begin        
    if falling_edge(execute) then
        executeFinish <= '0';
    elsif rising_edge(execute) then
    
        shouldBranch <= '0';
        memoryAccess <= '0';
        returnOn <= '0';
        case opcode is
            when "0000" =>
                result <= std_logic_vector(unsigned(r1) + unsigned(r2));
            when "0001" =>
                result <= std_logic_vector(unsigned(r1) - unsigned(r2));
            when "0010" =>
                result <= r1 xor r2;
            when "0011" => 
                result <= r1 and r2;
            when "0100" =>
                result <= not r1;
            when "0101" =>
                result <= r1 or r2;
            when "0110" => 
                result <= std_logic_vector(shift_left(unsigned(r1), to_integer(unsigned(r2))));
            when "0111" => 
                result <= std_logic_vector(shift_right(unsigned(r1), to_integer(unsigned(r2))));
            when "1000" =>
                result(7 downto 0) <= immediate;
                result(15 downto 8) <= rd(15 downto 8);
            when "1001" =>
                --result <= r1 msb imm
                result(15 downto 8) <= immediate;
                result(7 downto 0) <= rd(7 downto 0);
            when "1010" =>
                memoryAccess <= '1';
                result <= std_logic_vector(unsigned(immediate) + unsigned(r2));
                loadOrStore <= '1';
                --memory address calculus imm + rz value
            when "1011" =>
                memoryAccess <= '1';
                result <= std_logic_vector(unsigned(immediate) + unsigned(r2));
                loadOrStore <= '0';

                --memory address calculus imm + rz value
            when "1100" =>
                -- check if r1 equal r2
                -- should branch
                -- result = address of jump
                if rd=r1 then
                    shouldBranch <= '1';
                    result <= r2;
                else
                    --result = rd value nothing change
                    result <= rd;
                end if;
            when "1101" =>
                -- check if r1 < r2
                -- should branch 
                -- result = address of jump
                if rd<r1 then
                    shouldBranch <= '1';
                    result <= r2;
                else
                    result <= rd;
                end if;
            when "1110" =>
                -- check if r1 > r2
                -- should branch 
                -- result = address of jump
                if rd>r1 then 
                    shouldBranch <= '1';
                    result <= r2;
                else 
                    result <= rd;
                end if;
            when "1111" =>
                shouldBranch <= '1';
                returnOn <= '1';
                --return : jump to rv value
        end case;
        executeFinish <= '1';
    end if;
end process;

end Behavioral;
