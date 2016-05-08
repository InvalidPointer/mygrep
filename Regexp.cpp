//
// Created by InvalidPointer on 5/8/2016.
//

#include "Regexp.h"

Regexp::Regexp(string pattern)
{
    sv = SyntaxAnalyzer::analyze(LexicalAnalyzer::analyze(pattern));
}

bool Regexp::match(string target)
{
    RegexpChecker rc(&sv, &target, sv.begin(), target.begin());
    return rc.check();
}
