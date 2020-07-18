#include <iostream>
#include "TreeCmd.h"

using namespace std;


int main(int argc, char** argv)
{
    if (argc<2) return -1;

    TreeCmd *tree = new TreeCmd(argv[1]);
    tree->execute();
    delete tree;
    return 0;
}
