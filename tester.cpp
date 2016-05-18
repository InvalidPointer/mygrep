#include <iostream>
#include <fstream>
#include "dirent.h"
#include "sys/stat.h"

#include "Regexp.h"

using namespace std;

struct test
{
    int num;
    vector<int> lines;
};

vector<string> get_files_in_dir(const string &dir_name);

int main(int argc, char **argv)
{
    if (argc != 3) {
        cout << "Wrong params! Usage: " << argv[0] << " %path_to_tests% {match|search}" << endl;
        return 0;
    }
    int mode = !string(argv[2]).compare("search");

    string tests_dir = argv[1];
    vector<string> test_fnames = get_files_in_dir(tests_dir + "/expressions");
    vector<test> error_tests;
    for (auto it = test_fnames.begin(); it < test_fnames.end(); it++) {
        test t{-1};

        ifstream expr_file (tests_dir + "/expressions/" + *it);
        string expr;
        expr_file >> expr;
        Regexp r(expr);

        ifstream str_file (tests_dir + "/strings/" + *it);
        ifstream res_file (tests_dir + "/answers/" + *it);
        string test_string;
        int line = 0;
        while (str_file >> test_string) {
            if (!mode) {
                bool res;
                res_file >> res;
                if (r.match(test_string) != res) {
                    t.num = it - test_fnames.begin();
                    t.lines.push_back(line);
                }
            } else {
                string res;
                res_file >> res;
                rc_result rc_res = r.search(test_string);
                if (rc_res.status) {
                    if (rc_res.result.compare(res)) {
                        t.num = it - test_fnames.begin();
                        t.lines.push_back(line);
                    }
                } else {
                    if (res.compare("NotFound!")) {
                        t.num = it - test_fnames.begin();
                        t.lines.push_back(line);
                    }
                }
            }
            line++;
        }

        if (t.num != -1) {
            error_tests.push_back(t);
        }
    }

    cout << "OK in " << test_fnames.size() - error_tests.size() << "/" << test_fnames.size() << " tests!" << endl;
    if (error_tests.size()) {
        cout << "Errors in:" << endl;
    }
    for (auto it = error_tests.begin(); it < error_tests.end(); it++) {
        cout << "Test: " << it->num + 1 << " Lines: ";
        for (auto inner_it = it->lines.begin(); inner_it < it->lines.end(); inner_it++) {
            cout << *inner_it + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}


vector<string> get_files_in_dir(const string &dir_name) {
    vector<string> out;
    DIR *dir;
    class dirent *ent;
    class stat st;

    dir = opendir(dir_name.c_str());
    while ((ent = readdir(dir)) != NULL) {
        const string file_name = ent->d_name;
        const string full_file_name = dir_name + "/" + file_name;

        if (file_name[0] == '.')
            continue;

        if (stat(full_file_name.c_str(), &st) == -1)
            continue;

        if ((st.st_mode & S_IFDIR) != 0)
            continue;

        out.push_back(file_name);
    }
    closedir(dir);

    return out;
}