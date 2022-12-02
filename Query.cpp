//
// Created by cgm81 on 12/1/2022.
//

#include "Query.h"

void Query::performSearch(string term, AVLTree<Word> & tree) {
    unordered_map<int, int> wMap;
    vector<pair<int, int>> resultVector;
    Word w(term);
    if (tree.contains(w)) {
       wMap = tree.findVal(w).getDocs();
        auto ptr = wMap.begin();
        while (ptr != wMap.end()) {
            resultVector.push_back(make_pair(ptr->first, ptr->second));
            ptr++;
        }
    }
}
