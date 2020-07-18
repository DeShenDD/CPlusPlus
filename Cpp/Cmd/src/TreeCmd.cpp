#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>   
#include <fcntl.h> 
#include <dirent.h>
#include <errno.h>
#include "TreeCmd.h"

using namespace std;

#define PRETREE "|___"

TreeCmd::TreeCmd(char* str):deep(0)
{
    if (!str) cout<<"null path"<<endl;
    else
    {
        int length = strlen(str);
        if (length>0 && length<1024)
            strncpy(mPath, str, length);
    }
}

TreeCmd::~TreeCmd()
{
    memset(mPath, 0, sizeof(mPath));
}

int TreeCmd::ListDir(char* str)
{
    if (!str) return -1;
    DIR* dir;
    struct dirent *ptr;
    if((dir=opendir(str))==NULL) {
        cout<<"couldn't open path: "<<mPath
              <<"error code: "<< strerror(errno)<<endl;
        return -1;
    }

    int curDeep = deep;
    char temp[1024];
    while((ptr=readdir(dir))!=NULL)
    {
        if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, "..")) continue;
        if(ptr->d_type==DT_DIR)
        {
            for(int i=0;i<curDeep;i++)
            {
                cout<<"   ";
            }
            BlueBegin<<PRETREE<<ptr->d_name<<endl;
            deep++;
            sprintf(temp, "%s/%s", str, ptr->d_name);
            ResetColor;
            ListDir(temp);
        } else 
        {
            
            for(int i=0;i<curDeep;i++)
            {
                cout<<"   ";
            }

            sprintf(temp, "%s/%s", str, ptr->d_name);
            if (!access(temp,X_OK)) {
                GreenBegin<<PRETREE<<ptr->d_name<<endl;
                ResetColor;
            } else {
                cout<<PRETREE<<ptr->d_name<<endl;
            }
            
        }
    }
    return 0;
}

int TreeCmd::execute()
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

    while((ptr=readdir(dir))!=NULL)
    {
        deep = 0;
        if(!strcmp(ptr->d_name, ".") || !strcmp(ptr->d_name, "..")) continue;

        if(ptr->d_type==DT_DIR)
        {
            BlueBegin<<"|"<<"___"<<ptr->d_name<<endl;
            ResetColor;
            deep++;
            sprintf(mChildPath, "%s/%s", mPath, ptr->d_name);
            ListDir(mChildPath);
        } else 
        {
            if (!access(ptr->d_name,X_OK)) {
                GreenBegin<<PRETREE<<ptr->d_name<<endl;
                ResetColor;
            } else {
                cout<<PRETREE<<ptr->d_name<<endl;
            }
        }
    }
    return 0;
}
