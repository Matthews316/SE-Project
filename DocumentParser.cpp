#include "DocumentParser.h"

// TODO: add stemming (Porter library)
// 

vector<string> DocumentParser::tokenize(string str)
{
    string line = str;
    vector <string> tokens;
    stringstream wordStream(line);
    string partWord;
    while(getline(wordStream, partWord, ' ')) {
        string newString = "";
        for (int i = 0; i < partWord.size(); ++i) {
            if (isalpha(partWord[i])) {
                newString += tolower(partWord[i]);
            }
        }
        if (stopWords.find(newString) == stopWords.end()) {
            tokens.push_back(newString);
        }
    }
     
    return tokens;
}

void DocumentParser::StopWords(const string& testRight){   
    ifstream stopInfile(testRight);

    if (!stopInfile.is_open()) { 
        cout << "Error" << endl;
        return;
    }

    string word;

    while (!stopInfile.eof()) {   
        getline(stopInfile, word);
        string newWord;
        for (auto c : word) {
            if (isalpha(c)) {
                newWord += c;
            }
        }
        stopWords.insert(newWord);
    }

    stopInfile.close();

}

/**
 * example code that reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void DocumentParser::testReadJsonFile(const string &fileName)
{
    docID++;
    // open an ifstream on the file of interest and check that it could be opened.
    ifstream input(fileName);
    if (!input.is_open())
    {
        cerr << "cannot open file: " << fileName << endl;
        return;
    }
        
    
    // Create a RapidJSON IStreamWrapper using the file input stream above.
    rapidjson::IStreamWrapper isw(input);

    // Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    rapidjson::Document d;
    d.ParseStream(isw);


    auto text = d["text"].GetString();
    vector<string> tokens = tokenize(text);

    for (auto token : tokens) {
        // TODO: insert token into words AVLTree
        index_->insertWord(token, docID);
    }

    auto persons = d["entities"]["persons"].GetArray();
    for (auto &p : persons)
    {
        string name = p["name"].GetString();
        // TODO: add to persons AVLTree
        index_->insertPerson(name, docID);
    }

    auto orgs = d["entities"]["organizations"].GetArray();
    for (auto &o : orgs)
    {
        string name = o["name"].GetString();
        // TODO: add to orgs AVLTree
        index_->insertOrgs(name, docID);
    
    }
    // index_->prettyPrintWordTree();

    input.close();
}

/**
 * example code for how to traverse the filesystem using std::filesystem
 * which is new for C++17.
 *
 * @param path an absolute or relative path to a folder containing files
 * you want to parse.
 */
void DocumentParser::testFileSystem(const string &path)
{
    docID = 0;
    // recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(path);

    // loop over all the entries.
    for (const auto &entry : it)
    {

        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            testReadJsonFile(entry.path().string());
        }
    }

    // IndexHandler Handler_;
    // Query Processor(IndexHandler* handler){
    // Handler_ = &handler;
    // }
}
