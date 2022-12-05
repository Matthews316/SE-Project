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
    jMap.clear(); //combined map cleared before each new iteration
    const auto &[min, max]  = minmax(fMap, sMap, [](auto &a, auto &b) { return a.size() < b.size(); });
    for (auto &[key, value]: min) { //smallest map key used for lookup to minimize searches
        auto ptr = max.find(key); //check larger map for key
        if (ptr != max.end()) {
            jMap.emplace(key, value + ptr->second); //add common documents to combined map and add occurrences
        }
    }
    sMap = jMap; //set second map equal to combined map for next iteration
    fMap.clear(); //clear first map, so it can be loaded with new map from next word
}

Query::Query(Index*& i) {
    index = i;
}

//reads in search terms entered by the user
void Query::runQuery(Index *i) {
    cout << "Please enter search term(s): " << endl;
    string search;
    getline(cin, search);
    vector<string> wordVec;
    vector<string> personVec;
    vector<string> orgVec;
    istringstream ss(search); //use istringstream to parse search string into individual words
    string word;
    while (ss >> word) {
        if (word == "PERSON") { //check to see if PERSON string is passed
            ss >> word; //read next person word
            personVec.push_back(word); //add to person vector
        }
        else if (word == "ORG") { //check to see if ORG string is passed
            ss >> word; //read next org word
            orgVec.push_back(word); //add to org vector
        }
        else {
            wordVec.push_back(word); //add word(s) to word vector
        }
    }
    if (!wordVec.empty() && personVec.empty() && orgVec.empty()) { //if only words pass in word tree and words vector
        if ((wordVec.size() > 1)) { //if more than 1 word, perform AND search
            performAndSearch(wordVec, i->getWords());
        }
        else performSearch(wordVec[0], i->getWords()); //if only 1 word, perform simple search
    }
    else if (wordVec.empty() && !personVec.empty() && orgVec.empty()) { //if only person pass in person tree and person vector
        performSearch(personVec[0], i->getPersons());
    }
    else if (wordVec.empty() && personVec.empty() && !orgVec.empty()) { //if only org pass in org tree and org vector
        performSearch(orgVec[0], i->getOrgs());
    }
    else if (!wordVec.empty() && !personVec.empty() && orgVec.empty()) { //mixed search type: person and words
        performTwoMixedSearch(wordVec, personVec, i->getWords(), i->getPersons());
    }
    else if (!wordVec.empty() && personVec.empty() && !orgVec.empty()) { //mixed search type: org and words
        performTwoMixedSearch(wordVec, orgVec, i->getWords(), i->getOrgs());
    }
    else if (wordVec.empty() && !personVec.empty() && !orgVec.empty()) { //mixed search type: org and person
        performTwoMixedSearch(personVec, orgVec, i->getPersons(), i->getOrgs());
    }
    else if (!wordVec.empty() && !personVec.empty() && !orgVec.empty()) { //mixed search type: words, org and person
        performThreeMixedSearch(wordVec, personVec, orgVec, i->getWords(), i->getPersons(), i->getOrgs());
    }
}
//perform a simple search with one word, person or org
void Query::performSearch(const string & term, AVLTree<Word> & tree) {
    unordered_map<int, int> wMap;
    vector<pair<int, int>> resultVector;
    Word w(term);
    if (tree.contains(w)) {
        wMap = tree.findVal(w).getDocs(); //if tree contains word, return documents map
        auto ptr = wMap.begin(); //set up iterator
        while (ptr != wMap.end()) {
            resultVector.emplace_back(ptr->first, ptr->second);  //add all map values to a vector of pairs
            ptr++;
        }
        displayResults(resultVector, term); //display search results
    }
    else
        cout << "Search keyword " << "'" << term << "'" << " not found" << endl; //word not found in the tree
}
//perform a search with multiple words and find intersection of articles
void Query::performAndSearch(const vector<string> & termVec, AVLTree<Word> & tree) {
    unordered_map<int, int> xMap;
    unordered_map<int, int> yMap;
    unordered_map<int, int> cMap;
    vector<pair<int, int>> resultVector;
    for (size_t i = 0; i < termVec.size(); ++i) { //get all words from search
        Word w(termVec[i]);
        if (!tree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        } else {
            if (xMap.empty()) { //check to see if first map is document map is empty
                xMap = tree.findVal(w).getDocs(); //set first map equal to word docs
            } else {
                yMap = tree.findVal(w).getDocs(); //set second map equal to word docs
            }
        }
        if (!xMap.empty() && !yMap.empty()) { //if both maps populated, check for intersection
            findIntersection(xMap,yMap,cMap);
        }
    }
    auto itr = cMap.begin();
    while (itr != cMap.end()) {
        resultVector.emplace_back(itr->first, itr->second); //add intersection of articles to result vector
        itr++;
    }

    displayANDResults(resultVector, termVec); //display results
}
//perform a search with mixed search types (e.g., words and person)
void Query::performTwoMixedSearch(const vector<string> & fVec, const vector<string> & sVec, AVLTree<Word> & fTree, AVLTree<Word> & sTree) {
    unordered_map<int, int> xMap;
    unordered_map<int, int> yMap;
    unordered_map<int, int> cMap;
    vector<pair<int, int>> resultVector;
    for (size_t i = 0; i < fVec.size(); ++i) { //find intersection in first type vector
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
    for (size_t i = 0; i < sVec.size(); ++i) { //find intersection with second type vector
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
            resultVector.emplace_back(itr->first, itr->second); //add intersection of articles to result vector
            itr++;
        }
    //combine search terms of different type into one single vector for display function
    vector<string> terms;
    terms.reserve(fVec.size() + sVec.size());
    terms.insert(terms.end(), fVec.begin(), fVec.end());
    terms.insert(terms.end(), sVec.begin(), sVec.end());
    displayANDResults(resultVector, terms);
}

//perform a mixed search with all three search types (words, person, and org)
void Query::performThreeMixedSearch(const vector<string> & fVec, const vector<string> & sVec, const vector<string> & tVec, AVLTree<Word> & fTree, AVLTree<Word> & sTree, AVLTree<Word> & tTree) {
    unordered_map<int, int> xMap;
    unordered_map<int, int> yMap;
    unordered_map<int, int> cMap;
    vector<pair<int, int>> resultVector;
    for (size_t i = 0; i < fVec.size(); ++i) { //find intersection in first type vector
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
    for (size_t i = 0; i < sVec.size(); ++i) { //find intersection with second type vector
        Word w(sVec[i]);
        if (!sTree.contains(w)) {
            cout << "No documents found that contain all terms";
            return;
        } else {
            xMap = sTree.findVal(w).getDocs();
        }
        findIntersection(xMap,yMap,cMap);
    }
    for (size_t i = 0; i < tVec.size(); ++i) { //find intersection with third type vector
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
        resultVector.emplace_back(itr->first, itr->second); //add intersection of articles to result vector
        itr++;
    }
    //combine search terms of different type into one single vector for display function
    vector<string> terms;
    terms.reserve(fVec.size() + sVec.size() + tVec.size());
    terms.insert(terms.end(), fVec.begin(), fVec.end());
    terms.insert(terms.end(), sVec.begin(), sVec.end());
    terms.insert(terms.end(), tVec.begin(), tVec.end());
    displayANDResults(resultVector, terms);
}

//display results by relevancy
void Query::displayResults(vector<pair<int, int>> & rVec, const string & t) {
    sort(rVec.begin(), rVec.end(), sortVal); //sort results by value in descending order
    //display search term and number of articles
    cout << "Found " << rVec.size() << " document(s) containing search term " << "'" << t << "'" << endl;
    if (rVec.empty()) { //return if no results to display
        return;
    }
    else {
        cout << endl;
        cout << "Top 15 search results by relevancy:" << endl;
        for (size_t i = 0; i < 15; ++i) {
            if (i == rVec.size()) {
                break;
            }
            auto doc = index->getDocument(rVec[i].first);
            cout << i + 1 << "." << endl;
            cout << doc.getTitle() << endl;
            cout << doc.getPublication() << endl;
            cout << doc.getDate() << endl;
        }

        int id;
        cout << "\nEnter document id to display text: ";
        cin >> id;

        if (id > rVec.size() || id < 0) {
            cout << "Invalid id" << endl;
        } else {
            auto doc = index->getDocument(rVec[id-1].first);
            cout << doc.getText() << endl << endl;
        }
        
        
    }
}

void Query::displayANDResults(vector<pair<int, int>> & rVec, const vector<string> & tVec) {
    sort(rVec.begin(), rVec.end(), sortVal); //sort results by value in descending order
    cout << "Found " << rVec.size() << " document(s) containing search terms ";
    for (size_t i = 0; i < tVec.size(); ++i) { //display all search terms and number of common articles
        if (i < tVec.size() - 1) {
            cout << "'" << tVec[i] << "'" << " + ";
        }
        else {
            cout << "'" << tVec[i] << "'" << endl;
        }
    }
    if (rVec.empty()) { //return if no results to display
        return;
    }
    else {
        cout << endl;
        cout << "Top 15 search results by relevancy:" << endl;
        for (size_t i = 0; i < 15; ++i) {
            if (i == rVec.size()) {
                break;
            }
            cout << rVec[i].first << " " << rVec[i].second << endl; //display 15 results with most occurrences
        }
    }
}