#include "AST.hpp"


///////////////////////////////////////////////////
// Program Node
///////////////////////////////////////////////////

ASTProgNode::ASTProgNode()
{
    
}


ASTProgNode::~ASTProgNode()
{
    for(auto prog : this->programs){
        delete(prog);
    }
}

void ASTProgNode::addNode(IAST* iast)
{
    this->programs.push_back(iast);
}

int ASTProgNode::updateLabel(std::map<std::string, uint32_t>& labelTable)
{
    for(auto& astNode : this->programs){
        if(typeid(*astNode) == typeid(ASTITypeInstructionNode) ){
            ASTITypeInstructionNode* ast = (ASTITypeInstructionNode*)astNode;
            std::string* label = ast->getTempLabel();
        
            if(label != nullptr){
                if(labelTable.count(*label+":") == 0){
                    std::cerr << "Label use in Instruction";
                    std::cerr << " but never declared : " << *label << std::endl;
                    return -1;
                }
                ast->update(labelTable[*label+":"]);
            }
        }
    }
    return 0;
}

IAST *ASTProgNode::getChildren(int index)
{
    if(index < this->programs.size()){
        return this->programs.at(index);
    }
    return nullptr;
}

void ASTProgNode::print()
{
    std::cout << "(Prog Node : ";
    for(auto* program : this->programs){
        std::cout << "entree dans la boucle" << std::endl;
        program->print();
        std::cout << "\n";
    }
    std::cout << ")";
}

///// J type instruction

ASTJTypeInstructionNode::ASTJTypeInstructionNode(ASTTerminalNodeInstruction* instruction,ASTTerminalNodeRegister* rx,ASTTerminalNodeRegister* ry,ASTTerminalNodeRegister* rz)
{
    this->instruction = std::unique_ptr<ASTTerminalNodeInstruction>(std::move(instruction));
    this->rx = std::unique_ptr<ASTTerminalNodeRegister>(rx);
    this->ry = std::unique_ptr<ASTTerminalNodeRegister>(ry);
    this->rz = std::unique_ptr<ASTTerminalNodeRegister>(rz);

}

ASTJTypeInstructionNode::~ASTJTypeInstructionNode()
{

}

void ASTJTypeInstructionNode::print()
{
    std::cout << "(J Type instruction Node : ";
    this->instruction->print();
    this->rx->print();
    this->ry->print();
    this->rz->print();
    std::cout << ")";
}

IAST *ASTJTypeInstructionNode::getChildren(int index)
{
    switch (index)
    {
    case 0:
        /* code */
        return instruction.get();
        break;
    case 1:
        /* code */
        return this->rx.get();
        break;
    case 2:
        /* code */
        return this->ry.get();
        break;
    case 3:
        /* code */
        return this->rz.get();
        break;
    
    default:
        break;
    }
    return nullptr;
}

//// L type instruction

ASTLTypeInstructionNode::ASTLTypeInstructionNode(ASTTerminalNodeInstruction* instruction,ASTTerminalNodeRegister* rd, ASTTerminalNodeRegister* rx, ASTTerminalNodeRegister* ry)
{
    this->instruction = std::unique_ptr<ASTTerminalNodeInstruction>(instruction);
    this->rd = std::unique_ptr<ASTTerminalNodeRegister>(rd);
    this->rx = std::unique_ptr<ASTTerminalNodeRegister>(rx);
    this->ry = std::unique_ptr<ASTTerminalNodeRegister>(ry);

}

ASTLTypeInstructionNode::~ASTLTypeInstructionNode()
{

}

void ASTLTypeInstructionNode::print()
{
    std::cout << "(L Type instruction Node : ";
    this->instruction->print();
    this->rd->print();
    this->rx->print();
    this->ry->print();
    std::cout << ")";
}

