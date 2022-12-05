#include "Word.h"

Word::Word() = default;

Word::Word(string w) { //constructor to convert search strings to word objects
    wordElement = w;
}

Word::Word(string w, unordered_map<int, int> &m) { //constructor for creating tree nodes with word and map of docs & occurrences
    wordElement = w;
    docs = m;
}

bool Word::operator == (const Word &rhs) const { //comparison operators
    return wordElement == rhs.wordElement;
}

bool Word::operator < (const Word &rhs) const { //comparison operators
    return wordElement < rhs.wordElement;
    
}

bool Word::operator > (const Word &rhs) const { //comparison operators
    return wordElement > rhs.wordElement;
}

ostream &operator << (ostream &out, const Word &w) {  //overloaded output stream operator for printing out words
    //and creating persistent files
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

//checks to see if document is new or already present for a word
void Word::insertDoc(int d) {
    auto ptr = docs.find(d);
    if (ptr != docs.end()) {
        ptr->second++; //if document found increment occurrence value
    } else {
        docs.insert(make_pair(d, 1)); //if document not found create new pair in map
    }
}

void Word::insertPersistentDoc(int d, int occ) {
    docs.insert(make_pair(d, occ)); //create new document pair in persistent data load
}

string Word::getWord() {
    return wordElement;
}

unordered_map<int, int> &Word::getDocs() {
    return docs;
}
