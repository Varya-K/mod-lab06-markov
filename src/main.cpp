// Copyright 2022 UNN-IASR
#include <iostream>
#include "textgen.h"

int main() {
    const int NPREF = 2;
    const int MAXGEN = 1000;
    Textgen g = Textgen(NPREF, "Text2.txt");
    cout << g.Gentext(MAXGEN);
}
