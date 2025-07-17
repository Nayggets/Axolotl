# Axolotl

## Instruction set architecture

### L type

L type is a group of logical instruction it regroup all the instruction to do logical calculus.

### I type

I type is a group of logical instruction to set a immediate value to a register

### M type

M type is a group of logical instruction to access the Memory (write or read)

### J type

J type is a group of instruction to do branching or calling function.

### Table of instruction

| Instruction             | type | binary              | Utility                                                                       |
| ----------------------- | ---- | ------------------- | ----------------------------------------------------------------------------- |
| add rd,rx,ry            | L    | 0000 brd brx bry    | rd = rx +ry                                  if(rx+ry > 2^(16)) carry = 1     |
| sub rd,rx,ry            | L    | 0001 brd brx bry    | rd = rx - ry                                    if(rx - ry < -2^(15)) deb = 1 |
| xor rd,rx,ry            | L    | 0010 brd brx bry    | rd = rx xor ry                                                                |
| and rd,rx,ry            | L    | 0011 brd brx bry    | rd = rx and ry                                                                |
| not rd,rx               | L    | 0100 brd brx 0000   | rd = !rx                                                                      |
| or rd,rx,ry             | L    | 0101 brd brx bry    | rd = rx or ry                                                                 |
| sll rd,rx,ry            | L    | 0110 brd brx bry    | rd = rx << ry                                                                 |
| slr rd,rx,ry            | L    | 0111 brd brx bry    | rd = rx >> ry                                                                 |
| load_lsb rd, imm[8bits] | I    | 1000 brd bimm       | rd[7:0] = imm                                                                 |
| load_msb rd, imm[8bits] | I    | 1001 brd bimm       | rd[15:8] = imm                                                                |
| mem_store rd,imm(rx)    | M    | 1010 brd bimm brx   | mem[rx+imm] = rd                                                              |
| mem_load rd,imm(rx)     | M    | 1011 brd bimm brx   | rd = mem[rx+imm]                                                              |
| je rd,rx,ry             | J    | 1100 brx bry brz    | if(rx==ry) R2 = pc ; pc = rd                                                  |
| jlt rd,rx,ry            | J    | 1101 0000 0000 brz  | if(rx < ry) R2 = pc ; pc = rd                                                 |
| jgt rd,rx,ry            | J    | 1110 brx bry brz    | if(rx > ry ) R2=pc ; pc = rd                                                  |
| `ret`                   | J    | 1111 0000 0000 0000 | pc = R2                                                                       |

## Pseudo instruction

| pseudo Instruction | Axolotl instruction equivalent             | Utility                               |
| ------------------ | ------------------------------------------ | ------------------------------------- |
| set rd,imm         | load_lsb rd,imm[7:0] load_msb rd,imm[15:8] | rd = imm                              |
| mul rd,rx,ry       | ...                                        | rd = rx * ry                          |
| div rd,rx,ry       | ...                                        | rd = rx / ry                          |
| mod rd, rx ,ry     | ...                                        | rd = rx % ry                          |
| hlt                | set R16,halt halt: je R16,R16,R16          | set the processor in an infinite loop |

## Register

| Registe | Description                                 | Name | Binary | Saver   |
| ------- | ------------------------------------------- | ---- | ------ | ------- |
| R1      | Stack pointeur use to handle the stack      | sp   | 0000   | Callee  |
| R2      | Return addresse use for the ret instruction | ra   | 0001   | Callee  |
| R3      | Argument 0 of function                      | a0   | 0010   | Context |
| R4      | Argument 1 of function                      | a1   | 0011   | Context |
| R5      | Argument 2 of function                      | a2   | 0100   | Context |
| R6      | Argument 3 of function                      | a3   | 0101   | Context |
| R7      | Return Value                                | rv   | 0110   | Caller  |
| R8      | Temporary 0                                 | t0   | 0111   | Caller  |
| R9      | Temporary 1                                 | t1   | 1000   | Caller  |
| R10     | Temporary 2                                 | t2   | 1001   | Caller  |
| R11     | Temporary 3                                 | t3   | 1010   | Caller  |
| R12     | Temporary 4                                 | t4   | 1011   | Caller  |
| R13     | Temporary 5                                 | t5   | 1100   | Caller  |
| R14     | Temporary 6                                 | t6   | 1101   | Caller  |
| R15     | Jump Value1                                 | j1   | 1110   | ---     |
| R16     | Jump Value2                                 | j2   | 1111   | ---     |

NB : if you have more than 4 arguments for a function you have to use the stack.

Imagine that we have 7 arguments we will have to use the stack this way.

| Stack                                |
| ------------------------------------ |
| Argument 6                           |
| Argument 5                           |
| Argument 4                           |
| Argument 3                           |
| Argument 2                           |
| Argument 1                           |
| Argument 0                           |
| "Nothing" <--Stack pointeur position |

NB : the stack pointeur is decrementing not incrementing. 
