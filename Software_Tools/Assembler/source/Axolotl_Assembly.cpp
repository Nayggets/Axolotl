#include "Axolotl_Assembly.hpp"

int treat_file(std::string fileName,std::string outputFileName)
{
    std::ifstream If;
    If.open(fileName,std::ofstream::ios_base::in);

    if(If.is_open() == 0){
        std::cerr << "Huge error file " << fileName << " fail to open" << std::endl;
    }
    std::string str = "";
    std::string fileContent = "";
    int line = 0;
    while(std::getline(If,str)){
        line++;
        fileContent += str + "\n";
    }
    Lexer lexer((fileContent.c_str()));
    std::vector<token_t> tokens;
    Parser parser(&lexer);
    ASTProgNode* prog = parser.releaseAST();
    if(prog == nullptr){
        std::cerr << "Lexing/Parsing failed : compilation aborted" << std::endl;
        exit(-1);
    }
    Visitor visitor;
    visitor.visitTree(prog,outputFileName.c_str(),false);
    delete (prog);
    return 0;
}