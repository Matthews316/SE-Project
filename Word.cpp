#include "Word.h"

Word::Word() = default;

Word::Word(string w) {
    wordElement = w;
}

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
    int count = 0;
    int size = w.docs.size();
    for (auto it = w.docs.begin(); it != w.docs.end(); ++it) {
        if (count == size-1) {
            out << w.wordElement << "\t" << it->first << "\t" << it->second;
        } else {
            out << w.wordElement << "\t" << it->first << "\t" << it->second << endl;
        }
        count++;
    }
    return out;
}

// New param for occ
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

unordered_map<int, int> &Word::getDocs() {
    return docs;
}