#ifndef PARSER
#define PARSER 1
#include "Lexer.hpp"
#include "AST.hpp"
#include <string.h>
#include <memory>
#include <fstream>
#include <algorithm>
#include <map>

class Parser
{
    public:
        Parser(Lexer* lexer);
        ~Parser();
        ASTProgNode* releaseAST();

    private:
        // Parse label
        int parseLabel(token_t* token); 
        //parse Section
        int parseSection(token_t* token);
        //parse Instruction
        int parseInstruction(token_t* token,token_t* lastToken);
        int parseLInstruction(token_t* token);
        int parseIInstruction(token_t* token);
        int parseMInstruction(token_t* token);
        int parseJInsutrction(token_t* token);
        //parse register
        ASTTerminalNodeRegister* parseRegister(token_t* token);
        //parse immediate value
        ASTTerminalNodeNumber* parseImmediateValue(token_t* token,token_t* oldtoken);
        void printParsingError(std::string nameOfActualParse, token_t* error, token_t* before_error,std::string erorrMessage);
        int expected(const char* expected,token_t* token);

    private:
        std::unique_ptr<ASTProgNode> prog; // The AST
        Lexer* lexer; // the recursive lexer
        std::map<std::string,uint32_t> labelTable;
        uint32_t address; //the current address of the instruction we are parsing
        bool parseFailed;
};



#endif