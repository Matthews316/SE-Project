#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H

#include <fstream>

#include "Word.h"
#include "AVLTree.h"

class Index {

public:
    Index() = default;
    void insertWord(string w, int d);
    void insertPerson(string w, int d);
    void insertOrgs(string w, int d);
    void loadTree(string w, int d, char t, AVLTree<Word>&);
    void generateFiles(AVLTree<Word> &, char);
    void prettyPrintWordTree();
    void prettyPrintPersonTree();
    void prettyPrintOrgsTree();

private:
    AVLTree<Word> words;
    AVLTree<Word> persons;
    AVLTree<Word> orgs;

};



#endif //FINALPROJEXAMPLES_INDEX_H
