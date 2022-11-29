//
// Created by cgm81 on 11/9/2022.
//

#include "Word.h"

Word::Word() = default;

Word::Word(string w, unordered_map<int, int> &m) {
    wordElement = w;
    docs = m;
}

bool Word::operator == (const Word &rhs) const {
    return wordElement == rhs.wordElement;
}

bool Word::operator < (const Word &rhs) const {
    return wordElement < rhs.wordElement;
}

bool Word::operator > (const Word &rhs) const {
    return wordElement > rhs.wordElement;
}

ostream &operator << (ostream &out, const Word &w) {
    out << w.wordElement << endl;
    for (auto &p : w.docs)
    out << p.first << " " << p.second << endl;
    return out;
}

void Word::insertDoc(int d) {
    auto ptr = docs.find(d);
    if (ptr != docs.end()) {
        ptr->second++;
    } else {
        docs.insert(make_pair(d, 1));
    }
}

string Word::getWord() {
    return wordElement;
}









