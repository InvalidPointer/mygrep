//
// Created by InvalidPointer on 07.05.2016.
//

#include <iostream>
#include "SyntaxAnalyzer.h"

void flush_buf(string &buf, vector<token> &toks)
{
    if (!buf.empty()) {
        reverse(buf.begin(), buf.end());
        toks.push_back(token {STR_T, buf});
        buf = "";
    }
}

vector<token> SyntaxAnalyzer::analyze(vector<token> raw_tokens)
{
    vector<token> pf_tokens;

    stack<token> ops;
    string buf = "";
    for (auto it = raw_tokens.rbegin(); it < raw_tokens.rend(); it++) {
        if (it->type != STR_T && it->type != CAT_T) {
            flush_buf(buf, pf_tokens);
        }

        switch (it->type) {
            case STR_T:
                if (!it->lexeme.compare(".")) {
                    flush_buf(buf, pf_tokens);
                    pf_tokens.push_back(*it);
                } else {
                    buf += it->lexeme;
                }
                break;
            case ENUM_T:
            case ITER_OM_T:
            case ITER_ZO_T:
            case ITER_ZM_T:
                while (!ops.empty() && prior[it->type] < prior[ops.top().type] && ops.top().type != C_BR_T) {
                    pf_tokens.push_back(ops.top());
                    ops.pop();
                }
                ops.push(*it);
                break;
            case CAT_T:
                if (it - 2 >= raw_tokens.rbegin() && (it - 2)->type > CAT_T) {
                    flush_buf(buf, pf_tokens);
                    while (!ops.empty() && prior[CAT_T] < prior[ops.top().type] && ops.top().type != C_BR_T) {
                        pf_tokens.push_back(ops.top());
                        ops.pop();
                    }
                    ops.push(*it);
                }
                break;
            case O_BR_T:
                while (ops.top().type != C_BR_T) {
                    pf_tokens.push_back(ops.top());
                    ops.pop();
                }
                ops.pop();
                break;
            case C_BR_T:
                ops.push(*it);
                break;
        }
    }
    flush_buf(buf, pf_tokens);
    while (!ops.empty()) {
        if (ops.top().type == C_BR_T) {
            throw invalid_argument("Brackets amount mismatch!");
        }

        pf_tokens.push_back(ops.top());
        ops.pop();
    }

    reverse(pf_tokens.begin(), pf_tokens.end());

    return pf_tokens;
}