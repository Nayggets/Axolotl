#include "Parser.hpp"


static std::vector<std::string> registers = { "R1","R2","R3","R4",
                                              "R5","R6","R7","R8",
                                              "R9","R10","R11","R12",
                                              "R13","R14","R15","R16",
                                              "r1","r2","r3","r4",
                                              "r5","r6","r7","r8",
                                              "r9","r10","r11","r12",
                                              "r13","r14","r15","r16"};

void Parser::printParsingError(std::string nameOfActualParse, token_t* error, token_t* before_error,std::string errorMessage)
{
    std::cerr << "Error during " << nameOfActualParse << " at line " << error->line << " and colomn " << error->caracter << " for token " << error->word
    << " after token " << before_error->word << " : " << errorMessage << std::endl;  
}

int Parser::expected(const char *expected, token_t* token)
{
    token_t oldToken = *token;
    if(this->lexer->getTok(token) != 1){
        this->printParsingError("Parse Section",token,&oldToken,"Section non completed");
        return -1;
    }
    if(strcmp(expected,token->word) != 0){
        return -1;
    }
    return 0;
}

Parser::Parser(Lexer* lexer)
{
    this->lexer = lexer;
    this->prog = std::make_unique<ASTProgNode>();
    token_t token;
    token_t oldtoken;
    oldtoken.word = "";
    this->address = 0;
    while(lexer->getTok(&token) == 1){
        if(token.token_type == tok_label){
            this->parseLabel(&token);
        }
        else if(token.token_type == tok_section){
            
        }
        else if(token.token_type == tok_identifier){
            this->parseInstruction(&token,&oldtoken);
            this->address++;
        }
        else{
            this->printParsingError("GeneralParse",&token,&oldtoken,"excepted \"label\" or \"section\" or \"instruction\"");
        }
        oldtoken = token;
    }

    this->prog->updateLabel(this->labelTable);

    std::cout << "la fin des elements " << std::endl;
}

Parser::~Parser()
{

}

ASTProgNode *Parser::releaseAST()
{
    return prog.release();
}

int Parser::parseLabel(token_t* token)
{
    std::cout << " Token word est : " << token->word << std::endl;
    this->labelTable[token->word] = this->address+1;
    return 0;
}

int Parser::parseSection(token_t* token)
{
    token_t nameSection;
    if(this->lexer->getTok(&nameSection) != 1){
        this->printParsingError("Parse Section",&nameSection,token,"Section non completed");
        return -1;
    }
    if(nameSection.token_type != tok_identifier){
        return -1;
        this->printParsingError("Parse Section",&nameSection,token,"Expected a section name (an identifier)");
    }
    return -1;
    #warning Section not implemented yet 
}



int Parser::parseInstruction(token_t* token,token_t* lastToken)
{
    int code = 0;
    if(strcmp(token->word,"add") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"sub") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"xor") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"and") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"not") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"or") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"sll") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"slr") == 0){
        code = this->parseLInstruction(token);
    }
    else if(strcmp(token->word,"load_lsb") == 0){
        code = this->parseIInstruction(token);
    }
    else if(strcmp(token->word,"load_msb") == 0){
        code = this->parseIInstruction(token);
    }
    else if(strcmp(token->word,"mem_store") == 0){
        code = this->parseMInstruction(token);
    }
    else if(strcmp(token->word,"mem_load") == 0){
        code = this->parseMInstruction(token);
    }
    else if(strcmp(token->word,"je") == 0){
        code = this->parseJInsutrction(token);
    }
    else if(strcmp(token->word,"jlt") == 0){
        code = this->parseJInsutrction(token);
    }
    else if(strcmp(token->word,"jgt") == 0){
        code = this->parseJInsutrction(token);
    }
    else if(strcmp(token->word,"ret") == 0){
        code = this->parseJInsutrction(token);
    }
    else{
        this->printParsingError("Instruction parse",token,lastToken,"Unknow instruction espected {add,sub,xor,and,or,not,sll,slr,load_lsb,load_msb,mem_store,je,jlt,jgt,ret}");
        return -1;
    }
    return 0;

}


