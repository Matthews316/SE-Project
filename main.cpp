#include <iostream>
#include "AVLTree.h"
#include "Word.h"
#include "Index.h"

using namespace std;

int main() {

//    vector<Word> wVec;

//    AVLTree<int> tree;
//
//    tree.insert(6);
//    tree.insert(2);
//    tree.insert(7);
//    tree.insert(4);
//    tree.insert(3);
//    tree.insert(8);
//    tree.insert(10);
//    tree.insert(12);
//
//    tree.storeTree(wVec);
//
//    for(size_t i = 0; i < wVec.size(); ++i) {
//        cout << wVec[i] << endl;
//    }


    AVLTree<Word> wTree;
    Index index;


 index.loadTree("happy", 1, 'w', wTree);
 index.loadTree("happy", 1, 'w', wTree);
 index.loadTree("dragon", 1, 'w', wTree);
 index.loadTree("dragon", 2, 'w', wTree);
 index.loadTree("dragon", 2, 'w', wTree);
 index.loadTree("dragon", 3, 'w', wTree);


 index.generateFiles(wTree, 'w');
 wTree.clear();
    wTree.printTreeSort();

    ifstream textFile("WordFile.txt");
    if (textFile.fail()) {
        throw std::runtime_error("Text File Failed!");
    }
    string word;
    int doc;
    int occurrence;
    unordered_map<int, int> map;

    while (true) {
        textFile >> word;
        if (word == "EndofFile")
            break;
        while (true) {
            textFile >> doc;
            if (doc == -1) {
                break;
            }
            textFile >> occurrence;
            map.insert(make_pair(doc, occurrence));
        }
        Word wObject(word, map);
        wTree.insert(wObject);
        map.clear();
    }

    textFile.close();

    wTree.printTreeSort();



    return 0;

}
