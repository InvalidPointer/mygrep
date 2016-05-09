#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Regexp.h"

using namespace std;

int main()
{
    //vector<token> lv = la.analyze("123|a*|321|\\*abc\\\\");
    vector<token> lv = LexicalAnalyzer::analyze(".+");
    vector<token> sv = SyntaxAnalyzer::analyze(lv);
    for (auto it = sv.begin(); it < sv.end(); it++) {
        cout << "Lexeme: " << it->lexeme << " Token: " << it->type << endl;
    }

    Regexp r("a?b");
    cout << r.match("aab") << endl;

    return 0;
}