#ifndef AST
#define AST 1
#include <memory>
#include <vector>
#include <map>
#include <iostream>
#include <string.h>
#include "Lexer.hpp"

class IAST
{
    public:
        virtual void print() = 0;
        virtual ~IAST() = default;
};




class ASTProgNode : public IAST
{
    public:
        ASTProgNode();
        ~ASTProgNode();
        void print();
        void addNode(IAST* iast);
        void updateLabel(std::map<std::string,uint32_t>& labelTable);
    private:
        std::vector<IAST*> programs;
};

class ASTTerminalNodeNumber : public IAST
{
    public:
        ASTTerminalNodeNumber(uint8_t number);
        ~ASTTerminalNodeNumber();
        void print();
    private:
        int8_t number;
};

class ASTTerminalNodeRegister : public IAST
{
    public:
        ASTTerminalNodeRegister(const char* registerName);
        ~ASTTerminalNodeRegister();
        void print();
    private:
        char registerName[3];
};


class ASTTerminalNodeInstruction : public IAST
{
    public:
        ASTTerminalNodeInstruction(token_t* token);
        ~ASTTerminalNodeInstruction();
        const char* getInstruction();
        void print();
    private:
        std::string instruction;
};


class ASTJTypeInstructionNode : public IAST
{
    public:
        ASTJTypeInstructionNode(ASTTerminalNodeInstruction* instruction,ASTTerminalNodeRegister* rx,ASTTerminalNodeRegister* ry,ASTTerminalNodeRegister* rz);
        ~ASTJTypeInstructionNode();
        void print();
    private:
        std::unique_ptr<ASTTerminalNodeInstruction> instruction; // jump instruction
        std::unique_ptr<ASTTerminalNodeRegister> rx; // rx
        std::unique_ptr<ASTTerminalNodeRegister> ry; // ry
        std::unique_ptr<ASTTerminalNodeRegister> rz; // rz 

};


class ASTLTypeInstructionNode : public IAST
{
    public: 
        ASTLTypeInstructionNode(ASTTerminalNodeInstruction* instruction,ASTTerminalNodeRegister* rd, ASTTerminalNodeRegister* rx, ASTTerminalNodeRegister* ry);
        ~ASTLTypeInstructionNode();
        void print();

    private:
        std::unique_ptr<ASTTerminalNodeInstruction> instruction;
        std::unique_ptr<ASTTerminalNodeRegister> rd;
        std::unique_ptr<ASTTerminalNodeRegister> rx;
        std::unique_ptr<ASTTerminalNodeRegister> ry; // is null if instruction is not rd,rx

};

class ASTMTypeInstructionNode : public IAST
{

    private:
        std::unique_ptr<ASTTerminalNodeInstruction> instruction;
};


class ASTITypeInstructionNode : public IAST
{    public: 
        ASTITypeInstructionNode(ASTTerminalNodeInstruction* instruction,ASTTerminalNodeRegister* rd, ASTTerminalNodeNumber* number,token_t* temp_label);
        ~ASTITypeInstructionNode();
        void print();
        std::string* getTempLabel();
        void update(const int16_t address);

    private:
        std::unique_ptr<ASTTerminalNodeInstruction> instruction;
        std::unique_ptr<ASTTerminalNodeRegister> rd;
        std::unique_ptr<ASTTerminalNodeNumber> imm;
        std::string temp_label;
};

#endif