int Parser::parseLInstruction(token_t* token)
{
    if(strcmp(token->word,"not") == 0){

        // Implementation
        ASTTerminalNodeInstruction* instruction = new ASTTerminalNodeInstruction(token);
        ASTTerminalNodeRegister* rd;
        ASTTerminalNodeRegister* rx;
        rd = this->parseRegister(token);
        if(rd == nullptr){
            return -1;
        }
        expected(",",token);

        rx = this->parseRegister(token);
        if(rx == nullptr){
            return -1;
        }
        this->prog->addNode(new ASTLTypeInstructionNode(instruction,rd,rx,nullptr));
        return 0;
    }
    ASTTerminalNodeInstruction* instruction = new ASTTerminalNodeInstruction(token);

    ASTTerminalNodeRegister* rd;
    ASTTerminalNodeRegister* rx;
    ASTTerminalNodeRegister* ry;

    //// Rd recuperation and verification
    rd = this->parseRegister(token);
    if(rd == nullptr){
        return -1;
    }
    expected(",",token);
    rx = this->parseRegister(token);
    if(rx == nullptr){
        return -1;
    }
    expected(",",token);
    ry = this->parseRegister(token);
    if(ry == nullptr){
        return -1;
    }

    this->prog->addNode(new ASTLTypeInstructionNode(instruction,rd,rx,ry));
    return 0;
    
}

int Parser::parseIInstruction(token_t* token)
{
    ASTTerminalNodeInstruction* instruction = new ASTTerminalNodeInstruction(token);
    ASTTerminalNodeRegister* rd;
    ASTTerminalNodeNumber* imm = nullptr;
    rd = this->parseRegister(token);
    if(rd == nullptr){
        return -1;
    }
    expected(",",token);
    token_t oldToken = *token;
    if(this->lexer->getTok(token) != 1){
        this->printParsingError("Parse Instruction",token,&oldToken,"Instruction non completed");
        return -1;
    }
    token_t tempLabel = {0};
    tempLabel.token_type = tok_eof;
    if(token->token_type == tok_identifier){
        tempLabel = *token;
    }
    else if(token->token_type == tok_number){
        
        imm = this->parseImmediateValue(token,&oldToken);
        if(imm == nullptr){
            return -1;
        }
    }
    else{
        this->printParsingError("Parse Instruction",token,&oldToken,"expected a number or an identifier referenced to a label");
        return -1;
    }
    
    if(tempLabel.token_type == tok_eof){
        this->prog->addNode(new ASTITypeInstructionNode(instruction,rd,imm,nullptr));
    }
    else{
        this->prog->addNode(new ASTITypeInstructionNode(instruction,rd,imm,&tempLabel));
    }
    return 0;
}

int Parser::parseMInstruction(token_t* token)
{
    return -1;
}

int Parser::parseJInsutrction(token_t* token)
{
    if(strcmp(token->word,"ret") == 0){
                // Implementation
        ASTTerminalNodeInstruction* instruction = new ASTTerminalNodeInstruction(token);
        this->prog->addNode(new ASTJTypeInstructionNode(instruction,nullptr,nullptr,nullptr));
        return 0;
    }
    ASTTerminalNodeInstruction* instruction = new ASTTerminalNodeInstruction(token);

    ASTTerminalNodeRegister* rd;
    ASTTerminalNodeRegister* rx;
    ASTTerminalNodeRegister* ry;

    //// Rd recuperation and verification
    rd = this->parseRegister(token);
    if(rd == nullptr){
        return -1;
    }
    expected(",",token);
    rx = this->parseRegister(token);
    if(rx == nullptr){
        return -1;
    }
    expected(",",token);

    ry = this->parseRegister(token);
    if(ry == nullptr){
        return -1;
    }

    this->prog->addNode(new ASTJTypeInstructionNode(instruction,rd,rx,ry));
    return 0;
    return -1;
}



ASTTerminalNodeRegister* Parser::parseRegister(token_t* token)
{
    
    token_t oldToken = *token;

    if(this->lexer->getTok(token) != 1){
        this->printParsingError("Register parse",token,&oldToken,"Instruction Line not completed");
        return nullptr;
    }
    if(token->token_type != tok_identifier || std::count(registers.begin(),registers.end(),token->word) == 0){
        this->printParsingError("Register parse",token,&oldToken,"Expected a register : {R1,R2,R3,...,R16}");
        return nullptr;
    }
    return new ASTTerminalNodeRegister(token->word);
}

ASTTerminalNodeNumber* Parser::parseImmediateValue(token_t* token,token_t* oldtoken)
{
    std::cout << std::strtol(token->word,nullptr,10) << std::endl;
    if(token->token_type != tok_number || std::strtol(token->word,nullptr,10) > 255 || std::strtol(token->word,nullptr,10) < 0){
        this->printParsingError("Immediate Value parse",token,oldtoken,"immediate value is not correct");
        return nullptr;
    }

    return new ASTTerminalNodeNumber(std::strtol(token->word,nullptr,10)); 
}
