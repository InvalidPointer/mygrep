//
// Created by InvalidPointer on 07.05.2016.
//

#ifndef MYGREP_SYNTAXANALYZER_H
#define MYGREP_SYNTAXANALYZER_H


#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdexcept>

#include "token.h"

using namespace std;

class SyntaxAnalyzer
{
private:
public:
    SyntaxAnalyzer() {}
    ~SyntaxAnalyzer() {}

    static vector<token> analyze(vector<token> raw_tokens);
};


#endif //MYGREP_SYNTAXANALYZER_H
