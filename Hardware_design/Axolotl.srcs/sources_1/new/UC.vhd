----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 09/02/2025 03:25:21 PM
-- Design Name: 
-- Module Name: UC - Behavioral
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

entity UC is
    Port ( clk : in STD_LOGIC;
           reset : in STD_LOGIC;
           fetchFinish : in STD_LOGIC;
           decodeFinish : in STD_LOGIC;
           executeFinish : in STD_LOGIC;
           memoryAccessFinish : in STD_LOGIC;
           writeBackFinish : in STD_LOGIC;
           fetchStart : out STD_LOGIC;
           decodeStart : out STD_LOGIC;
           executeStart : out STD_LOGIC;
           memoryAccessStart : out STD_LOGIC;
           writeBackStart : out STD_LOGIC);
end UC;

architecture Behavioral of UC is

    type processorState is (FETCH,DECODE,EXECUTE,MEMORYACCESS,WRITEBACK);
    signal currentState : processorState;
    signal nextState : processorState;
    

begin


process(clk)
    begin
        if rising_edge(clk) then currentState <= nextState;
        end if;
end process;

process(currentState)
    begin 
       nextState <= currentState;
       fetchStart <= '0';
       decodeStart <= '0';
       executeStart <= '0';
       memoryAccessStart <= '0';
       writeBackStart <= '0';
        case currentState is
            when FETCH =>
                if fetchFinish = '1' then
                    nextState <= DECODE;
                    decodeStart <= '1';
                    fetchStart <= '0';
                end if;
            when DECODE => 
                if decodeFinish = '1' then
                    nextState <= EXECUTE;
                    executeStart <= '1';
                    decodeStart <= '0';
                end if;
            when EXECUTE =>
                if executeFinish = '1' then
                    nextState <= MEMORYACCESS;
                    memoryAccessStart <= '1';
                    executeStart <= '0';
                end if;
            when MEMORYACCESS =>
                if memoryAccessFinish = '1' then
                    nextState <= WRITEBACK;
                    writeBackStart  <= '1';
                    memoryAccessStart <= '0';
                end if;
            when WRITEBACK =>
                if writeBackFinish = '1' then
                    nextState <= FETCH;
                    fetchStart <= '1';
                    writeBackStart <= '0';
                end if;
       end case;
end process;
end Behavioral;
