//
// Created by cgm81 on 12/1/2022.
//

#ifndef FINALPROJEXAMPLES_QUERY_H
#define FINALPROJEXAMPLES_QUERY_H

#include "AVLTree.h"
#include "Word.h"
#include "Index.h"

using namespace std;

class Query {

public:
    void performSearch(string, AVLTree<Word> &);
    void rankResults(vector<pair<int, int>> &);

private:

};

#endif //FINALPROJEXAMPLES_QUERY_H
