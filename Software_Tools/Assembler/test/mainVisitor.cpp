#include <iostream>
#include <fstream>
#include "Parser.hpp"
#include "Visitor.hpp"
int main(int argc,char* argv[])
{
    if(argc < 3){
        std::cout << "<usage> ./Axolotl_as input_file_name output_file_name\n" << "you can ./Axolotl_as --help" << std::endl;
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
    if(prog == nullptr){
        std::cerr << "Lexing/Parsing failed : compilation aborted" << std::endl;
        exit(-1);
    }
    Visitor visitor;
    visitor.visitTree(prog,argv[2],true);
    delete (prog);
    
    return 0;
}