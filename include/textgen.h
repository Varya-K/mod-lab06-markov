#pragma once
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

class Textgen
{
public:
    typedef deque<string> prefix;
    Textgen(int prefix_size, string file_name);
    string getSuffix(prefix pref);
    string Gentext(int count_of_words);
    map<prefix, vector<string>> GetStateTab();

private:
    map<prefix, vector<string>> statetab;
    int npref;
    prefix first_prefix;
};
