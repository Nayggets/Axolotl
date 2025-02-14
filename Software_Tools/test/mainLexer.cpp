#include <iostream>
#include <fstream>
#include "Lexer.hpp"

int main(int argc,char* argv[])
{
    if(argc < 2){
        std::cout << "<usage> ./Axolotl_as file_name\n" << "you can ./Axolotl_as --help" << std::endl;
        exit(-1);
    }
    int return_code = 0;
    std::ifstream If;
    If.open(argv[1]);
    std::string str = "";
    std::string file_content = "";
    int line = 0;
    while(std::getline(If,str)){
        line++;
        file_content += str + "\n";
    }
    Lexer lexing((file_content.c_str()));
    std::vector<token_t> tokens;
    token_t token;
    while(lexing.getTok(&token) == 1){
        tokens.push_back(token);
        std::cout << "Token type = " << token.token_type << " and token string : " << token.word << " at line : " << token.line << " and at caracter : " << token.caracter << std::endl;
    }
    //for(int i = 1 ; i < argc ; i++){
        //file = std::string(argv[1]);
        //return_code = treat_file(file);
        //printf("%s compiled with code : %d\n",argv[1],return_code);

        
    //}
}