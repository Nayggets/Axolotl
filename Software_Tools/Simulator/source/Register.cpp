#include "Registers.hpp"
#include <cassert>

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



void Registers::setLSBRegister(short index,unsigned char value)
{
    assert(index >= 0 && index < 17);
    this->registers[index] &= (0x00FF);
    this->registers[index] |= value>>8;

}