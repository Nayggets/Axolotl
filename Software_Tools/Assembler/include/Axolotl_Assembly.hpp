#include <string>
#include <fstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Visitor.hpp"

int treat_file(std::string fileName,std::string outputFileName);