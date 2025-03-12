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

void ASTProgNode::updateLabel(std::map<std::string, uint32_t>& labelTable)
{
    for(auto& astNode : this->programs){
        if(typeid(*astNode) == typeid(ASTITypeInstructionNode) ){
            ASTITypeInstructionNode* ast = (ASTITypeInstructionNode*)astNode;
            std::string* label = ast->getTempLabel();
            if(label == nullptr){
                std::cout << "HUGE PROBLEME !!!!" << std::endl;
            }
        
            if(label != nullptr){
                std::cout << "word est : " << *label << " est sa valeur est : " << labelTable[*label] << std::endl;
                ast->update(labelTable[*label+":"]);
            }
        }
    }
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

void ASTITypeInstructionNode::update(const int16_t address)
{
   if(strcmp(this->instruction->getInstruction(),"load_lsb") == 0){
        this->imm = std::make_unique<ASTTerminalNodeNumber>(address & 0xFF);
   }
   else{
        this->imm = std::make_unique<ASTTerminalNodeNumber>((address >> 8) & 0xFF);
   }
   this->temp_label.clear();
}


ASTITypeInstructionNode::ASTITypeInstructionNode(ASTTerminalNodeInstruction* instruction,ASTTerminalNodeRegister* rd, ASTTerminalNodeNumber* number,token_t* temp_label)
{
    this->instruction = std::unique_ptr<ASTTerminalNodeInstruction>(instruction);
    this->rd = std::unique_ptr<ASTTerminalNodeRegister>(rd);
    this->imm = std::unique_ptr<ASTTerminalNodeNumber>(number);
    if(temp_label != nullptr){
        std::cout << "Le label word est : " << temp_label->word << std::endl;
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

void ASTTerminalNodeNumber::print()
{
    std::cout << "(NodeNumber : " << (unsigned int)this->number << ")";
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
