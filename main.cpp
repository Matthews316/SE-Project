#include "DocumentParser.h"
#include "AVLTree.h"
#include "GUI.h"


int main(int argc, char *argv[])
{
    GUI interface(argv[1], argv[2], argv[3], argv[4]);
    interface.run();


    // DocumentParser parser;
    // parser.StopWords(argv[1]);
    // parser.testFileSystem(argv[2]);
    

    return 0;
}


