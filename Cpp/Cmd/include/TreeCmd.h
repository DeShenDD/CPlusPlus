#ifndef __TREE_CMD_
#define __TREE_CMD_
#include <iostream>
#include "CmdFactory.h"

class TreeCmd : public CmdFactory{

public:
    TreeCmd(char* path);
    ~TreeCmd();
    int execute();
private:
    char mPath[1024];
    char mChildPath[1024];
    int ListDir(char* str);
    int deep;

struct TreeList {
    char* name;
    TreeList *next;
};

};

#endif
