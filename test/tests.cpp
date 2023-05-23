// Copyright 2021 GHA Test Team
#include <gtest/gtest.h>
#include "textgen.h"

TEST(Task1, TestPrefixCurrenSize) {
    int NPREF = 3;
    Textgen g(NPREF, "Test1.txt");
    auto statetab = g.GetStateTab();
    for (auto prefix_suf : statetab) {
        EXPECT_EQ(NPREF, prefix_suf.first.size());
    }
}


TEST(Task2, TestPairPrefixSuffix) {
    int NPREF = 2;
    Textgen g(NPREF, "Test1.txt");
    std::ifstream file("Test1.txt");
    std::string text1 = "", str;
    if (file.is_open()) {
        while (getline(file, str)) {
            text1 += str + " ";
        }
    }
    std::string text = "";
    bool previous_is_space = false;
    for (int i = 0; i < text1.length(); i++) {
        if (text1[i] != ' ') {
            text += text1[i];
            previous_is_space = false;
        } else {
            if (previous_is_space == false) {
                text += text1[i];
                previous_is_space = true;
            }
        }
    }
    file.close();
    auto statetab = g.GetStateTab();
    for (auto prefix_suf : statetab) {
        std::string pref = "";
        for (int i = 0; i < NPREF; i++) {
            if (i == NPREF - 1) {
                pref += prefix_suf.first[i];
            } else {
                pref += prefix_suf.first[i] + " ";
            }
        }
        for (std::string suf : prefix_suf.second) {
            EXPECT_TRUE(text.find(pref+" "+suf) != std::string::npos);
        }
    }
}


TEST(Task3, TestSingleSuffix) {
    int NPREF = 2;
    Textgen g = Textgen(NPREF, "Test1.txt");
    prefix pref1;
    pref1.push_back("am");
    pref1.push_back("glad");
    EXPECT_EQ(g.getSuffix(pref1), "to");
    prefix pref2;
    pref2.push_back("Hello,");
    pref2.push_back("friend,");
    EXPECT_EQ(g.getSuffix(pref2), "I");
}

TEST(Task4, TestMultipleSuffix) {
    int NPREF = 2;
    Textgen g = Textgen(NPREF, "Test1.txt");
    prefix pref1;
    pref1.push_back("I");
    pref1.push_back("am");
    std::string suf1 = g.getSuffix(pref1);
    EXPECT_TRUE((suf1 == "glad") || (suf1 == "a") || (suf1 == "thinking"));
    prefix pref2;
    pref2.push_back("glad");
    pref2.push_back("to");
    std::string suf2 = g.getSuffix(pref2);
    EXPECT_TRUE((suf2 == "see") || (suf2 == "be"));
}

TEST(Task5, TestSize) {
    int NPREF = 2;
    Textgen g = Textgen(NPREF, "Test1.txt");
    std::string text = g.Gentext(8);
    EXPECT_TRUE((text == "Hello, world, I am glad to see you!") ||
                (text == "Hello, world, I am a part of you!") ||
                (text == "Hello, world, I am thinking of you! I") ||
                (text == "Hello, world, I am thinking of you! Hello,") ||
                (text == "Hello, world, I am glad to be here"));
}
