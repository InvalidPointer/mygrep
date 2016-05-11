//
// Created by InvalidPointer on 5/8/2016.
//

#include "RegexpChecker.h"

RegexpChecker::RegexpChecker(const vector<token> *v, const string *s, vector<token>::const_iterator vit, string::const_iterator sit, bool search):
    sv(v),
    svit(vit),
    target(s),
    btit(sit),
    tit(sit),
    search(search)
{
}

rc_result RegexpChecker::check()
{
    for ( ; svit < sv->end() && tit < target->end(); ) {
        if (!check_op()) {
            return rc_result {false, ""};
        }
    }

    return rc_result {(svit == sv->end() && (tit == target->end() || search)),
                      target->substr(btit - target->begin(), static_cast<int>(tit - btit))};
}

bool RegexpChecker::check_op()
{
    switch (svit->type) {
        case STR_T:
            return op_str();
        case ENUM_T:
            svit++;
            return op_enum();
        case CAT_T:
            svit++;
            return op_cat();
        case ITER_OM_T:
            svit++;
            return op_iter(1);
        case ITER_ZO_T:
            svit++;
            return op_iter(0, 1);
        case ITER_ZM_T:
            svit++;
            return op_iter();
        case ITER_N_T: {
            svit++;
            int pos = (svit - 1)->lexeme.find(",");
            return op_iter(stoi((svit - 1)->lexeme.substr(0, pos)), stoi((svit - 1)->lexeme.substr(pos + 1)));
        }
    }

    return true;
}

bool RegexpChecker::op_str()
{
    bool res = !svit->lexeme.compare(".") || !target->compare(tit - target->begin(), svit->lexeme.size(), svit->lexeme);
    if (res) {
        tit += svit->lexeme.size();
    }
    svit++;

    return res;
}


bool RegexpChecker::op_enum()
{
    skip_params++;
    if (check_op()) {
        skip_op();
        skip_params--;
        return true;
    }

    return skip_params--, check_op();
}

bool RegexpChecker::op_cat()
{
    skip_params++;
    if (!check_op()) {
        skip_op();
        skip_params--;
        return false;
    }

    return skip_params--, check_op();
}

bool RegexpChecker::op_iter(int min, int max)
{
    if (min < 0 || (max != -1 && min > max)) {
        throw invalid_argument("Error iter boundaries!");
    }

    int iter_count = 0;
    bool found = false;
    vector<token>::const_iterator base_it = svit;
    string::const_iterator base_tit = tit, prev_tit = tit;
    skip_op();
    do {
        for (int i = 0; i < skip_params; i++) {
            skip_op();
        }
        RegexpChecker rc(sv, target, svit, tit, search);
        if (rc.check().status && iter_count >= min) {
            found = true;
        } else if (found) {
            tit = prev_tit;
            return true;
        }
        svit = base_it;
        prev_tit = tit;
    } while (iter_count++, check_op() && (max == -1 || iter_count <= max));

    if (found) {
        tit = prev_tit;
        return true;
    }
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
        case ITER_OM_T:
        case ITER_ZO_T:
        case ITER_ZM_T:
        case ITER_N_T:
            svit++;
            skip_op();
            break;
    }
}
