using namespace std;
#include <iostream>
#include <string>
#include "GUI.h"


void GUI::displaymenu(){ 
    cout<<"===================================================== \n";
    cout<<"                       Shmoogle                       \n";                  
    cout<<"===================================================== \n";
    cout<<" 1.Create an index from a directory\n";
    cout<<" 2.Write the index to persistance\n";
    cout<<" 3.Read the index to persistance\n";
    cout<<" 4.Enter a query\n";
    cout<<" 5.Output Stats \n";
}

void GUI::createIndex()
{
    cout<< "you have selected Create an index from a directory : \n";

    DocumentParser parser(index_);
    parser.StopWords(stopWordsPath_);
    parser.testFileSystem(documentsPath_);
}

void GUI::writePersistance()
{
    cout<< "you have selected Write to persistance \n";
    index_->generateFilesWords();
    index_->generateFilesPersons();
    index_->generateFilesOrgs();
}

void GUI::readPersistance()
{
    cout<< "you have selected Read to persistance \n";
}

void GUI::enterQuery()
{
cout<< "you have selected Enter a query\n";
}

void GUI::OutputStats()
{
cout<< "you have selected View all statistics\n";
}

void GUI::run(){
    string st[20];
    int item = 0;

    int choice;
    string select;
    do { 
        displaymenu();
        cout<<"Enter your choice(1-5):";
        cin>>choice;
        switch (choice) {
            case 1: createIndex(); break;
            case 2: writePersistance();break;
            case 3: readPersistance();break;
            case 4: enterQuery(); break;
            case 5: OutputStats(); break;
            default: cout << "invalid"; break;
        }
        cout << "Press y or Y to continue:";
        cin >> select;
    } while (select == "y" || select == "Y");
}




// User Interface
//  The user interface of the application should provide the following options:



//  allows the user to create an index from a directory with documents.
//  allows the user to write the index to a file (make it persistent) and read an index from a file.
//  allow the user to enter a query (as described above).
//  The results should display the article’s identifying/important information including Article Title,
// publication, and date published. If the result set contains more than 15 results, display the 15
// with the highest relevancy. If less than 15 are returned, display all of them ordered by relevance.
// If you’d like to show more, please paginate.
//  The user should be allowed to choose one of the articles from the result set above and have the
// complete text of the article printed.
//  Output basic statistics of the search engine including:
//  Timing for indexing and for queries (use std::chrono).
//  Total number of individual articles in the current index.
//  The total number of unique words indexed (total nodes in the word AVL Tree)
//  Any other interesting stats that you gather in the course of parsing.