#include <iostream>
#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "Regexp.h"

using namespace std;

int main()
{
    //vector<token> lv = la.analyze("123|a*|321|\\*abc\\\\");
    vector<token> lv = LexicalAnalyzer::analyze("(ab*|c)d|qt{1,2}*");
    SyntaxAnalyzer sa(lv);
    vector<token> sv = sa.analyze();
    for (auto it = sv.begin(); it < sv.end(); it++) {
        cout << "Lexeme: " << it->lexeme << " Token: " << it->type << endl;
    }

    Regexp r("la*");
    cout << "'" << r.search("hjklaaaaaddabedfbdfdbsbba") << "'" << endl;

    return 0;
}