IAST *ASTLTypeInstructionNode::getChildren(int index)
{
    switch (index)
    {
    case 0:
        /* code */
        return instruction.get();
        break;
    case 1:
        /* code */
        return rd.get();
        break;
    case 2:
        /* code */
        return rx.get();
        break;
    case 3:
        /* code */
        return ry.get();
        break;
    
    default:
        return nullptr;
        break;
    }
    return nullptr;
}

//// M type instruction 


//// I type instruction
void ASTITypeInstructionNode::print()
{
    std::cout << "(I Type instruction Node : ";
    this->instruction->print();
    this->rd->print();
    this->imm->print();
    std::cout << ")";
}

std::string *ASTITypeInstructionNode::getTempLabel()
{
    if(this->temp_label != ""){
        return &this->temp_label;
    }
    return nullptr;
}

void ASTITypeInstructionNode::update(const uint16_t address)
{
   if(strcmp(this->instruction->getInstruction(),"load_lsb") == 0){
        this->imm = std::make_unique<ASTTerminalNodeNumber>(address & 0xFF);
   }
   else{
        this->imm = std::make_unique<ASTTerminalNodeNumber>((address >> 8) & 0xFF);
   }
   this->temp_label.clear();
}

IAST *ASTITypeInstructionNode::getChildren(int index)
{
    switch (index)
    {
    case 0:
        /* code */
        return instruction.get();
        break;
    case 1:
        /* code */
        return rd.get();
        break;
    case 2:
        /* code */
        return imm.get();
        break; 
    default:
        return nullptr;
        break;
    }
    return nullptr;
}

ASTITypeInstructionNode::ASTITypeInstructionNode(ASTTerminalNodeInstruction* instruction,ASTTerminalNodeRegister* rd, ASTTerminalNodeNumber* number,token_t* temp_label)
{
    this->instruction = std::unique_ptr<ASTTerminalNodeInstruction>(instruction);
    this->rd = std::unique_ptr<ASTTerminalNodeRegister>(rd);
    this->imm = std::unique_ptr<ASTTerminalNodeNumber>(number);
    if(temp_label != nullptr){
        this->temp_label = temp_label->word;
    }
}



ASTITypeInstructionNode::~ASTITypeInstructionNode()
{

}

ASTTerminalNodeNumber::ASTTerminalNodeNumber(uint8_t number)
{
    this->number = number;
}

ASTTerminalNodeNumber::~ASTTerminalNodeNumber()
{

}

uint8_t ASTTerminalNodeNumber::getValue()
{
    return number;
}

void ASTTerminalNodeNumber::print()
{
    std::cout << "(NodeNumber : " << (unsigned int)this->number << ")";
}

IAST *ASTTerminalNodeNumber::getChildren(int index)
{
    return nullptr;
}

ASTTerminalNodeRegister::ASTTerminalNodeRegister(const char* registerName)
{
    this->registerName[0] = registerName[0];
    this->registerName[1] = registerName[1];
    this->registerName[2] = registerName[2];
}

ASTTerminalNodeRegister::~ASTTerminalNodeRegister()
{

}

void ASTTerminalNodeRegister::print()
{
    std::cout << "(NodeRegister : " << this->registerName << ")" << std::endl;
}




uint8_t ASTTerminalNodeRegister::getNumberRegister()
{
    return std::strtol(&this->registerName[1],nullptr,10) -1;    
}

IAST *ASTTerminalNodeRegister::getChildren(int index)
{
    return nullptr;
}

//// Terminal Node Instruction

ASTTerminalNodeInstruction::ASTTerminalNodeInstruction(token_t* token)
{
    this->instruction = token->word;
}

ASTTerminalNodeInstruction::~ASTTerminalNodeInstruction()
{

}

const char *ASTTerminalNodeInstruction::getInstruction()
{
    return instruction.c_str();
}

void ASTTerminalNodeInstruction::print()
{
    std::cout << "(Node instruction : " << this->instruction << ")";
}

IAST *ASTTerminalNodeInstruction::getChildren(int index)
{
    return nullptr;
}

IAST *ASTMTypeInstructionNode::getChildren(int index)
{
    return nullptr;
}
