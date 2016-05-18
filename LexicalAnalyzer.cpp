#include "LexicalAnalyzer.h"

bool LexicalAnalyzer::isspecial(char ch)
{
    return string(".?+{}*[-]|()\\").find(ch) != string::npos;
}

string LexicalAnalyzer::is_num(const string &s)
{
    return to_string(stoi(s));
}

vector<token> LexicalAnalyzer::analyze(const string &expr)
{
    vector<token> toks;

    bool escaped = false;
    for (auto it = expr.begin(); it < expr.end(); it++) {
        if (!isgraph(*it)) {
            throw invalid_argument("Invalid symbol in regex!");
        }

        if (!isspecial(*it) || escaped) {
            if (!isspecial(*it) && escaped) {
                throw invalid_argument("Invalid escape character!");
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
                case '{': {
                    int pos = expr.find("}", it - expr.begin());
                    if (pos == string::npos) {
                        throw invalid_argument("Not enough '}'!");
                    } else {
                        string stok = expr.substr(it - expr.begin() + 1, pos - (it - expr.begin()) - 1);
                        it = expr.begin() + pos;

                        pos = stok.find(",");
                        if (pos == string::npos) {
                            toks.push_back(token {ITER_N_T, is_num(stok) + "," + is_num(stok)});
                        } else if (pos == 0) {
                            toks.push_back(token {ITER_N_T, "0," + is_num(stok.substr(1))});
                        } else if (pos == stok.size() - 1) {
                            toks.push_back(token {ITER_N_T, is_num(stok.substr(0, stok.size() - 1)) + ",-1"});
                        } else {
                            toks.push_back(token {ITER_N_T, is_num(stok.substr(0, pos)) + "," + is_num(stok.substr(pos + 1))});
                        }
                    }
                    break;
                }
                case '}':
                    throw invalid_argument("Unescaped '}'!");
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
                    throw invalid_argument("Unescaped special symbol!");
            }
        }
    }

    return toks;
}