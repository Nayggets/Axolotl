#include "Axolotl_Assembly.hpp"

int treat_file(std::string& file_name)
{
    std::ifstream If;
    If.open(file_name);
    std::string str = "";
    std::string file_content = "";
    int line = 0;
    while(std::getline(If,str)){
        line++;
        file_content += str + "\n";
    }
    Lexer lexer((file_content.c_str()));
    std::vector<token_t> tokens;
    token_t token;
    Parser parser(&lexer);
    return 0;
}