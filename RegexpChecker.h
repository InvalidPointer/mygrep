//
// Created by InvalidPointer on 5/8/2016.
//

#ifndef MYGREP_REGEXPCHECKER_H
#define MYGREP_REGEXPCHECKER_H


#include <vector>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "token.h"
#include "rc_result.h"

using namespace std;

class RegexpChecker
{
private:
    bool child;

    const vector<token> *sv;
    vector<token>::const_iterator svit;
    const string *target;
    const string::const_iterator btit;
    string::const_iterator tit;

    bool search;

    bool check_op();
    bool op_str();
    bool op_enum();
    bool op_cat();
    bool op_iter(int min = 0, int max = -1);

    void skip_op();
public:
    RegexpChecker(const vector<token> *v, const string *s, vector<token>::const_iterator vit, string::const_iterator sit, bool search = false);
    ~RegexpChecker() {}

    rc_result check();
};


#endif //MYGREP_REGEXPCHECKER_H
