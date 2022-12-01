#ifndef GUI_H
#define GUI_H

#include <iostream>
#include<string>

#include "DocumentParser.h"
#include "Index.h"

class GUI {

private:
    std::string stopWordsPath_;
    std::string documentsPath_;
    std::string makePersistencePath_;
    std::string readPersistencePath_;
    Index* index_;

public:
    GUI() {
        index_ = new Index();
    }
    ~GUI() {
        delete index_;
    }
    
    GUI(std::string stopWordsPath, std::string documentsPath, 
        std::string makePersistencePath, std::string readPersistencePath)
            : stopWordsPath_{stopWordsPath}, documentsPath_{documentsPath},
              makePersistencePath_{makePersistencePath}, readPersistencePath_{readPersistencePath} {
        index_ = new Index();
    }

    void displaymenu();
    void createIndex();
    void writePersistance();
    void readPersistance();
    void enterQuery();
    void OutputStats();
    void run();
};

#endif