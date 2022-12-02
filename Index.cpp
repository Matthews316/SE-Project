#include "Index.h"

void Index::insertWord(string w, int d){
    loadTree(w, d, 'w', words);
}

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

void Index::loadFilesWords(){
    loadFiles(words);
}

void Index::loadFilesPersons(){
    loadFiles(persons);
}

void Index::loadFilesOrgs(){
    loadFiles(orgs);
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
        outFile << indexVector[i] << 0 << endl;
    }
    outFile << "EndofFile";

    outFile.close();


}

void Index::loadFiles(AVLTree<Word> & tree) {
    ifstream textFile("WordFile.txt");
    if (textFile.fail()) {
        throw std::runtime_error("Text File Failed!");
    }
    string word;
    string docStr;
    string occurrenceStr;
    int doc;
    int occurrence;
    unordered_map<int, int> map;

    while (true) {
        // textFile >> word;
        getline(textFile, word);
        cout << word << endl;
        if (word == "EndofFile")
            break;
        while (true) {
            // textFile >> doc;
            getline(textFile, docStr, ' ');

            doc = stoi(docStr);            
            if (doc == 0) {
                break;
            }
            // textFile >> occurrence;
            getline(textFile, occurrenceStr);
            occurrence = stoi(occurrenceStr);

            cout << " " << occurrence << endl;
            map.insert(make_pair(doc, occurrence));
        }
        Word wObject(word, map);
        tree.insert(wObject);
        map.clear();
    }

    textFile.close();
}

AVLTree<Word>& Index::getWords() {
    return words;
}

AVLTree<Word>& Index::getPersons() {
    return persons;
}

AVLTree<Word>& Index::getOrgs() {
    return orgs;
}

Document Index::getDocument(int id){
    return documentMap[id];
}

void Index::addDocument(int id, Document& doc){
    documentMap[id] = doc;
}

int Index::numDocuments(){
    return documentMap.size();
}
