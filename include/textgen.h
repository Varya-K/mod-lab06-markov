// Copyright 2022 UNN-IASR
#pragma once
#include <string>
#include <deque>
#include <vector>
#include <map>
#include <fstream>


class Textgen {
 public:
    Textgen(int prefix_size, std::string file_name);
    std::string getSuffix(prefix pref);
    std::string Gentext(int count_of_words);
    std::map<prefix, std::vector<std::string>> GetStateTab();

 private:
    std::map<prefix, std::vector<std::string>> statetab;
    int npref;
    prefix first_prefix;
};
