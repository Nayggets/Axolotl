----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/20/2025 03:26:34 PM
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ALU is
    Port ( r1 : in STD_LOGIC_VECTOR (15 downto 0);
           r2 : in STD_LOGIC_VECTOR (15 downto 0);
           aluEnable : in STD_LOGIC;
           branching : in STD_LOGIC;
           selectOp : in STD_LOGIC_VECTOR (2 downto 0);
           shouldBranch : out STD_LOGIC;
           rout : out STD_LOGIC_VECTOR (15 downto 0));
end ALU;

architecture Structural of ALU is
    signal andOut : STD_LOGIC_VECTOR(15 downto 0);
    signal xorOut : STD_LOGIC_VECTOR(15 downto 0);
    signal orOut : STD_LOGIC_VECTOR(15 downto 0);
    signal notOut : STD_LOGIC_VECTOR(15 downto 0);
    signal sllOut : STD_LOGIC_VECTOR(15 downto 0);
    signal slrOut : STD_LOGIC_VECTOR(15 downto 0);
    signal addOut : STD_LOGIC_VECTOR(15 downto 0);
    signal subOut : STD_LOGIC_VECTOR(15 downto 0);
    signal outEq  : STD_LOGIC;
    signal outGt  : STD_LOGIC;
    signal outLt  : STD_LOGIC;

begin
    andOp : entity work.myAnd
        port map( a => r1,
                  b => r2,
                  enable => aluEnable,
                  c => andOut);
    addOp : entity work.Adder 
        port map( a => r1,
                  b => r2,
                  enable => aluEnable,
                  c => addOut);
    subOp : entity work.Substractor
        port map( a => r1,
                  b => r2,
                  enable => aluEnable,
                  c => subOut);
    sllOp : entity work.mySll
        port map( a => r1,
                  b => r2,
                  enable => aluEnable,
                  c => sllOut);
    slrOp : entity work.mySlr
        port map( a => r1,
                  b => r2,
                  enable => aluEnable,
                  c => slrOut);
    xorOp : entity work.myXor
        port map( a => r1,
                  b => r2,
                  enable => aluEnable,
                  c => xorOut);
    orOp : entity work.myOr
        port map( a => r1,
                  b => r2,
                  enable => aluEnable,
                  c => orOut);
    notOp : entity work.myNot
        port map( a => r1,
                  enable => aluEnable,
                  c => notOut);
    
    
    selectMux : entity work.Mux16bit_8To1
        port map( a => addOut,
                  b => subOut,
                  c => xorOut,
                  d => andOut,
                  e => notOut,
                  f => orOut,
                  g => sllOut,
                  h => slrOut,
                  sel => selectOp,
                  rout => rout);
    cmp_eq : entity work.cmp_eq
        port map(
                r1 => r1,
                r2 => r2,
                enable => branching,
                isEq => outEq);
                
    cmp_lt : entity work.cmp_lt
        port map(
                r1 => r1,
                r2 => r2,
                enable => branching,
                isLt => outLt);

    cmp_gt : entity work.cmp_gt
        port map(
                r1 => r1,
                r2 => r2,
                enable => branching,
                isGt => outGt);
                
    Mux4 : entity work.Mux4to1
        port map(
                 a => outEq,
                 b => outLt,
                 c => outGt,
                 d => '1',
                 sel => selectOp(1 downto 0),
                 rout => shouldBranch);
end Structural;
