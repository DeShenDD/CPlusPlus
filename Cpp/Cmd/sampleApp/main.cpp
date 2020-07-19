#include <iostream>
#include "LsCmd.h"
#include "TreeCmd.h"

using namespace std;


int main(int argc, char** argv)
{
    if (argc<2) return -1;

    TreeCmd *tree = new TreeCmd(argv[1]);
    tree->execute();

    LsCmd *ls = new LsCmd(argv[1]);
    ls->execute();

    delete tree;
    delete ls;
    return 0;
}
