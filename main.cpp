#include <iostream>
#include "LexicalAnalyzer.h"

using namespace std;

int main()
{
    LexicalAnalyzer la;
    vector<token> lv = la.analyze("123|a*|321|\\*abc\\\\");
    for (auto it = lv.begin(); it < lv.end(); it++) {
        cout << "Lexeme: " << it->lexeme << " Token: " << it->type << endl;
    }

    return 0;
}