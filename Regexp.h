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
    Regexp(const string &pattern);
    ~Regexp() {}

    bool match(const string &target) const;
    rc_result search(const string &target) const;
};


#endif //MYGREP_MYGREP_H
