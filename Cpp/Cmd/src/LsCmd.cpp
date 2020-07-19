#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <dirent.h>
#include <errno.h>
#include "LsCmd.h"

using namespace std;


LsCmd::LsCmd(char* str)
{
    if (!str) cout<<"null path"<<endl;
    else
    {
        int length = strlen(str);
        if (length>0 && length<1024)
            strncpy(mPath, str, length);
    }
}

LsCmd::~LsCmd()
{
    memset(mPath, 0, sizeof(mPath));
}

void LsCmd::FileUser(int mode, char* p)
{
    char user[3];
    if (S_IRUSR & mode)
    {
        user[0] = 'r';
    } else
    {
        user[0] = '-';
    }

    if (S_IWUSR & mode)
    {
        user[1] = 'w';
    } else
    {
        user[1] = '-';
    }

    if (S_IXUSR & mode)
    {
        user[2] = 'x';
    } else
    {
        user[2] = '-';
    }

    strncpy(p, user, 3);
}

void LsCmd::FileGroup(int mode, char *p)
{
    char user[3];
    if (S_IRGRP & mode)
    {
        user[0] = 'r';
    } else
    {
        user[0] = '-';
    }

    if (S_IWGRP & mode)
    {
        user[1] = 'w';
    } else
    {
        user[1] = '-';
    }

    if (S_IXGRP & mode)
    {
        user[2] = 'x';
    } else
    {
        user[2] = '-';
    }

    strncpy(p, user, 3);
}

void LsCmd::FileOthers(int mode, char* p)
{
    char user[3];
    if (S_IROTH  & mode)
    {
        user[0] = 'r';
    } else
    {
        user[0] = '-';
    }

    if (S_IWOTH  & mode)
    {
        user[1] = 'w';
    } else
    {
        user[1] = '-';
    }

    if (S_IXOTH  & mode)
    {
        user[2] = 'x';
    } else
    {
        user[2] = '-';
    }

    strncpy(p, user, 3);
}

char LsCmd::FileType(int mode)
{
    char type;
    if(S_ISDIR(mode))
    {
        type = 'd';
    } else if (S_ISCHR(mode))
    {
        type = 'c';
    } else if (S_ISREG(mode))
    {
        type = '-';
    } else if (S_ISBLK(mode))
    {
        type = 'b';
    } else if (S_ISFIFO(mode))
    {
        type = 'f';
    } else if (S_ISLNK(mode))
    {
        type = 'l';
    } else if (S_ISSOCK(mode))
    {
        type = 's';
    }

    return type;
}

int LsCmd::execute()
{
    DIR* dir;
    struct dirent *ptr;
    dir=opendir(mPath);
    if(dir==NULL) {
        cout<<"couldn't open path: "<<mPath
              <<"error code: "<< strerror(errno)<<endl;
        return -1;
    }

    cout<<mPath<<endl;
    struct stat st;
    char info[11];

    while((ptr=readdir(dir))!=NULL)
    {
        if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, "..")) continue;

        sprintf(mChildPath, "%s/%s", mPath, ptr->d_name);
        stat(mChildPath, &st);

        memset(info, 0, sizeof(info));
        info[0] = FileType(st.st_mode);
        FileUser(st.st_mode, &info[1]);
        FileGroup(st.st_mode, &info[4]);
        FileOthers(st.st_mode, &info[7]);
        cout<<info<<"  "<<ptr->d_name<<endl;
    }
    return 0;
}
