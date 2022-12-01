#include "DocumentParser.h"
#include "AVLTree.h"
#include "GUI.h"


int main(int argc, char *argv[])
{
    GUI interface(argv[1], argv[2], argv[3], argv[4]);
    interface.run();
    

    return 0;
}


