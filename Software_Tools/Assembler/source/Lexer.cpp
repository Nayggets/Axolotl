#include "Lexer.hpp"
#include <iostream>


Lexer::Lexer(const char* file_content)
{
    this->file_content = file_content;
}

Lexer::~Lexer()
{

}

static int caracter = 0;

char Lexer::getChar()
{
    caracter++;
    char a = *(this->file_content);
    this->file_content = this->file_content +1;
    return a;
}

static std::string str = std::string("");
static char lastChar = ' ';
static int line = 1;
int Lexer::getTok(token_t* token)
{
    str = "";
    token->token_type = tok_identifier;
    token->word;
    while((lastChar == ' ' || lastChar == '\n' || lastChar == '\t' || lastChar == '\r') && lastChar != '\0'){
        if(lastChar == '\n'){
            line++;
            caracter = 0;
        }
        lastChar = this->getChar();
    }
    token->line = line;
    token->caracter = caracter;

    if(lastChar == '\0'){
        token->token_type = tok_eof;
        return 0;
    }
    if(lastChar == ','){
        str += lastChar;
        lastChar = this->getChar();
        token->token_type = tok_symbol;
        token->word = str.c_str();
        return 1;
    }
    
    if(isalpha(lastChar) || lastChar == '.'){ // identifier [a-zA-Z][a-zA-Z0-9]+;
        if(lastChar == '.'){
            token->token_type = tok_section;
            str += lastChar;
            lastChar = this->getChar();
        }
        while((isalpha(lastChar) || isdigit(lastChar) || lastChar == '_') && lastChar != '\n'){
            str += lastChar;
            lastChar = this->getChar();
        }
        if(lastChar == ':'){
            str += lastChar;
            lastChar = this->getChar();
            token->word = str.c_str();
            if(token->token_type == tok_section){
                token->token_type = tok_error;
                return -1;
            }
            token->token_type = tok_label;
            return 1;
        }

        if(token->token_type == tok_section){
            token->word = str.c_str();
            if(str != ".section"){
                token->token_type = tok_error;
                return -1;
            }
            return 1;
        }

        token->token_type = tok_identifier;
        return 1;
    }
    
    if(isdigit(lastChar)){
        while(isdigit(lastChar)){
            str += lastChar;
            lastChar = this->getChar();
        }
        token->word = str.c_str();        
        token->token_type = tok_number;
        return 1;
    }
    token->token_type = tok_error;
    token->word = str.c_str();
    return -1;
}
