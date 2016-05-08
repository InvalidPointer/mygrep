//
// Created by InvalidPointer on 5/8/2016.
//

#ifndef MYGREP_MYGREP_H
#define MYGREP_MYGREP_H


#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "RegexpChecker.h"

class Regexp
{
private:
    vector<token> sv;
public:
    Regexp(string pattern);
    ~Regexp() {}

    bool match(string target);
};


#endif //MYGREP_MYGREP_H
