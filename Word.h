//
// Created by cgm81 on 11/9/2022.
//

#ifndef FINALPROJEXAMPLES_WORD_H
#define FINALPROJEXAMPLES_WORD_H

#include <unordered_map>
#include <iterator>
#include <string>

#include "AVLTree.h"

using namespace std;


class Word {

public:

    Word();
    Word(string, unordered_map<int, int> &);
    bool operator == (const Word &) const;
    bool operator < (const Word &) const;
    bool operator > (const Word &) const;
    friend ostream & operator << (ostream &out, const Word &);
    void insertDoc(int);
    string getWord();

private:
    string wordElement;
    unordered_map<int, int> docs;

};
#endif //FINALPROJEXAMPLES_WORD_H
