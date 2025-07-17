#include "Decoder.hpp"


void Decoder::DecodeInstruction(unsigned short binary, Instruction *dst)
{
    dst->opcode = binary >> 12 & 0xFF;

    if(dst->opcode & 0x08 == 0){
        std::cout << "I decode a L instruction" << std::endl;
        this->DecodeLInstruction(binary,dst);
    }
    else if(dst->opcode & 0x12 == 3){
        std::cout << "I decode a J instruction" << std::endl;
        this->DecodeJInstruction(binary,dst);
    }
    else if(binary >> 15 & 0x01 == 1 && binary >> 13 & 0x01 == 1){
        std::cout << "I decode a M instruction" << std::endl;
        this->DecodeMInstruction(binary,dst);
    }
    else{
        std::cout << "I decode a I instruction" << std::endl;
        this->DecodeLInstruction(binary,dst);
    }
}

void Decoder::DecodeLInstruction(unsigned short binary, Instruction *dst)
{

    dst->instruction.instructionL.rd = binary >> 8 & 0xFF;
    dst->instruction.instructionL.rx = binary >> 4 & 0xFF;
    dst->instruction.instructionL.ry = binary & 0xFF;

}

void Decoder::DecodeIInstruction(unsigned short binary, Instruction *dst)
{
    dst->instruction.instructionI.rd= binary >> 8 & 0xFF;
    dst->instruction.instructionI.imm = binary >> 4 & 0xFFFF;
}
void Decoder::DecodeMInstruction(unsigned short binary, Instruction *dst)
{
    dst->instruction.instructionM.rd = binary >> 8 & 0xFF;
    dst->instruction.instructionM.imm = binary >> 4 & 0xFF;
    dst->instruction.instructionM.rx = binary & 0xFF;
}

void Decoder::DecodeJInstruction(unsigned short binary, Instruction *dst)
{
    dst->instruction.instructionJ.rx = binary >> 8 & 0xFF;
    dst->instruction.instructionJ.ry = binary >> 4 & 0xFF;
    dst->instruction.instructionJ.rz = binary & 0xFF;}
