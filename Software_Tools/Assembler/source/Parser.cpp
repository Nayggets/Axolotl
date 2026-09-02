#include "Parser.hpp"


static std::vector<std::string> registers = { "R1","R2","R3","R4",
                                              "R5","R6","R7","R8",
                                              "R9","R10","R11","R12",
                                              "R13","R14","R15","R16"};

static std::vector<std::string> pseudoRegisters = { "SP","RA","A0","A1",
                                              "A2","A3","RV","T0",
                                              "T1","T2","T3","T4",
                                              "T5","T6","J1","J2"
                                            };

void Parser::printParsingError(std::string nameOfActualParse, token_t* error, token_t* before_error,std::string errorMessage)
{
    this->parseFailed = true;
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
    this->parseFailed = false;
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

    if(this->prog->updateLabel(this->labelTable) == -1){
        this->parseFailed = true;
    }
}

Parser::~Parser()
{

}

ASTProgNode *Parser::releaseAST()
{
    if(this->parseFailed){
        return nullptr;
    }
    return prog.release();
}

int Parser::parseLabel(token_t* token)
{
    this->labelTable[token->word] = this->address;
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
    else if(strcmp(token->word,"set") == 0){
        code = this->parseSetInsutrction(token);
    }
    else if(strcmp(token->word,"mul") == 0){
        #warning mul not design yet
    }
    else if(strcmp(token->word,"div") == 0){
        #warning div not design yet
    }
    else if(strcmp(token->word,"mod") == 0){
        #warning div not design yet
    }
    else if(strcmp(token->word,"hlt") == 0){
        #warning hlt not design yet (hardware or software feature?)
    }
    else{
        this->printParsingError("Instruction parse",token,lastToken,"Unknow instruction espected {add,sub,xor,and,or,not,sll,slr,load_lsb,load_msb,mem_store,je,jlt,jgt,ret}");
        return -1;
    }
    return code;

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
        
        imm = this->parseImmediateValue(token,&oldToken,8);
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
    ASTTerminalNodeInstruction* instruction = new ASTTerminalNodeInstruction(token);
    ASTTerminalNodeRegister* rd;
    ASTTerminalNodeNumber* imm;
    ASTTerminalNodeRegister* ry;

    //// Rd recuperation and verification
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
    imm = this->parseImmediateValue(token,&oldToken,4);
    if(imm == nullptr){
        return -1;
    }
    expected(",",token);

    ry = this->parseRegister(token);
    if(ry == nullptr){
        return -1;
    }
    return 0;
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

    ASTTerminalNodeRegister* rx;
    ASTTerminalNodeRegister* ry;
    ASTTerminalNodeRegister* rz;

    //// Rd recuperation and verification
    rx = this->parseRegister(token);
    if(rx == nullptr){
        return -1;
    }
    expected(",",token);
    ry = this->parseRegister(token);
    if(ry == nullptr){
        return -1;
    }
    expected(",",token);

    rz = this->parseRegister(token);
    if(rz == nullptr){
        return -1;
    }

    this->prog->addNode(new ASTJTypeInstructionNode(instruction,rx,ry,rz));
    return 0;
}

int Parser::parseSetInsutrction(token_t *token)
{
    token_t saveSetToken = *token;
    // SETUP 
    token_t tokLsb = {0};
    tokLsb.word = "load_lsb";
    tokLsb.line = token->line;
    tokLsb.caracter = token->caracter;
    token_t tokMsb = {0};
    tokMsb.word = "load_msb";
    tokMsb.line = token->line;
    tokMsb.caracter = token->caracter;
    ASTTerminalNodeInstruction* instructionLsb = new ASTTerminalNodeInstruction(&tokLsb);
    ASTTerminalNodeInstruction* instructionMsb = new ASTTerminalNodeInstruction(&tokMsb);

    ASTTerminalNodeRegister* rd;
    ASTTerminalNodeNumber* immLsb = nullptr;
    ASTTerminalNodeNumber* immMsb = nullptr;

    rd = this->parseRegister(token);
    if(rd == nullptr){
        return -1;
    }
    expected(",",token);
    token_t oldToken = *token;
    if(this->lexer->getTok(token) != 1){
        this->printParsingError("Parse Set Instruction",token,&oldToken,"Instruction non completed");
        return -1;
    }
    token_t tempLabel = {0};
    tempLabel.token_type = tok_eof;
    if(token->token_type == tok_identifier){
        tempLabel = *token;
    }
    else if(token->token_type == tok_number){
        int value = strtol(token->word,nullptr,10);
        if(value < 0 || value > 65535){
            this->printParsingError("Parse Set Instruction",token,&oldToken,"expected a number between 0 and 65535");
            return -1;
        }
        immLsb = new ASTTerminalNodeNumber(value & 0xFF);
        immMsb = new ASTTerminalNodeNumber((value >> 8) & 0xFF);
    }
    else{
        this->printParsingError("Parse Set Instruction",token,&oldToken,"expected a number or an identifier referenced to a label");
        return -1;
    }
    
    if(tempLabel.token_type == tok_eof){
        this->prog->addNode(new ASTITypeInstructionNode(instructionLsb,rd,immLsb,nullptr));
        this->prog->addNode(new ASTITypeInstructionNode(instructionMsb,rd,immMsb,nullptr));

    }
    else{
        this->prog->addNode(new ASTITypeInstructionNode(instructionLsb,rd,immLsb,&tempLabel));
        this->prog->addNode(new ASTITypeInstructionNode(instructionMsb,rd,immMsb,&tempLabel));

    }
    return 0;
}

int Parser::parseMulInsutrction(token_t *token)
{
    return 0;
}

int Parser::parseDivInsutrction(token_t *token)
{
    return 0;
}

int Parser::parseModInsutrction(token_t *token)
{
    return 0;
}

int Parser::parseHltInsutrction(token_t *token)
{
    return 0;
}

ASTTerminalNodeRegister* Parser::parseRegister(token_t* token)
{
    
    token_t oldToken = *token;

    if(this->lexer->getTok(token) != 1){
        this->printParsingError("Register parse",token,&oldToken,"Instruction Line not completed");
        return nullptr;
    }

    std::string tokenword = token->word;
    
    std::transform(tokenword.begin(), tokenword.end(), tokenword.begin(), ::toupper);
    std::cout << "token word is : " << tokenword << "and token type is : " << token->token_type << std::endl;
    if(token->token_type != tok_identifier || (std::count(registers.begin(),registers.end(),tokenword) == 0 && std::count(pseudoRegisters.begin(),pseudoRegisters.end(),tokenword) == 0)){
        this->printParsingError("Register parse",token,&oldToken,"Expected a register : {R1,R2,R3,...,R16} or pseudo register : {SP,RA,A0,...,J1,J2}");
        return nullptr;
    }

    if(std::count(registers.begin(),registers.end(),tokenword) == 0){
        return new ASTTerminalNodeRegister(pseudoRegisters.at(find(pseudoRegisters.begin(),pseudoRegisters.end(),tokenword) - pseudoRegisters.end()).c_str());
    }
    return new ASTTerminalNodeRegister(token->word);
}




ASTTerminalNodeNumber* Parser::parseImmediateValue(token_t* token,token_t* oldtoken,uint bitNumber)
{
    if(token->token_type != tok_number || std::strtol(token->word,nullptr,10) > std::pow(2,bitNumber) || std::strtol(token->word,nullptr,10) < 0){
        this->printParsingError("Immediate Value parse",token,oldtoken,"immediate value is not correct");
        return nullptr;
    }

    return new ASTTerminalNodeNumber(std::strtol(token->word,nullptr,10)); 
}
