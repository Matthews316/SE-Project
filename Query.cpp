//
// Created by cgm81 on 12/1/2022.
//

#include "Query.h"

//need to create comparison function for vector of pairs
bool sortVal (const pair<int, int> &lhs, const pair<int, int> &rhs) {
    return (lhs.second > rhs.second);
}

//function for finding the intersection of documents between search terms; code sourced from stack overflow
void findIntersection (unordered_map<int, int> & fMap, unordered_map<int, int> & sMap, unordered_map<int, int> & jMap) {
    jMap.clear();
    const auto &[min, max]  = minmax(fMap, sMap, [](auto &a, auto &b) { return a.size() < b.size(); });
    for (auto &[key, value]: min) {
        auto ptr = max.find(key);
        if (ptr != max.end()) {
            jMap.emplace(key, value + ptr->second);
        }
    }
    sMap = jMap;
    fMap.clear();
}

Query::Query() = default;

void Query::runQuery(Index *i) {
    cout << "Please enter search term(s): " << endl;
    string search;
    getline(cin, search);
    vector<string> wordVec;
    vector<string> personVec;
    vector<string> orgVec;
    istringstream ss(search);
    string word;
    while (ss >> word) {
        if (word == "PERSON") {
            ss >> word;
            personVec.push_back(word);
        }
        else if (word == "ORG") {
            ss >> word;
            orgVec.push_back(word);
        }
        else {
            wordVec.push_back(word);
        }
    }
    if (!wordVec.empty() && personVec.empty() && orgVec.empty()) {
        if ((wordVec.size() > 1)) {
            performAndSearch(wordVec, i->getWords());
        }
        else performSearch(wordVec[0], i->getWords());
    }
    else if (wordVec.empty() && !personVec.empty() && orgVec.empty()) {
        performSearch(personVec[0], i->getPersons());
    }
    else if (wordVec.empty() && personVec.empty() && !orgVec.empty()) {
        performSearch(orgVec[0], i->getOrgs());
    }
    else if (!wordVec.empty() && !personVec.empty() && orgVec.empty()) {
        performTwoMixedSearch(wordVec, personVec, i->getWords(), i->getPersons());
    }
    else if (!wordVec.empty() && personVec.empty() && !orgVec.empty()) {
        performTwoMixedSearch(wordVec, orgVec, i->getWords(), i->getOrgs());
    }
    else if (wordVec.empty() && !personVec.empty() && !orgVec.empty()) {
        performTwoMixedSearch(personVec, orgVec, i->getPersons(), i->getOrgs());
    }
    else if (!wordVec.empty() && !personVec.empty() && !orgVec.empty()) {
        performThreeMixedSearch(wordVec, personVec, orgVec, i->getWords(), i->getPersons(), i->getOrgs());
    }
}

void Query::performSearch(const string & term, AVLTree<Word> & tree) {
    unordered_map<int, int> wMap;
    vector<pair<int, int>> resultVector;
    Word w(term);
    if (tree.contains(w)) {
        wMap = tree.findVal(w).getDocs();
        auto ptr = wMap.begin();
        while (ptr != wMap.end()) {
            resultVector.emplace_back(ptr->first, ptr->second);
            ptr++;
        }
        displayResults(resultVector, term);
    }
    else
        cout << "Search keyword " << "'" <<term << "'" << " not found" << endl;
}

void Query::performAndSearch(const vector<string> & termVec, AVLTree<Word> & tree) {
    unordered_map<int, int> xMap;
    unordered_map<int, int> yMap;
    unordered_map<int, int> cMap;
    vector<pair<int, int>> resultVector;
    for (size_t i = 0; i < termVec.size(); ++i) {
        Word w(termVec[i]);
        if (!tree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        } else {
            if (xMap.empty()) {
                xMap = tree.findVal(w).getDocs();
            } else {
                yMap = tree.findVal(w).getDocs();
            }
        }
        if (!xMap.empty() && !yMap.empty()) {
            findIntersection(xMap,yMap,cMap);
        }
    }
    auto itr = cMap.begin();
    while (itr != cMap.end()) {
        resultVector.emplace_back(itr->first, itr->second);
        itr++;
    }

    displayANDResults(resultVector, termVec);
}

void Query::performTwoMixedSearch(const vector<string> & fVec, const vector<string> & sVec, AVLTree<Word> & fTree, AVLTree<Word> & sTree) {
    unordered_map<int, int> xMap;
    unordered_map<int, int> yMap;
    unordered_map<int, int> cMap;
    vector<pair<int, int>> resultVector;
    for (size_t i = 0; i < fVec.size(); ++i) {
        Word w(fVec[i]);
        if (!fTree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        }
        else {
            if (xMap.empty()) {
                xMap = fTree.findVal(w).getDocs();
            }
            else {
                yMap = fTree.findVal(w).getDocs();
            }
        }
        if (!xMap.empty() && !yMap.empty()) {
            findIntersection(xMap,yMap,cMap);
        }
    }
    for (size_t i = 0; i < sVec.size(); ++i) {
        Word w(sVec[i]);
        if (!sTree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        } else {
            xMap = sTree.findVal(w).getDocs();
        }
            findIntersection(xMap,yMap,cMap);
    }
        auto itr = cMap.begin();
        while (itr != cMap.end()) {
            resultVector.emplace_back(itr->first, itr->second);
            itr++;
        }
        displayTwoMixedResults(resultVector, fVec, sVec);
}


