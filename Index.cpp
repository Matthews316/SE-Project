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
        // Need to make space to include other features
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
        fileName = "WordFile.tsv";
    }
    else if (t == 'p') {
        fileName = "PeopleFile.tsv";
    }
    else if (t == 'o') {
        fileName = "OrgFile.tsv";
    }
    else {
        throw std::runtime_error("Incorrect file type chosen");
    }
    ofstream outFile(fileName);
    if (!outFile)
        cout << "File open error!" << endl;

    for (size_t i = 0; i < indexVector.size(); ++i) {
    }
    outFile.close();


}

void Index::loadFiles(AVLTree<Word> & tree) {
    ifstream textFile("WordFile.txt");
    if (textFile.fail()) {
        throw std::runtime_error("Text File Failed!");
    }
    string word;
    //string docStr;
    //string occurrenceStr;
    int doc;
    int occurrence;
    unordered_map<int, int> map;
    unordered_set<string> seen;


    while (textFile.good()) {
        getline(textFile, word, '\t');
        getline(textFile, docStr, '\t');
        getline(textFile, occurrenceStr);
        }

        doc = stoi(docStr);
        occurrence = stoi(occurrenceStr);
        map.insert(make_pair(doc, occurrence));
    }

    Word wObject(word, map);
    tree.insert(wObject);
    map.clear();

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

void Index::generateDocs(string filename){
    ofstream outFile(filename);
    if (!outFile)
        cout << "File open error!" << endl;

    for (auto p : documentMap) {
        cout << p.first << "\t";
        cout << p.second.getTitle() << "\t";
        cout << p.second.getPublication() << "\t";
        //cout << p.second.getDate() << "\t";
        cout << p.second.getText() << endl;
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
        getline(textFile, title, '\t');
        getline(textFile, publication, '\t');
        getline(textFile, date, '\t');
        getline(textFile, text);

        int id = stoi(idStr);
        Document doc(title, publication, date, text);
        documentMap[id] = doc;
    }
    
}
