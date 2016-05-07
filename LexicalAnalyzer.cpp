//
// Created by InvalidPointer on 07.05.2016.
//

#include "LexicalAnalyzer.h"


bool isspecial(char ch)
{
    return string("|*()\\").find(ch) != string::npos;
}


vector<token> LexicalAnalyzer::analyze(const string &expr)
{
    vector<token> toks;
    string term_concat = "";

    bool escaped = false;
    for (auto it = expr.begin(); it < expr.end(); it++) {
        if (!isgraph(*it)) {
            throw invalid_argument("Invalid symbol in regex!");
        }

        if (!isspecial(*it)) {
            term_concat += *it;
        } else if (escaped) {
            if (isspecial(*it)) {
                term_concat += *it;
            } else {
                throw invalid_argument("Invalid escape character!");
            }
            escaped = false;
        } else {
            if (!term_concat.empty() && *it != '\\') {
                toks.push_back(token {STR, term_concat});
                term_concat = "";
            }

            if (*it == '|') {
                toks.push_back(token {ENUM, "|"});
            } else if (*it == '*') {
                toks.push_back(token {ITER, "*"});
            } else if (*it == '(') {
                toks.push_back(token {O_BR, "("});
            } else if (*it == ')') {
                toks.push_back(token {C_BR, ")"});
            } else if (*it == '\\') {
                escaped = true;
            }
        }
    }
    if (!term_concat.empty()) {
        toks.push_back(token {STR, term_concat});
    }

    return toks;
}


