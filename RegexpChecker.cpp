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
    switch (svit->type) {
        case STR_T:
            return op_str();
        case ENUM_T:
            svit++;
            return op_enum();
    }

    return true;
}

bool RegexpChecker::op_str()
{
    bool res = !target->compare(tit - target->begin(), svit->lexeme.size(), svit->lexeme);
    if (res) {
        tit += svit->lexeme.size();
    }

    //cout << *target << " " << tit - target->begin() << " " << svit->lexeme.size() << " " << svit->lexeme << " " << res << endl;

    svit++;

    return res;
}


bool RegexpChecker::op_enum()
{
    if (check_op()) {
        skip_op();
        return true;
    }

    return check_op();
}

bool RegexpChecker::op_iter()
{
    return false;
}

void RegexpChecker::skip_op()
{
    switch (svit->type) {
        case STR_T:
            svit++;
            break;
        case ENUM_T:
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
