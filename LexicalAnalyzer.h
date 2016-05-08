//
// Created by InvalidPointer on 07.05.2016.
//

#ifndef MYGREP_LEXICALANALYZER_H
#define MYGREP_LEXICALANALYZER_H


#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

#include "token.h"

using namespace std;

bool isspecial(char ch);

class LexicalAnalyzer
{
private:

public:
    LexicalAnalyzer() {}
    ~LexicalAnalyzer() {}

    static vector<token> analyze(const string &s);
};


#endif //MYGREP_LEXICALANALYZER_H
