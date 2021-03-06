#include <iostream>
#include "Regexp.h"

Regexp::Regexp(const string &pattern)
{
    SyntaxAnalyzer sa(LexicalAnalyzer::analyze(pattern));
    sv = sa.analyze();

    /*for (auto it = sv.begin(); it < sv.end(); it++) {
        cout << "Lexeme: " << it->lexeme << endl;
    }*/
}

bool Regexp::match(const string &target) const
{
    RegexpChecker rc(&sv, &target, target.begin());
    return rc.check().status;
}

rc_result Regexp::search(const string &target) const
{
    for (auto tit = target.begin(); tit < target.end(); tit++) {
        RegexpChecker rc(&sv, &target, tit, true);
        rc_result r = rc.check();
        if (r.status) {
            return r;
        }
    }

    return rc_result {false, ""};
}