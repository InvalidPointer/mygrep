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

enum token_type {STR, ENUM, ITER, O_BR, C_BR};

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
