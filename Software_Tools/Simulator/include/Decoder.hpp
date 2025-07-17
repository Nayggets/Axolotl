#include <iostream>

class Decoder
{
    public:
        void DecodeInstruction(unsigned short binary,Instruction* dst);
    private:
        void DecodeLInstruction(unsigned short binary, Instruction* dst);
        void DecodeIInstruction(unsigned short binary, Instruction* dst);
        void DecodeMInstruction(unsigned short binary, Instruction* dst);
        void DecodeJInstruction(unsigned short binary, Instruction* dst);
};


struct Instruction
{
    unsigned short opcode : 4;
    union typeInstruction
    {
        LTypeInstruction instructionL;
        ITypeInstruction instructionI;
        JTypeInstruction instructionJ;
        MTypeInstruction instructionM;
    } instruction;
    
    
};


struct LTypeInstruction
{
    unsigned short rd : 4;
    unsigned short rx : 4;
    unsigned short ry : 4;
};

struct ITypeInstruction
{
    unsigned short rd : 4;
    unsigned short imm : 8;
};

struct MTypeInstruction
{
    unsigned short rd : 4;
    unsigned short imm : 4;
    unsigned short rx : 4;
};


struct JTypeInstruction
{
    unsigned short rx : 4;
    unsigned short ry : 4;
    unsigned short rz : 4;
};
