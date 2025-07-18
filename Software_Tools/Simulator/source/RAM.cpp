#include "RAM.hpp"        
#include <cassert>
RAM::RAM()
{
}
short RAM::getValue(short index)
{
    assert(index >= 0 && index < 65536);
    return this->mem[index];
}


void RAM::setValue(short value,short index)
{
    assert(index >= 0 && index < 65536);
    this->mem[index] = value;
}
