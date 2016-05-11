//
// Created by InvalidPointer on 5/8/2016.
//

#include "Regexp.h"

Regexp::Regexp(const string &pattern)
{
    SyntaxAnalyzer sa(LexicalAnalyzer::analyze(pattern));
    sv = sa.analyze();
}

bool Regexp::match(const string &target) const
{
    RegexpChecker rc(&sv, &target, sv.begin(), target.begin());
    return rc.check().status;
}

rc_result Regexp::search(const string &target) const
{
    for (auto tit = target.begin(); tit < target.end(); tit++) {
        RegexpChecker rc(&sv, &target, sv.begin(), tit, true);
        rc_result r = rc.check();
        if (r.status) {
            return r;
        }
    }

    return rc_result {false, ""};
}