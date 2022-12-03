#ifndef FINALPROJEXAMPLES_INDEX_H
#define FINALPROJEXAMPLES_INDEX_H

#include <fstream>

#include "Word.h"
#include "AVLTree.h"
#include "document.h"
#include <unordered_set>


class Index {

public:
    Index() = default;
    void insertWord(string w, int d);
    void insertPerson(string w, int d);
    void insertOrgs(string w, int d);
    void loadTree(string w, int d, char t, AVLTree<Word>&);
    void generateFiles(AVLTree<Word> &, char);
    
    void prettyPrintWordTree();
    void prettyPrintPersonTree();
    void prettyPrintOrgsTree();
    
    void generateFilesWords();
    void generateFilesPersons();
    void generateFilesOrgs();

    void loadFilesOrgs();
    void loadFilesWords();
    void loadFilesPersons();


    void loadFiles(AVLTree<Word> &);


    Document getDocument(int);
    void addDocument(int, Document&);
    int numDocuments();

    void generateDocs(string);
    void loadDocs(string);


    AVLTree<Word>& getWords();
    AVLTree<Word>& getPersons();
    AVLTree<Word>& getOrgs();

private:
    AVLTree<Word> words;
    AVLTree<Word> persons;
    AVLTree<Word> orgs;
    unordered_map<int, Document> documentMap;

    // QueryEngine
    // 1. Word class needs to return unordered_map
    // 2. loop through unordered_map and retrive Document obj
    //    from documentMap in the index class


};



#endif //FINALPROJEXAMPLES_INDEX_H
