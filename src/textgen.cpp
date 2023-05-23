#include "textgen.h"

Textgen::Textgen(int prefix_size, string file_name): npref(prefix_size) {
    ifstream file(file_name);
    setlocale(LC_ALL, "Russian");
    string text1 = "", str;
    if (file.is_open()) {
        while (getline(file, str)) {
            text1 += str + " ";
        }
    }
    string text = "";
    bool previous_is_space = false;
    for (int i = 0; i < text1.length(); i++) {
        if (text1[i] != ' ') {
            text += text1[i];
            previous_is_space = false;
        }
        else if (previous_is_space == false) {
            text += text1[i];
            previous_is_space = true;
        }
    }
    file.close();
    prefix pref;
    string suff="";
    int first_index = 0;
    int second_index = text.find(' ');
    for (int i = 0; i < prefix_size; i++) {
        if (second_index == string::npos) {
            break;
        }
        pref.push_back(text.substr(first_index, second_index - first_index));
        first_index = second_index + 1;
        second_index = text.find(' ', first_index);
    }
    first_prefix = pref;
    while (second_index!=string::npos) {
        suff = text.substr(first_index, second_index - first_index);
        statetab[pref].push_back(suff);
        pref.pop_front();
        pref.push_back(suff);
        first_index = second_index + 1;
        second_index = text.find(' ', first_index);
    }
    suff = text.substr(first_index, text.length() - first_index);
    statetab[pref].push_back(suff);
}

string Textgen::getSuffix(prefix pref) {
    if (statetab.find(pref) == statetab.end()) return "";
    else {
        return statetab[pref][rand() % (statetab[pref].size())];
    }
}

string Textgen::Gentext(int count_of_words) {
    prefix pref = first_prefix;
    string result = "";
    for (int i = 0; i < pref.size(); i++) {
        if (i == pref.size() - 1) result += pref[i];
        else result += pref[i] + " ";
    }
    for (int i = 0; i < count_of_words-npref;i++) {
        string suff = getSuffix(pref);
        if (suff == "") break;
        result += " " + suff;
        pref.pop_front();
        pref.push_back(suff);
    }
    return result;
}


map<Textgen::prefix, vector<string>> Textgen::GetStateTab() {
    return statetab;
}
