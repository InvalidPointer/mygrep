//
// Created by InvalidPointer on 5/8/2016.
//

#include <iostream>
#include "RegexpChecker.h"

RegexpChecker::RegexpChecker(vector<token> *v, string *s, vector<token>::const_iterator vit, string::const_iterator sit)
{
    sv = v;
    svit = vit;
    target = s;
    tit = sit;
}

bool RegexpChecker::check()
{
    for ( ; svit < sv->end() && tit < target->end(); ) {
        if (!check_op()) {
            return false;
        }
    }

    return (svit == sv->end() && tit == target->end());
}

bool RegexpChecker::check_op()
{
    left_params++;
    switch (svit->type) {
        case STR_T:
            return op_str();
        case ENUM_T:
            svit++;
            left_params++;
            return op_enum();
        case CAT_T:
            svit++;
            left_params++;
            return op_cat();
        case ITER_T:
            svit++;
            return op_iter();
    }

    return true;
}

bool RegexpChecker::op_str()
{
    bool res = !target->compare(tit - target->begin(), svit->lexeme.size(), svit->lexeme);
    if (res) {
        tit += svit->lexeme.size();
    }

    svit++;
    left_params--;

    return res;
}


bool RegexpChecker::op_enum()
{
    if (left_params--, check_op()) {
        skip_op();
        left_params--;
        return true;
    }

    return left_params--, check_op();
}

bool RegexpChecker::op_cat()
{
    return (left_params--, check_op()) && (left_params--, check_op());
}

bool RegexpChecker::op_iter()
{
    left_params--;

    vector<token>::const_iterator base_it = svit;
    string::const_iterator base_tit = tit;
    skip_op();
    do {
        for (int i = 0; i < left_params; i++) {
            skip_op();
        }
        RegexpChecker rc(sv, target, svit, tit);
        if (rc.check()) {
            return true;
        }
        svit = base_it;
    } while (check_op());

    tit = base_tit;
    return false;
}

void RegexpChecker::skip_op()
{
    switch (svit->type) {
        case STR_T:
            svit++;
            break;
        case ENUM_T:
        case CAT_T:
            svit++;
            skip_op();
            skip_op();
            break;
        case ITER_T:
            svit++;
            skip_op();
            break;
    }
}
