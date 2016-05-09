//
// Created by InvalidPointer on 07.05.2016.
//

#include "LexicalAnalyzer.h"


bool isspecial(char ch)
{
    return string(".?+|*()\\").find(ch) != string::npos;
}


vector<token> LexicalAnalyzer::analyze(const string &expr)
{
    vector<token> toks;

    bool escaped = false;
    token_type prev_t = CAT_T;
    for (auto it = expr.begin(); it < expr.end(); it++) {
        if (!isgraph(*it)) {
            throw invalid_argument("Invalid symbol in regex!");
        }

        if (!isspecial(*it) || escaped) {
            if (!isspecial(*it) && escaped) {
                throw invalid_argument("Invalid escape character!");
            }
            if (prev_t == STR_T) {
                toks.push_back(token {CAT_T, ""});
            }
            toks.push_back(token {STR_T, string(1, *it)});
            escaped = false;
        } else {
            switch (*it) {
                case '.':
                    toks.push_back(token {STR_T, "."});
                    break;
                case '|':
                    toks.push_back(token {ENUM_T, "|"});
                    break;
                case '+':
                    toks.push_back(token {ITER_OM_T, "+"});
                    break;
                case '?':
                    toks.push_back(token {ITER_ZO_T, "?"});
                    break;
                case '*':
                    toks.push_back(token {ITER_ZM_T, "*"});
                    break;
                case '(':
                    toks.push_back(token {O_BR_T, "("});
                    break;
                case ')':
                    toks.push_back(token {C_BR_T, ")"});
                    break;
                case '\\':
                    escaped = true;
                    break;
                default:
                    break;
            }
        }
        prev_t = toks.back().type;
    }

    return toks;
}