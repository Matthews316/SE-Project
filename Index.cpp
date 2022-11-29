

#include "Index.h"

void Index::loadTree(string w, int d, char t, AVLTree<Word> & tree) {

    if (t == 'w') {
        unordered_map<int, int> wMap;
        Word tWord(w, wMap);
        if (!tree.contains(tWord)) {
            wMap.insert(make_pair(d, 1));
            Word wNode(w, wMap);
            tree.insert(wNode);
        } else {
            tree.findVal(tWord).insertDoc(d);
        }
    }
    else if (t == 'p') {
        unordered_map<int, int> pMap;
        Word person(w, pMap);
        if (!tree.contains(person)) {
            pMap.insert(make_pair(d, 1));
            Word pNode(w,pMap);
            tree.insert(pNode);
        }
        else {
            tree.findVal(person).insertDoc(d);
        }
    }
    else if (t == 'o') {
        unordered_map<int, int> oMap;
        Word org(w, oMap);
        if (!tree.contains(org)) {
            oMap.insert(make_pair(d, 1));
            Word oNode(w,oMap);
            tree.insert(oNode);
        }
        else {
            tree.findVal(org).insertDoc(d);
        }
    }
}

void Index::generateFiles(AVLTree<Word> & tree, char t) {
    vector<Word> indexVector;
    tree.storeTree(indexVector);
    string fileName;
    if (t == 'w') {
        fileName = "WordFile.txt";
    }
    else if (t == 'p') {
        fileName = "PeopleFile.txt";
    }
    else if (t == 'o') {
        fileName = "OrgFile.txt";
    }
    else {
        throw std::runtime_error("Incorrect file type chosen");
    }
    ofstream outFile(fileName);
    if (!outFile)
        cout << "File open error!" << endl;
    for (size_t i = 0; i < indexVector.size(); ++i) {
        outFile << indexVector[i] << -1 << endl;
    }
    outFile << "EndofFile";

    outFile.close();
}






