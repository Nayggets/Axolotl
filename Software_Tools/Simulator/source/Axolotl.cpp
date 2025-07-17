#include "Axolotl.hpp"

void Axolotl::Emulate(std::ifstream file)
{
    std::vector<short> content;
    short value;
    while(file.read((char*)&value,2)){
        content.push_back(value);
    }
    assert(content.size() < 65536);
    Instruction toExecute = {0};
    for(short binary : content){
        this->decoder->DecodeInstruction(binary,&toExecute);
        this->Execute(&toExecute);
    }


    //TODO 
    //this.printState();

}

void Axolotl::Execute(Instruction *toExecute)
{
    switch (toExecute->opcode)
    {
    case 0:
        /* code */
        break;
    case 1:
        /* code */
        break;
    case 2:
        /* code */
        break;
    case 3:
        /* code */
        break;
    case 4:
        /* code */
        break;
    case 5:
        /* code */
        break;
    case 6:
        /* code */
        break;
    case 7:
        /* code */
        break;
    case 8:
        /* code */
        break;
    case 9:
        /* code */
        break;
    case 10:
        /* code */
        break;
    case 11:
        /* code */
        break;
    case 12:
        /* code */
        break;
    case 13:
        /* code */
        break;
    case 14:
        /* code */
        break;
    case 15:
        /* code */
        break;
    default:
        break;
    }
}

void Axolotl::ExecuteAdd(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) - this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
}
void Axolotl::ExecuteSub(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) - this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
}
void Axolotl::ExecuteXor(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) ^ this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
}
void Axolotl::ExecuteAnd(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) & this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
}
void Axolotl::ExecuteNot(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,~this->registers->getValueRegister(toExecute->instruction.instructionL.rx));
}
void Axolotl::ExecuteOr(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) | this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
}
void Axolotl::ExecuteSll(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) << this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
}
void Axolotl::ExecuteSlr(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) >> this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
}
void Axolotl::ExecuteLoadLSB(Instruction* toExecute)
{
    this->registers->setLSBRegister(toExecute->instruction.instructionI.rd,toExecute->instruction.instructionI.imm);

}
void Axolotl::ExecuteLoadMSB(Instruction* toExecute)
{
    this->registers->setMSBRegister(toExecute->instruction.instructionI.rd,toExecute->instruction.instructionI.imm);
}
void Axolotl::ExecuteMemStore(Instruction* toExecute)
{
    this->mem->setValue(this->registers->getValueRegister(toExecute->instruction.instructionM.rx),this->registers->getValueRegister(toExecute->instruction.instructionM.rd)+toExecute->instruction.instructionM.imm);
}
void Axolotl::ExecuteMemLoad(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionM.rd,this->mem->getValue(this->registers->getValueRegister(toExecute->instruction.instructionM.rx)+toExecute->instruction.instructionM.imm));
}
void Axolotl::ExecuteJe(Instruction* toExecute)
{

}
void Axolotl::ExecuteJlt(Instruction* toExecute)
{

}
void Axolotl::ExecuteJgt(Instruction* toExecute)
{

}
void Axolotl::ExecuteRet(Instruction* toExecute)
{

}
