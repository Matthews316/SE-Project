#include "Index.h"

void Index::insertWord(string w, int d){
    loadTree(w, d, 'w', words);
}

// Index::Index() {
//     words = AVLTree<Word>();
//     persons = AVLTree<Word>();
//     orgs = AVLTree<Word>();
// }

void Index::insertPerson(string w, int d){
    loadTree(w, d, 'p', persons);
}

void Index::insertOrgs(string w, int d){
    loadTree(w, d, 'o', orgs);
}


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

void Index::prettyPrintWordTree(){
    words.prettyPrintTree();
}

void Index::prettyPrintPersonTree(){
    persons.prettyPrintTree();
}

void Index::prettyPrintOrgsTree(){
    orgs.prettyPrintTree();
}

void Index::generateFilesWords(){
    generateFiles(words, 'w');
}

void Index::generateFilesPersons(){
    generateFiles(persons, 'p');
}

void Index::generateFilesOrgs(){
    generateFiles(orgs, 'o');
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

// void loadFiles() {
//     ifstream textFile("WordFile.txt");
//     if (textFile.fail()) {
//         throw std::runtime_error("Text File Failed!");
//     }
//     string word;
//     int doc;
//     int occurrence;
//     unordered_map<int, int> map;

//     while (true) {
//         textFile >> word;
//         if (word == "EndofFile")
//             break;
//         while (true) {
//             textFile >> doc;
//             if (doc == -1) {
//                 break;
//             }
//             textFile >> occurrence;
//             map.insert(make_pair(doc, occurrence));
//         }
//         Word wObject(word, map);
//         wTree.insert(wObject);
//         map.clear();
//     }

//     textFile.close();
// }
