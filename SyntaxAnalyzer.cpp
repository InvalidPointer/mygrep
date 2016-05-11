//
// Created by InvalidPointer on 07.05.2016.
//

#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer(const vector<token> &tokens)
{
    raw_tokens = tokens;
    init();
}

void SyntaxAnalyzer::init()
{
    it = raw_tokens.begin();
    pf_tokens.clear();
    brackets_count = 0;
    buf = "";
}

void SyntaxAnalyzer::flush_buf()
{
    if (!buf.empty()) {
        pf_tokens.push_back(token {STR_T, buf});
        buf = "";
    }
}

void SyntaxAnalyzer::E(bool last)
{
    if (it >= raw_tokens.end()) {
        throw invalid_argument("Not enough arguments for binary operation!");
    }

    int cur_pos = pf_tokens.size();

    if (it->type != STR_T && it->type != CAT_T) {
        flush_buf();
    }

    switch (it->type) {
        case O_BR_T:
            brackets_count++;

            it++;
            E();
            if (it->type != C_BR_T) {
                throw invalid_argument("Brackets amount mismatch!");
            }
            brackets_count--;
            flush_buf();

            it++;
            O(cur_pos);
            break;
        case C_BR_T:
            if (brackets_count > 0) {
                return;
            } else {
                throw invalid_argument("Wrong ')'!");
            }
        case STR_T: {
            token tmp = *it;
            it++;
            if (O()) {
                pf_tokens.push_back(tmp);
            } else {
                if (tmp.lexeme.compare(".")) {
                    flush_buf();
                    pf_tokens.push_back(tmp);
                } else {
                    buf += tmp.lexeme;
                }
            }
            break;
        }
        case CAT_T:
            break;
        default:
            throw invalid_argument("Wrong operation syntax!");
    }

    if (it >= raw_tokens.end()) {
        return;
    }

    if (it->type == STR_T || it->type == O_BR_T) {
        pf_tokens.insert(pf_tokens.begin() + cur_pos, token {CAT_T, ""});
        E(true);
    }

    if (it->type == CAT_T) {
        if (it + 2 >= raw_tokens.end() || (it + 2)->type <= CAT_T) {
            it++;
            E();
        } else {
            pf_tokens.insert(pf_tokens.begin() + cur_pos, *it);
            flush_buf();

            it++;
            E(true);
        }
    }
    if (it->type == ENUM_T && !last) {
        pf_tokens.insert(pf_tokens.begin() + cur_pos, *it);
        flush_buf();

        it++;
        E();
    }
}

bool SyntaxAnalyzer::O(int pos)
{
    if (it < raw_tokens.end() && it->type > CAT_T) {
        if (pos >= 0) {
            pf_tokens.insert(pf_tokens.begin() + pos, *it);
        }
        token tmp = *it;
        it++;
        O(pos);
        if (pos == -1) {
            pf_tokens.push_back(tmp);
        }

        return true;
    }
    return false;
}

vector<token> SyntaxAnalyzer::analyze()
{
    init();

    if (raw_tokens.size() == 0) {
        return raw_tokens;
    }

    E();
    flush_buf();

    return pf_tokens;
}