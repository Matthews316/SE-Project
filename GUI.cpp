using namespace std;
#include <iostream>
#include <string>
#include "GUI.h"
#include "Query.h"


void GUI::displaymenu(){ 
    cout<<"===================================================== \n";
    cout<<"                       Shmoogle                       \n";                  
    cout<<"===================================================== \n";
    cout<<" 1.Create an index from a directory\n";
    cout<<" 2.Write the index to persistence\n";
    cout<<" 3.Read the index to persistence\n";
    cout<<" 4.Enter a query\n";
    cout<<" 5.Output Stats \n";
    cout<<" 6.Exit \n";
}


void GUI::createIndex()
{
    cout<< "you have selected Create an index from a directory : \n";

    DocumentParser parser(index_);
    parser.StopWords(stopWordsPath_);
    parser.testFileSystem(documentsPath_);
}

void GUI::writePersistence()
{
    cout<< "you have selected Write to persistence \n";
    index_->generateFilesWords();
    index_->generateFilesPersons();
    index_->generateFilesOrgs();
    index_->generateDocs("Doc.tsv");
}

void GUI::readPersistence()
{
    cout<< "you have selected Read to persistence \n";
    index_->loadFilesWords();
    index_->loadFilesPersons();
    index_->loadFilesOrgs();
    index_->loadDocs("Docs.tsv");
}

void GUI::enterQuery()
{
cout<< "you have selected Enter a query\n";
Query q;
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
        cout<<"Enter your choice(1-6):";
        cin>>choice;
        switch (choice) {
            case 1: createIndex(); break;
            case 2: writePersistence();break;
            case 3: readPersistence();break;
            case 4: enterQuery(); break;
            case 5: OutputStats(); break;
            case 6: break;
            default: cout << "invalid" << endl; break;
        }
        cout << "Press y or Y to continue. Press n or N to exit:";
        cin >> select;
    } while (select == "y" || select == "Y");

    cout << "\nThank you for shmooglin!\n" << endl;
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