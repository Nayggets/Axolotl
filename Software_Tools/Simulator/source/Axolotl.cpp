#include "Axolotl.hpp"

void Axolotl::Emulate(std::ifstream& file)
{
    std::vector<short> content;
    short value;
    while(file.read((char*)&value,2)){
        content.push_back(value);
    }
    assert(content.size() < 65536 && content.size() > 0);
    Instruction toExecute = {0};
    

    int i = 0;
    for(short binary : content){
        this->mem->setValue(binary,i);
        i++;
    }
    short command = this->mem->getValue(0);
    while(!this->stopped){
        this->decoder->DecodeInstruction(command,&toExecute);
        this->Execute(&toExecute);
        command = this->mem->getValue(this->PC);
        this->printState();
        usleep(100000);

    }


    this->printState();

}

void Axolotl::Execute(Instruction *toExecute)
{
    PC++;
    switch (toExecute->opcode)
    {
    case 0:
        this->ExecuteAdd(toExecute);
        break;
    case 1:
        this->ExecuteSub(toExecute);
        break;
    case 2:
        this->ExecuteXor(toExecute);
        /* code */
        break;
    case 3:
        this->ExecuteAnd(toExecute);
        /* code */
        break;
    case 4:
        this->ExecuteNot(toExecute);
        /* code */
        break;
    case 5:
        this->ExecuteOr(toExecute);
        /* code */
        break;
    case 6:
        this->ExecuteSll(toExecute);
        /* code */
        break;
    case 7:
        this->ExecuteSlr(toExecute);
        /* code */
        break;
    case 8:
        this->ExecuteLoadLSB(toExecute);
        /* code */
        break;
    case 9:
        this->ExecuteLoadMSB(toExecute);
        /* code */
        break;
    case 10:
        this->ExecuteMemStore(toExecute);
        /* code */
        break;
    case 11:
        this->ExecuteMemLoad(toExecute);
        /* code */
        break;
    case 12:
        this->ExecuteJe(toExecute);
        /* code */
        break;
    case 13:
        this->ExecuteJlt(toExecute);
        /* code */
        break;
    case 14:
        this->ExecuteJgt(toExecute);
        /* code */
        break;
    case 15:
        this->ExecuteRet(toExecute);
        /* code */
        break;
    default:
        break;
    }
}

void Axolotl::ExecuteAdd(Instruction* toExecute)
{
    this->registers->setValueRegister(toExecute->instruction.instructionL.rd,this->registers->getValueRegister(toExecute->instruction.instructionL.rx) + this->registers->getValueRegister(toExecute->instruction.instructionL.ry));
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
    std::cout << "Execute Je with : " << "rx value : " << this->registers->getValueRegister(toExecute->instruction.instructionJ.rx) << " ry value : " << this->registers->getValueRegister(toExecute->instruction.instructionJ.ry)  << " rz value : " << this->registers->getValueRegister(toExecute->instruction.instructionJ.rz) << std::endl;
    if(toExecute->instruction.instructionJ.rx == 15 && toExecute->instruction.instructionJ.rx == toExecute->instruction.instructionJ.ry && toExecute->instruction.instructionJ.rx == toExecute->instruction.instructionJ.rz){
        std::cout << "Programmed stopped" << toExecute->instruction.instructionJ.rx << std::endl;
        stopped = true;
    }
    else if(this->registers->getValueRegister(toExecute->instruction.instructionJ.rx) == this->registers->getValueRegister(toExecute->instruction.instructionJ.ry)){
        std::cout << "JE executed" << std::endl;
        this->PC = this->registers->getValueRegister(toExecute->instruction.instructionJ.rz);
        this->registers->setValueRegister(R2,PC);
    }
    
}
void Axolotl::ExecuteJlt(Instruction* toExecute)
{
    if(this->registers->getValueRegister(toExecute->instruction.instructionJ.rx) < this->registers->getValueRegister(toExecute->instruction.instructionJ.ry)){
        std::cout << "JTL done" << std::endl;
        this->PC = this->registers->getValueRegister(toExecute->instruction.instructionJ.rz);
        this->registers->setValueRegister(R2,PC);
    }
}
void Axolotl::ExecuteJgt(Instruction* toExecute)
{
    if(this->registers->getValueRegister(toExecute->instruction.instructionJ.rx) > this->registers->getValueRegister(toExecute->instruction.instructionJ.ry)){
        std::cout << "JGT done" << std::endl;
        this->PC = this->registers->getValueRegister(toExecute->instruction.instructionJ.rz);
        this->registers->setValueRegister(R2,PC);
    }
}
void Axolotl::ExecuteRet(Instruction* toExecute)
{
    this->PC = this->registers->getValueRegister(R2);
}

void Axolotl::printState()
{
    this->registers->printRegister();
}
