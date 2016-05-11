//
// Created by InvalidPointer on 07.05.2016.
//

#ifndef MYGREP_LEXICALANALYZER_H
#define MYGREP_LEXICALANALYZER_H


#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

#include "token.h"

using namespace std;

class LexicalAnalyzer
{
private:
    static bool isspecial(char ch);
    static string is_num(const string &s);
public:
    LexicalAnalyzer() {}
    ~LexicalAnalyzer() {}

    static vector<token> analyze(const string &s);
};


#endif //MYGREP_LEXICALANALYZER_H
