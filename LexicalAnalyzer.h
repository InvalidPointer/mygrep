//
// Created by InvalidPointer on 07.05.2016.
//

#ifndef MYGREP_LEXICALANALYZER_H
#define MYGREP_LEXICALANALYZER_H

#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

using namespace std;

enum token_type {O_BR_T, C_BR_T, ENUM_T, STR_T, ITER_T}; //Sorted by priorities except brackets

struct token
{
    token_type type;
    string lexeme;
};

bool isspecial(char ch);

class LexicalAnalyzer
{
private:

public:
    LexicalAnalyzer() {}
    ~LexicalAnalyzer() {}

    vector<token> analyze(const string &s);
};

#endif //MYGREP_LEXICALANALYZER_H
