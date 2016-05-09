#ifndef TOKEN_H
#define TOKEN_H


enum token_type {O_BR_T, C_BR_T, ENUM_T, STR_T, CAT_T, ITER_ZO_T, ITER_OM_T, ITER_ZM_T};
const int prior[] = {0, 0, 1, 2, 2, 3, 3, 3};

struct token
{
    token_type type;
    std::string lexeme;
};


#endif //TOKEN_H