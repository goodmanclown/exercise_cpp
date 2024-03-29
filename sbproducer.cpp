#include "SharedBufferProducer.hxx"

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
    cout << "Shared Buffer Producer 1.0 (Ubuntu OS release)" << endl;
    cout << "----------------------------------------------" << endl << endl;

    if( argc < 2 )
    {
        PrintUsage();
        exit(1);
    }

    size_t uNumberOfBuffer = 0;
    string sFilePathName;

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
        else if (strcasecmp(arg, "-f") == 0)
        {
            argvWrapper.erase(argvWrapper.begin());
            if (argvWrapper.empty())
            {
                PrintUsage();
                exit(-1);
            }

            sFilePathName = argvWrapper.front();
        }

        argvWrapper.erase(argvWrapper.begin());
    }

    if (uNumberOfBuffer <= 0 || uNumberOfBuffer > 65535 || sFilePathName.empty())
    {
        PrintUsage();
        exit(-1);
    }
    SharedBufferProducer sbp(uNumberOfBuffer, sFilePathName);
    sbp.Start();
}


void PrintUsage()
{
    cout << "usage: sbproducer -n number_of_shared_buffer -f file_path_name" << endl;
    cout << "number_of_shared_buffer: range 1..65535" << endl;
    cout << "file_path_name: a valid path and name to input file" << endl;
}
