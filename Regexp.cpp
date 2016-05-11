//
// Created by InvalidPointer on 5/8/2016.
//

#include "Regexp.h"

Regexp::Regexp(string pattern)
{
    SyntaxAnalyzer sa(LexicalAnalyzer::analyze(pattern));
    sv = sa.analyze();
}

bool Regexp::match(string target)
{
    RegexpChecker rc(&sv, &target, sv.begin(), target.begin());
    return rc.check().status;
}

string Regexp::search(string target)
{
    for (auto tit = target.begin(); tit < target.end(); tit++) {
        RegexpChecker rc(&sv, &target, sv.begin(), tit, true);
        rc_result r = rc.check();
        if (r.status) {
            return target.substr(tit - target.begin(), r.len - (tit - target.begin()));
        }
    }

    return "";
}