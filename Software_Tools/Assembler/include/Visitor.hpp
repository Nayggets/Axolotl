#include "AST.hpp"
#include <fstream>
#include <any>
#include <string>
#include <iostream>
#include <algorithm>
typedef struct bitField
{
    unsigned int bitField : 5; //Fith bit is for error only
} bit4Field_t;

class Visitor
{
    public:
        Visitor();
        ~Visitor();
        int visitTree(ASTProgNode* prog,std::string fileName, bool debug);
    private:
        std::any visitChildren(IAST* ctx);
        std::any visitInstruction(ASTTerminalNodeInstruction* ctx);
        std::any visitRegister(ASTTerminalNodeRegister* ctx);
        std::any visitImmediateValue(ASTTerminalNodeNumber* ctx);
        std::any visitIInstruction(ASTITypeInstructionNode* ctx);
        std::any visitJInstruction(ASTJTypeInstructionNode* ctx);
        std::any visitLInstruction(ASTLTypeInstructionNode* ctx);
        std::any visitMInstruction(ASTMTypeInstructionNode* ctx);
    private:
        ASTProgNode* program;
        std::ofstream outputFile;
};