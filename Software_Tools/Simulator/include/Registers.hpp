#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define R5 4
#define R6 5
#define R7 6
#define R8 7
#define R9 8
#define R10 9
#define R11 10
#define R12 11
#define R13 12
#define R14 13
#define R15 14
#define R16 15
#include <string>
#include <cassert>
#include <iostream>

class Registers
{
    public:
        short getValueRegister(short index);
        void setValueRegister(short index,short value);
        void setLSBRegister(short index,unsigned char value);
        void setMSBRegister(short index,unsigned char value);
        void printRegister();
    private:
        short registers[16];
        static const std::string registerName[16];
};