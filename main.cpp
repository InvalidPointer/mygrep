#include <iostream>
#include <cstring>
#include "Regexp.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        cout << "Wrong number of params! Usage: " << argv[0] << " %regexp% [search]" << endl;
        return 0;
    }

    Regexp r(argv[1]);
    if (argc == 3) {
        if (!strcmp(argv[2], "search")) {
            string str;
            while (cin >> str) {
                rc_result res = r.search(str);
                if (res.status) {
                    cout << res.result << endl;
                }
            }
        } else {
            cout << "Wrong param! Usage: " << argv[0] << " %regexp% [search]" << endl;
            return 0;
        }
    } else {
        string str;
        while (cin >> str) {
            if (r.match(str)) {
                cout << str << endl;
            }
        }
    }

    return 0;
}