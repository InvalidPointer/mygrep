//
// Created by InvalidPointer on 07.05.2016.
//

#include "SyntaxAnalyzer.h"

vector<token> SyntaxAnalyzer::analyze(vector<token> raw_tokens)
{
    vector<token> pf_tokens;

    stack<token> ops;
    string buf = "";
    for (auto it = raw_tokens.begin(); it < raw_tokens.end(); it++) {
        if (!buf.empty() && it->type != STR_T) {
            if (it->type < STR_T) {
                pf_tokens.push_back(token {STR_T, buf});
            } else {
                if (buf.size() > 1) {
                    pf_tokens.push_back(token {STR_T, buf.substr(0, buf.size() - 1)});
                }
                pf_tokens.push_back(token {STR_T, buf.substr(buf.size() - 1)});
            }

            buf = "";
        }
        switch (it->type) {
            case STR_T:
                buf += it->lexeme;
                break;
            case ENUM_T:
            case ITER_T:
                while (!ops.empty() && it->type < ops.top().type) {
                    pf_tokens.push_back(ops.top());
                    ops.pop();
                }
                ops.push(*it);
                break;
            case O_BR_T:
                ops.push(*it);
                break;
            case C_BR_T:
                while (ops.top().type != O_BR_T) {
                    pf_tokens.push_back(ops.top());
                    ops.pop();
                }
                ops.pop();
                break;
        }
    }
    if (!buf.empty()) {
        pf_tokens.push_back(token {STR_T, buf});
    }
    while (!ops.empty()) {
        if (ops.top().type == O_BR_T) {
            throw invalid_argument("Brackets amount mismatch!");
        }

        pf_tokens.push_back(ops.top());
        ops.pop();
    }

    return pf_tokens;
}