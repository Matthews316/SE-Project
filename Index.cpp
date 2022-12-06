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


// New param for occ
void Index::loadTree(string w, int d, char t, AVLTree<Word> & tree) {

    if (t == 'w') { //word tree
        unordered_map<int, int> wMap;
        Word tWord(w, wMap); //create word object with search term and map with docs and occurrences
        if (!tree.contains(tWord)) { //if tree doesn't contain word create a new node and map
            wMap.insert(make_pair(d, 1));
            Word wNode(w, wMap);
            tree.insert(wNode);
        } else {
            tree.findVal(tWord).insertDoc(d); //if tree contains word add document if doc doesn't exist or increment
            //occurrence if doc already exists
        }
    }
    else if (t == 'p') { //person tree
        unordered_map<int, int> pMap;
        Word person(w, pMap); //create word object with search term and map with docs and occurrences
        if (!tree.contains(person)) { //if tree doesn't contain word create a new node and map
            pMap.insert(make_pair(d, 1));
            Word pNode(w,pMap);
            tree.insert(pNode);
        }
        else {
            tree.findVal(person).insertDoc(d); //if tree contains word add document if doc doesn't exist or increment
            //occurrence if doc already exists
        }
    }
    else if (t == 'o') { //org tree
        unordered_map<int, int> oMap;
        Word org(w, oMap);
        if (!tree.contains(org)) { //if tree doesn't contain word create a new node and map
            oMap.insert(make_pair(d, 1)); //create word object with search term and map with docs and occurrences
            Word oNode(w,oMap);
            tree.insert(oNode);
        }
        else {
            tree.findVal(org).insertDoc(d); //if tree contains word add document if doc doesn't exist or increment
            //occurrence if doc already exists
        }
    }
}

//function for loading persistent data into the trees
void Index::loadPersistentTree(string w, int d, char t, AVLTree<Word> & tree, int occ) {

    if (t == 'w') {
        unordered_map<int, int> wMap;
        Word tWord(w, wMap);
        if (!tree.contains(tWord)) {
            wMap.insert(make_pair(d, occ)); //occurrence used here instead of value of 1
            Word wNode(w, wMap);
            tree.insert(wNode);
        } else {
            tree.findVal(tWord).insertPersistentDoc(d, occ); //occurrence used here instead of value of 1
        }
    }
    else if (t == 'p') {
        unordered_map<int, int> pMap;
        Word person(w, pMap);
        if (!tree.contains(person)) {
            pMap.insert(make_pair(d, occ)); //occurrence used here instead of value of 1
            Word pNode(w,pMap);
            tree.insert(pNode);
        }
        else {
            tree.findVal(person).insertPersistentDoc(d, occ); //occurrence used here instead of value of 1
        }
    }
    else if (t == 'o') {
        unordered_map<int, int> oMap;
        Word org(w, oMap);
        if (!tree.contains(org)) {
            oMap.insert(make_pair(d, occ)); //occurrence used here instead of value of 1
            Word oNode(w,oMap);
            tree.insert(oNode);
        }
        else {
            tree.findVal(org).insertPersistentDoc(d, occ); //occurrence used here instead of value of 1
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
    loadFiles(words, "WordFile.tsv", 'w');
}

void Index::loadFilesPersons(){
    loadFiles(persons, "PeopleFile.tsv", 'p');
}

void Index::loadFilesOrgs(){
    loadFiles(orgs, "OrgFile.tsv", 'o');
}

//generate tsv files for saving persistent data for all trees
void Index::generateFiles(AVLTree<Word> & tree, char t) {
    vector<Word> indexVector; //create vector to store tree nodes
    tree.storeTree(indexVector);  //populate vector with all tree nodes
    string fileName;
    if (t == 'w') { //word tree
        fileName = "WordFile.tsv";
    }
    else if (t == 'p') { //person tree
        fileName = "PeopleFile.tsv";
    }
    else if (t == 'o') { //organization tree
        fileName = "OrgFile.tsv";
    }
    else {
        throw std::runtime_error("Incorrect file type chosen");
    }
    ofstream outFile(fileName);
    if (!outFile)
        cout << "File open error!" << endl;

    for (size_t i = 0; i < indexVector.size(); ++i) {
        // TA 
        if (i == indexVector.size() - 1) {
            outFile << indexVector[i];
        } else {
            outFile << indexVector[i] << endl;
        }
    }
    outFile.close();


}
//load trees with persistent data files
void Index::loadFiles(AVLTree<Word> & tree ,string FileName, char type) {
    ifstream textFile(FileName);
    if (textFile.fail()) {
        throw std::runtime_error("Text File Failed!");
    }
    string word;
    string docStr;
    string occurrenceStr;
    int doc;
    int occurrence;
    unordered_map<int, int> map;
    unordered_set<string> seen;

    int count = 0;

    while (textFile.good()) {
        getline(textFile, word, '\t');
        getline(textFile, docStr, '\t');
        getline(textFile, occurrenceStr);
        
        doc = stoi(docStr);
        occurrence = stoi(occurrenceStr);
        map.insert(make_pair(doc, occurrence));
    

        loadPersistentTree(word, doc, type, tree, occurrence);
        map.clear();
    }
    cout << "Done Inserting" << endl;

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
//generate document details
void Index::generateDocs(string filename){
    ofstream outFile(filename);
    if (!outFile)
        cout << "File open error!" << endl;

    int counter = 0;
    for (auto p : documentMap) {
        outFile << p.first << "\t";
        outFile << p.second.getText() << "\t";
        outFile << p.second.getTitle() << "\t";
        outFile << p.second.getPublication() << "\t";
        if (counter == documentMap.size() - 1) {
            outFile << p.second.getDate();
        } else {
            outFile << p.second.getDate()  << endl;
        }
        counter++;
    }
    
}

void Index::loadDocs(string filename){

    ifstream textFile(filename);
    if (textFile.fail()) {
        throw std::runtime_error("Text File Failed!");
    }

    string idStr;
    string title;
    string publication;
    string date;
    string text;

    while (textFile.good()) {
        getline(textFile, idStr, '\t');
        getline(textFile, text, '\t');
        getline(textFile, title, '\t');
        getline(textFile, publication, '\t');
        getline(textFile, date);

        int id = stoi(idStr);
        Document doc(title, publication, date, text);
        documentMap[id] = doc;
    }
}

void Index:: clearAllTrees(){
 words.clear();
 persons.clear();
 orgs.clear();
 documentMap.clear();
}