//
// Created by InvalidPointer on 07.05.2016.
//

#ifndef MYGREP_SYNTAXANALYZER_H
#define MYGREP_SYNTAXANALYZER_H


#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <stdexcept>

#include "token.h"

using namespace std;

class SyntaxAnalyzer
{
private:
    vector<token> raw_tokens;
    vector<token> pf_tokens;
    vector<token>::iterator it;

    int brackets_count;
    string buf;

    void init();

    void E(bool last = false);
    bool O(int pos = -1);

    bool flush_buf(int pos = -1);
public:
    SyntaxAnalyzer(const vector<token> &tokens);
    ~SyntaxAnalyzer() {}

    vector<token> analyze();
};


#endif //MYGREP_SYNTAXANALYZER_H
