#include "DocumentParser.h"


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

// Read file with stop words
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

// Read in Json
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


    string title = d["title"].GetString();
    string datePublished = d["published"].GetString();
    string author = d["author"].GetString();
    string text = d["text"].GetString();


    Document doc(title, datePublished, author, text);
    index_->addDocument(docID, doc);

    vector<string> tokens = tokenize(text);
    
    for (auto token : tokens) {
        index_->insertWord(token, docID);
        
    
    }
    auto persons = d["entities"]["persons"].GetArray();
    for (auto &p : persons)
    {
        string name = p["name"].GetString();
        index_->insertPerson(name, docID);
    }

    auto orgs = d["entities"]["organizations"].GetArray();
    for (auto &o : orgs)
    {
        string name = o["name"].GetString();
        index_->insertOrgs(name, docID);
    
    }
   

    input.close();
}

void DocumentParser::testFileSystem(const string &path)
{
    
    
    docID = 0;
    // recursive_director_iterator used to "access" folder at parameter -path-
    // we are using the recursive iterator so it will go into subfolders.
    // see: https://en.cppreference.com/w/cpp/filesystem/recursive_directory_iterator
    auto it = filesystem::recursive_directory_iterator(path);

    // loop over all the entries.
   
    int numFiles = 1;
    for (const auto &entry : it)
    {
      
        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;
        // We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json")
        {
            if (numFiles % 1000 == 0) {
                cout << "Files parsed " << numFiles << endl;
            }
            testReadJsonFile(entry.path().string());
        }
       
    
    }


    
    
    

}
