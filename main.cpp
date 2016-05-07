#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"

using namespace std;

int main()
{
    LexicalAnalyzer la;
    //vector<token> lv = la.analyze("123|a*|321|\\*abc\\\\");
    vector<token> lv = la.analyze("(123|321)*");

    SyntaxAnalyzer sa;
    vector<token> sv = sa.analyze(lv);
    for (auto it = sv.begin(); it < sv.end(); it++) {
        cout << "Lexeme: " << it->lexeme << " Token: " << it->type << endl;
    }

    return 0;
}