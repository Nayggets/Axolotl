#include "Visitor.hpp"

Visitor::Visitor()
{
}

Visitor::~Visitor()
{
}

std::string uint16ToBitString(uint16_t x)
{
    std::string s = "";
    for(int i = 0; i < 16; i++)
    {
        if(x % 2 == 0){
            s.push_back('0');
        }
        else{
            s.push_back('1');
        }
        x = x/2;
    }
    std::reverse(s.begin(),s.end());
    return s;
}

int Visitor::visitTree(ASTProgNode *prog, std::string fileName, bool debug)
{
    outputFile.open(fileName);
    IAST* child;
    int i = 0;
    child = prog->getChildren(i);
    uint16_t currentInstruction;
    while(child != nullptr){
        currentInstruction = std::any_cast<uint16_t>(this->visitChildren(child));
        if(debug){
            std::cout << "line : " << i << " is : " << uint16ToBitString(currentInstruction) << std::endl;
        }
        outputFile.write((const char*)&currentInstruction,2);
        i++;
        child = prog->getChildren(i);
    }
    outputFile.close();
    return 0;
}

std::any Visitor::visitChildren(IAST *ctx)
{
    if(typeid(*ctx) == typeid(ASTTerminalNodeRegister)){
        return visitRegister((ASTTerminalNodeRegister*)ctx);
    }
    else if(typeid(*ctx) == typeid(ASTTerminalNodeInstruction)){
        return visitInstruction((ASTTerminalNodeInstruction*)ctx);
    }
    else if(typeid(*ctx) == typeid(ASTTerminalNodeNumber)){
        return visitImmediateValue((ASTTerminalNodeNumber*)ctx);
    }
    else if(typeid(*ctx) == typeid(ASTITypeInstructionNode)){
        return visitIInstruction((ASTITypeInstructionNode*)ctx);
    }
    else if(typeid(*ctx) == typeid(ASTLTypeInstructionNode)){
        return visitLInstruction((ASTLTypeInstructionNode*)ctx);
    }
    else if(typeid(*ctx) == typeid(ASTMTypeInstructionNode)){
        return visitMInstruction((ASTMTypeInstructionNode*)ctx);
    }
    else if(typeid(*ctx) == typeid(ASTJTypeInstructionNode)){
        return visitJInstruction((ASTJTypeInstructionNode*)ctx);
    }

    return std::any();
}

std::any Visitor::visitInstruction(ASTTerminalNodeInstruction *ctx)
{
    
    if(strcmp(ctx->getInstruction(),"add") == 0){
        return (uint8_t)0b0000;
    }
    else if(strcmp(ctx->getInstruction(),"sub") == 0){
        return (uint8_t) 0b0001;
    }  
    else if(strcmp(ctx->getInstruction(),"xor") == 0){
        return (uint8_t) 0b0010;
    }
    else if(strcmp(ctx->getInstruction(),"and") == 0){
        return (uint8_t) 0b0011;
    }
    else if(strcmp(ctx->getInstruction(),"not") == 0){
        return (uint8_t) 0b0100;
    }
    else if(strcmp(ctx->getInstruction(),"or") == 0){
        return (uint8_t) 0b0101;
    }
    else if(strcmp(ctx->getInstruction(),"sll") == 0){
        return (uint8_t) 0b0110;
    }
    else if(strcmp(ctx->getInstruction(),"slr") == 0){
        return (uint8_t) 0b0111;
    }
    else if(strcmp(ctx->getInstruction(),"load_lsb") == 0){
        return (uint8_t) 0b1000;
    }
    else if(strcmp(ctx->getInstruction(),"load_msb") == 0){
        return (uint8_t) 0b1001;
    }
    else if(strcmp(ctx->getInstruction(),"mem_store") == 0){
        return (uint8_t) 0b1010;
    }
    else if(strcmp(ctx->getInstruction(),"mem_load") == 0){
        return (uint8_t) 0b1011;
    }
    else if(strcmp(ctx->getInstruction(),"je") == 0){
        return (uint8_t) 0b1100;
    }
    else if(strcmp(ctx->getInstruction(),"jlt") == 0){
        return (uint8_t) 0b1101;
    }
    else if(strcmp(ctx->getInstruction(),"jgt") == 0){
        return (uint8_t) 0b1110;
    }
    else if(strcmp(ctx->getInstruction(),"ret") == 0){
        return (uint8_t) 0b1111;
    }
}

std::any Visitor::visitRegister(ASTTerminalNodeRegister *ctx)
{
    return ctx->getNumberRegister();
}

std::any Visitor::visitImmediateValue(ASTTerminalNodeNumber *ctx)
{
    return ctx->getValue();
}

std::any Visitor::visitIInstruction(ASTITypeInstructionNode *ctx)
{
    uint16_t IR;
    IR = std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(0)));
    IR = IR <<4;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(1)));
    IR = IR <<8;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(2)));
    return IR;
}

std::any Visitor::visitJInstruction(ASTJTypeInstructionNode *ctx)
{
    uint16_t IR;
    IR = std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(0))); // opcode
    IR = IR <<4;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(1))); //rd
    IR = IR <<4;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(2))); //rx
    IR = IR <<4;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(3))); //ry
    return IR;
}

std::any Visitor::visitLInstruction(ASTLTypeInstructionNode *ctx)
{
    uint16_t IR;
    IR = std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(0)));
    IR = IR <<4;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(1)));
    IR = IR <<4;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(2)));
    IR = IR <<4;
    IR += std::any_cast<uint8_t>(this->visitChildren(ctx->getChildren(3)));
    return IR;
}

std::any Visitor::visitMInstruction(ASTMTypeInstructionNode *ctx)
{
    return std::any();
}
