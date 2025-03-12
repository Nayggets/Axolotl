#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "Visitor.hpp"
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
    while(std::getline(If,str)){
        file_content += str + "\n";
    }
    Lexer lexing((file_content.c_str()));
    token_t token;
    Parser parser(&lexing);
    ASTProgNode* prog = parser.releaseAST();
    prog->print();
    delete (prog);
    //for(int i = 1 ; i < argc ; i++){
        //file = std::string(argv[1]);
        //return_code = treat_file(file);
        //printf("%s compiled with code : %d\n",argv[1],return_code);

        
    //}
    
    return 0;
}