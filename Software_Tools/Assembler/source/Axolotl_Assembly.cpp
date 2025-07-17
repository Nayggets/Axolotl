#include "Axolotl_Assembly.hpp"

int treat_file(std::string fileName,std::string outputFileName)
{
    std::ifstream If;
    If.open(fileName);
    std::string str = "";
    std::string fileContent = "";
    int line = 0;
    while(std::getline(If,str)){
        line++;
        fileContent += str + "\n";
    }
    Lexer lexer((fileContent.c_str()));
    std::vector<token_t> tokens;
    token_t token;
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