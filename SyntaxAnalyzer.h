//
// Created by InvalidPointer on 07.05.2016.
//

#ifndef MYGREP_SYNTAXANALYZER_H
#define MYGREP_SYNTAXANALYZER_H

#include "LexicalAnalyzer.h"
#include <stack>

class SyntaxAnalyzer
{
private:
public:
    SyntaxAnalyzer() {}
    ~SyntaxAnalyzer() {}

    vector<token> analyze(vector<token> raw_tokens);
};

#endif //MYGREP_SYNTAXANALYZER_H
