
#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H

#include <fstream>
#include "Word.h"
#include "AVLTree.h"



class Index {

public:

    void loadTree(string w, int d, char t, AVLTree<Word>&);
    void generateFiles(AVLTree<Word> &, char);

private:

};



#endif //FINALPROJEXAMPLES_INDEX_H
