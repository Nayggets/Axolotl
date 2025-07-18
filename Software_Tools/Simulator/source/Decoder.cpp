#include "Decoder.hpp"

Decoder::Decoder()
{
}

void Decoder::DecodeInstruction(unsigned short binary, Instruction *dst)
{
    dst->opcode = binary >> 12 & 0xFF;
    std::cout << (dst->opcode & 0x08) << std::endl;
    if((dst->opcode & 0x08) == 0){
        std::cout << "I decode a L instruction" << std::endl;
        this->DecodeLInstruction(binary,dst);
    }
    else if((dst->opcode & 12) == 12){
        std::cout << "I decode a J instruction" << std::endl;
        this->DecodeJInstruction(binary,dst);
    }
    else if((dst->opcode & 0x01) == 1 && ((dst->opcode >> 2) & 0x01) == 1){
        std::cout << "I decode a M instruction" << std::endl;
        this->DecodeMInstruction(binary,dst);
    }
    else{
        std::cout << "I decode a I instruction" << std::endl;
        this->DecodeIInstruction(binary,dst);
    }
}

void Decoder::DecodeLInstruction(unsigned short binary, Instruction *dst)
{

    dst->instruction.instructionL.rd = binary >> 8 & 0xFF;
    dst->instruction.instructionL.rx = binary >> 4 & 0xFF;
    dst->instruction.instructionL.ry = binary & 0xFF;
    std::cout << "LInstruction : " << dst->instruction.instructionL.rd << " " <<
    dst->instruction.instructionL.rx << " " << dst->instruction.instructionL.ry << std::endl;
}

void Decoder::DecodeIInstruction(unsigned short binary, Instruction *dst)
{
    dst->instruction.instructionI.rd= binary >> 8 & 0xF;
    dst->instruction.instructionI.imm = binary & 0xFF;
    std::cout << "LInstruction : " << dst->instruction.instructionI.rd << " " <<dst->instruction.instructionI.imm << std::endl;
}
void Decoder::DecodeMInstruction(unsigned short binary, Instruction *dst)
{
    dst->instruction.instructionM.rd = binary >> 8 & 0xFF;
    dst->instruction.instructionM.imm = binary >> 4 & 0xFF;
    dst->instruction.instructionM.rx = binary & 0xFF;
    std::cout << "MInstruction : " << dst->instruction.instructionM.rd << " " <<
    dst->instruction.instructionM.imm << " " << dst->instruction.instructionM.rx << std::endl;
}

void Decoder::DecodeJInstruction(unsigned short binary, Instruction *dst)
{
    dst->instruction.instructionJ.rx = binary >> 8 & 0xFF;
    dst->instruction.instructionJ.ry = binary >> 4 & 0xFF;
    dst->instruction.instructionJ.rz = binary & 0xFF;
    std::cout << "JInstruction : " << dst->instruction.instructionJ.rx << " " <<
    dst->instruction.instructionJ.ry << " " << dst->instruction.instructionJ.rz << std::endl;
}
