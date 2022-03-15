#include "SharedBufferConsumer.hxx"

#include <strings.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// FunctionDeclarations
void PrintUsage();

int main(int argc, char* argv[])
{
    cout << "----------------------------------------------" << endl;
    cout << "Shared Buffer Consumer 1.0 (Ubuntu OS release)" << endl;
    cout << "----------------------------------------------" << endl << endl;

    if( argc < 2 )
    {
        PrintUsage();
        exit(1);
    }

    size_t uNumberOfBuffer = 0;
    string sStringToSearch;

    vector<char*> argvWrapper(argv, argv+argc);

    // strip off the command name
    argvWrapper.erase(argvWrapper.begin());

    while ( !argvWrapper.empty() )
    {
        const auto arg = argvWrapper.front();

        if (strcasecmp(arg, "-n") == 0)
        {
            argvWrapper.erase(argvWrapper.begin());
            if (argvWrapper.empty())
            {
                PrintUsage();
                exit(-1);
            }

            uNumberOfBuffer = atoi(argvWrapper.front());
        }
        else if (strcasecmp(arg, "-s") == 0)
        {
            argvWrapper.erase(argvWrapper.begin());
            if (argvWrapper.empty())
            {
                PrintUsage();
                exit(-1);
            }

            sStringToSearch = argvWrapper.front();
        }

        argvWrapper.erase(argvWrapper.begin());
    }

    if (uNumberOfBuffer <= 0 || uNumberOfBuffer > 65535 || sStringToSearch.empty())
    {
        PrintUsage();
        exit(-1);
    }
    SharedBufferConsumer sbc(uNumberOfBuffer, sStringToSearch);
    sbc.Start();
}


void PrintUsage()
{
    cout << "usage: sbconsumer -n number_of_shared_buffer -s string_to_search" << endl;
    cout << "number_of_shared_buffer: range 1..65525" << endl;
    cout << "string_to_search: a non-empty ASCII substring to search in a sentence.  enclosed with double quotes" << endl;
    cout << "                  if there is any space in the substring, e.g., \"there is\"" << endl;
}
