#ifndef _CMD_FACTORY_
#define _CMD_FACTORY_
#include <iostream>


#define GreenBegin  std::cout<<"\033[32m"
#define GreenEnd    "\033[42m"<<endl
#define BlueBegin  std::cout<<"\033[34m"
#define BlueEnd    "\033[44m"<<endl;
#define RedBegin  std::cout<<"\033[34m"
#define RedEnd    "\033[41m"<<endl
#define ResetColor  std::cout<<"\033[0m";


class CmdFactory{
public:
    CmdFactory(){}

    virtual ~CmdFactory(){}

};


#endif
