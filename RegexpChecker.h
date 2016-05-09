//
// Created by InvalidPointer on 5/8/2016.
//

#ifndef MYGREP_REGEXPCHECKER_H
#define MYGREP_REGEXPCHECKER_H


#include <vector>
#include <string>

#include "token.h"

using namespace std;

class RegexpChecker
{
private:
    vector<token> *sv;
    vector<token>::const_iterator svit;
    string *target;
    string::const_iterator tit;

    int skip_params = 0;

    bool check_op();
    bool op_str();
    bool op_enum();
    bool op_cat();
    bool op_iter(int min = 0, int max = -1);

    void skip_op();
public:
    RegexpChecker(vector<token> *v, string *s, vector<token>::const_iterator vit, string::const_iterator sit);
    ~RegexpChecker() {}

    bool check();
};


#endif //MYGREP_REGEXPCHECKER_H
