#include <map>
#include "Lexer.hpp"

class LabelTable
{
    
    public:
        LabelTable(std::vector<token_t>& tokens);
        ~LabelTable();
        
        int getValue(const char*);

    private:
        std::map<const char*,int> table;
};