void Query::performThreeMixedSearch(const vector<string> & fVec, const vector<string> & sVec, const vector<string> & tVec, AVLTree<Word> & fTree, AVLTree<Word> & sTree, AVLTree<Word> & tTree) {
    unordered_map<int, int> xMap;
    unordered_map<int, int> yMap;
    unordered_map<int, int> cMap;
    vector<pair<int, int>> resultVector;
    for (size_t i = 0; i < fVec.size(); ++i) {
        Word w(fVec[i]);
        if (!fTree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        }
        else {
            if (xMap.empty()) {
                xMap = fTree.findVal(w).getDocs();
            }
            else {
                yMap = fTree.findVal(w).getDocs();
            }
        }
        if (!xMap.empty() && !yMap.empty()) {
            findIntersection(xMap,yMap,cMap);
        }
    }
    for (size_t i = 0; i < sVec.size(); ++i) {
        Word w(sVec[i]);
        if (!sTree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        } else {
            xMap = sTree.findVal(w).getDocs();
        }
        findIntersection(xMap,yMap,cMap);
    }
    for (size_t i = 0; i < tVec.size(); ++i) {
        Word w(tVec[i]);
        if (!tTree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        } else {
            xMap = tTree.findVal(w).getDocs();
        }
        findIntersection(xMap,yMap,cMap);
    }
    auto itr = cMap.begin();
    while (itr != cMap.end()) {
        resultVector.emplace_back(itr->first, itr->second);
        itr++;
    }
    displayThreeMixedResults(resultVector, fVec, sVec, tVec);
}

void Query::displayResults(vector<pair<int, int>> & rVec, const string & t) {
    sort(rVec.begin(), rVec.end(), sortVal);
    cout << "Found " << rVec.size() << " document(s) containing search term " << "'" << t << "'" << endl;
    if (rVec.empty()) {
        return;
    }
    else {
        cout << endl;
        cout << "Top 15 search results by relevancy:" << endl;
        for (size_t i = 0; i < 15; ++i) {
            if (i == rVec.size()) {
                break;
            }
            cout << rVec[i].first << " " << rVec[i].second << endl;
        }
    }
}

void Query::displayANDResults(vector<pair<int, int>> & rVec, const vector<string> & tVec) {
    sort(rVec.begin(), rVec.end(), sortVal);
    cout << "Found " << rVec.size() << " document(s) containing search terms ";
    for (size_t i = 0; i < tVec.size(); ++i) {
        if (i < tVec.size() - 1) {
            cout << "'" << tVec[i] << "'" << " + ";
        }
        else {
            cout << "'" << tVec[i] << "'" << endl;
        }
    }
    if (rVec.empty()) {
        return;
    }
    else {
        cout << endl;
        cout << "Top 15 search results by relevancy:" << endl;
        for (size_t i = 0; i < 15; ++i) {
            if (i == rVec.size()) {
                break;
            }
            cout << rVec[i].first << " " << rVec[i].second << endl;
        }
    }
}



void Query::displayTwoMixedResults(vector<pair<int, int>> & rVec, const vector<string> & fVec, const vector<string> & sVec) {
    sort(rVec.begin(), rVec.end(), sortVal);
    cout << "Found " << rVec.size() << " document(s) containing search terms ";
    for (size_t i = 0; i < fVec.size(); ++i) {
            cout << "'" << fVec[i] << "'" << " + ";
    }
    for (size_t i = 0; i < sVec.size(); ++i) {
        if (i < sVec.size() - 1) {
            cout << "'" << sVec[i] << "'" << " + ";
        }
        else {
            cout << "'" << sVec[i] << "'" << endl;
        }
    }
    if (rVec.empty()) {
        return;
    }
    else {
        cout << endl;
        cout << "Top 15 search results by relevancy:" << endl;
        for (size_t i = 0; i < 15; ++i) {
            if (i == rVec.size()) {
                break;
            }
            cout << rVec[i].first << " " << rVec[i].second << endl;
        }
    }
}

void Query::displayThreeMixedResults(vector<pair<int, int>> & rVec, const vector<string> & fVec, const vector<string> & sVec, const vector<string> & tVec) {
    sort(rVec.begin(), rVec.end(), sortVal);
    cout << "Found " << rVec.size() << " document(s) containing search terms ";
    for (size_t i = 0; i < fVec.size(); ++i) {
        cout << "'" << fVec[i] << "'" << " + ";
    }
    for (size_t i = 0; i < sVec.size(); ++i) {
            cout << "'" << sVec[i] << "'" << " + ";
    }
    for (size_t i = 0; i < tVec.size(); ++i) {
        if (i < tVec.size() - 1) {
            cout << "'" << tVec[i] << "'" << " + ";
        }
        else {
            cout << "'" << tVec[i] << "'" << endl;
        }
    }
    if (rVec.empty()) {
        return;
    }
    else {
        cout << endl;
        cout << "Top 15 search results by relevancy:" << endl;
        for (size_t i = 0; i < 15; ++i) {
            if (i == rVec.size()) {
                break;
            }
            cout << rVec[i].first << " " << rVec[i].second << endl;
        }
    }
}
