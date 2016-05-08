//
// Created by InvalidPointer on 07.05.2016.
//

#include "SyntaxAnalyzer.h"

vector<token> SyntaxAnalyzer::analyze(vector<token> raw_tokens)
{
    vector<token> pf_tokens;

    stack<token> ops;
    string buf = "";
    for (auto it = raw_tokens.rbegin(); it < raw_tokens.rend(); it++) {
        if (!buf.empty() && it->type != STR_T) {
            reverse(buf.begin(), buf.end());

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
                while (!ops.empty() && it->type < ops.top().type && ops.top().type != C_BR_T) {
                    pf_tokens.push_back(ops.top());
                    ops.pop();
                }
                ops.push(*it);
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
    if (!buf.empty()) {
        reverse(buf.begin(), buf.end());
        pf_tokens.push_back(token {STR_T, buf});
    }
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