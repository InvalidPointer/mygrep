#include <iostream>
#include <cstring>
#include "Regexp.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        cerr << "Wrong number of params! Usage: " << argv[0] << " %regexp% [search]" << endl;
        return 0;
    }

    try {
        Regexp r(argv[1]);

        if (argc == 3) {
            if (!strcmp(argv[2], "search")) {
                string str;
                while (getline(cin, str)) {
                    rc_result res = r.search(str);
                    if (res.status) {
                        cout << res.result << endl;
                    }
                }
            } else {
                cerr << "Wrong param! Usage: " << argv[0] << " %regexp% [search]" << endl;
                return 0;
            }
        } else {
            string str;
            while (getline(cin, str)) {
                if (r.match(str)) {
                    cout << str << endl;
                }
            }
        }
    } catch (const std::exception & ex) {
        cerr << ex.what() << endl;
    }

    return 0;
}