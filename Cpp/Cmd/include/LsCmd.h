#ifndef __LS_CMD_
#define __LS_CMD_
#include <iostream>
#include <map>
#include "CmdFactory.h"

class LsCmd : public CmdFactory{

public:
    LsCmd(char* path);
    ~LsCmd();
    int execute();
private:
    char mPath[1024];
    char mChildPath[1024];
    void FileUser(int mode, char *p);
    void FileGroup(int mode, char *p);
    void FileOthers(int mode, char *p);
    char FileType(int mode);
    std::map<std::string, std::string> data;

};

#endif
