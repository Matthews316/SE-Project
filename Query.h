//
// Created by cgm81 on 12/1/2022.
//

#ifndef FINALPROJEXAMPLES_QUERY_H
#define FINALPROJEXAMPLES_QUERY_H

#include "AVLTree.h"
#include "Word.h"
#include "Index.h"
#include <sstream>

using namespace std;

class Query {

public:
    Query();
    void runQuery(Index *);
    void performSearch(const string &, AVLTree<Word> &);
    void performAndSearch(const vector<string> &, AVLTree<Word> &);
    void performTwoMixedSearch(const vector<string> &, const vector<string> &, AVLTree<Word> &, AVLTree<Word> &);
    void performThreeMixedSearch(const vector<string> &, const vector<string> &, const vector<string> &, AVLTree<Word> &, AVLTree<Word> &, AVLTree<Word> &);
    void displayResults(vector<pair<int, int>> &, const string &);
    void displayANDResults(vector<pair<int, int>> &, const vector<string> &);
    void displayTwoMixedResults(vector<pair<int, int>> &, const vector<string> &, const vector<string> &);
    void displayThreeMixedResults(vector<pair<int, int>> &, const vector<string> &, const vector<string> &, const vector<string> &);

private:

};

#endif //FINALPROJEXAMPLES_QUERY_H