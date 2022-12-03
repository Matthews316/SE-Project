#ifndef _DOCUMENT_H
#define _DOCUMENT_H

#include <string>

using namespace std;

class Document {

private: 
    string title_;
    string publication_;
    string datePublished_;
    string text_;

public:
    Document() = default;
    Document(string, string, string, string);
    
    void setTitle(string);
    string getTitle();

    void setPublication(string);
    string getPublication();

    void setDate(string);
    string getDate();

    void setText(string);
    string getText();
};

#endif