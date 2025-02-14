#include <vector>
#include <memory>
#include <cctype>
#include <string>

typedef enum Token_Type
{
    tok_eof = -1,

    tok_identifier = 1,
    tok_number = 2,
    tok_symbol = 3,
    tok_label = 4,
    tok_section = 5,
    


    tok_error = 0xff,
}token_type_t;


typedef struct token
{
    const char* word;
    token_type_t token_type;
    int line;
    int caracter;
}token_t;

class Lexer
{
    public:
    Lexer(const char* file_content);
    ~Lexer();
    char getChar();
    int getTok(token_t* token);

    private:
        const char* file_content;
};

