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
    cout<<" 5.Output Statisitcs \n";
    cout<<" 6.Clear Tree \n";
    cout<<" 7.Exit \n";
}


void GUI::createIndex()
{
    cout<< "you have selected Create an index from a directory : \n Please Wait...\n";

    DocumentParser parser(index_);
    parser.StopWords(stopWordsPath_);
    parser.testFileSystem(documentsPath_);
}

void GUI::writePersistence()
{
    cout<< "you have selected Write to persistence \n Please Wait...\n";
    index_->generateFilesWords();
    index_->generateFilesPersons();
    index_->generateFilesOrgs();
    index_->generateDocs("Doc.tsv");
}

void GUI::readPersistence()
{
    cout<< "you have selected Read to persistence \n Please Wait...\n";
    
    index_->loadFilesWords();
    cout << "Done words" << endl;
    index_->loadFilesPersons();
    cout << "Done persons" << endl;
    index_->loadFilesOrgs();
    cout << "Done orgs" << endl;
    index_->loadDocs("Doc.tsv");
     cout << "Done docs" << endl;
}

void GUI::enterQuery()
{
    cout<< "you have selected Enter a query\n";
    Query q(index_);
    cin.ignore();
    q.runQuery(index_);
}

void GUI::OutputStats()
{
    cout<< "you have selected View all statistics\n";
    cout << "Numer of documents " << index_->numDocuments() << endl;
    cout << "Number of words indexed "  << index_->getWords().size() << endl;
    cout << "Number of persons indexed "  << index_->getOrgs().size() << endl;
    cout << "Number of orgs indexed "  << index_->getPersons().size() << endl;
}

void GUI::ClearTree()
{
    index_->clearAllTrees();
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
            case 6: ClearTree(); break;
            case 7: break;
            default: cout << "invalid" << endl; break;
        }
    } while (choice != 7);

    cout << "\nThank you for shmooglin!\n" << endl;
}

