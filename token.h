#ifndef TOKEN_H
#define TOKEN_H


enum token_type {O_BR_T, C_BR_T, ENUM_T, STR_T, ITER_T}; //Sorted by priorities except brackets and check

struct token
{
    token_type type;
    std::string lexeme;
};


#endif //TOKEN_H