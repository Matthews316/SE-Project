#ifndef DOCUMENTPARSER_H
#define DOCUMENTPARSER_H


#include "document.h"
#include <vector>
#include <sstream>
#include <ctype.h>
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_set>

#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

#include "Index.h"
#include "AVLTree.h"

using namespace std;

class DocumentParser {

public:
    DocumentParser() : index_{nullptr} {}
    DocumentParser(Index*& index) : index_{index} {}

    void StopWords(const string&);
    void testReadJsonFile(const string &);
    void testFileSystem(const string &);

    

    string removeStopWords(string );

    vector<string> tokenize(string str);

private:
    unordered_set<string> stopWords;
    Index* index_;
    int docID;
};
#endif