#include "Registers.hpp"
const std::string Registers::registerName[16] = {"R1","R2","R3","R4","R5","R6","R7","R8","R9","R10","R11","R12","R13","R14","R15","R16"};

short Registers::getValueRegister(short index)
{
    assert(index >= 0 && index < 17);
    return this->registers[index];
}
void Registers::setValueRegister(short index,short value)
{
    assert(index >= 0 && index < 17);
    this->registers[index] = value;
}


void Registers::setLSBRegister(short index,unsigned char value)
{
    assert(index >= 0 && index < 17);
    this->registers[index] &= (0xFF00);
    this->registers[index] |= value;
}



void Registers::setMSBRegister(short index,unsigned char value)
{
    assert(index >= 0 && index < 17);
    this->registers[index] &= (0x00FF);
    this->registers[index] |= value<<8;

}

void Registers::printRegister()
{
    for(int i = 0 ; i < 16 ; i++){
        std::cout << registerName[i] << " : " << this->registers[i] << std::endl;
    }
}
