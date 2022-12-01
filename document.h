#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#include <string>

using namespace std;

class Document {

private: 
    string title_;
    string publication_;
    string datePublished_;

public:
    void setTitle(string);
    string getTitle();

    void setPublication(string);
    string getPublication();

    void setDate(string);
    string setDate();
};

#endif