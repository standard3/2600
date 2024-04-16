#include "argparse.h"

void handlerProcessesList()
{
    ProcessList processList = getProcessesList();
    if (processList.dwSize == 0)
    {
        fprintf(stderr, "Error : todo");
        exit(1);
    }

    printProcesses(processList);
}

void handlerHelp()
{
    puts("Usage: plist.exe [-h|-d] <process>|<pid>\n");
    exit(0);
}

// todo: rethink too much duplicated code

void handlerThreadDetails(char* arg)
{
    DWORD dwPid = 0;

    // check for PID
    if (isPID(arg))
    {
        dwPid = atol(arg);
    }
    // process name
    else
    {
        PROCESSENTRY32 peProcess = getProcessFromName(arg);
        dwPid = peProcess.th32ProcessID;
    }

    ThreadList threadList = getThreadsList(dwPid);

    if (threadList.dwSize == 0)
    {
        fprintf(stderr, "Error : while getting thread details\n");
        exit(1);
    }

    printThreads(threadList);

    free(threadList.teThreadList);

    exit(0);
}

void handlerProcessDetails(char* arg)
{
    PROCESSENTRY32 peProcess;

    // check for PID
    if (isPID(arg))
    {
        peProcess = getProcessFromPID(atol(arg));
    }
    // process name
    else
        peProcess = getProcessFromName(arg);

    if (peProcess.dwSize == 0)
    {
        fprintf(stderr, "Error : while getting process\n");
        exit(1);
    }

    printProcessHeader();
    printProcess(peProcess);
}

int parseArguments(int argc, char** argv)
{
    // todo: make unknown flags return help
    char* arg = argv[1];

    // no arguments, print all processes
    if (argc == 1)
        handlerProcessesList();

    // args > 1, print specified process
    else if (strcmp(arg, "-h") == 0)
        handlerHelp();

    else if (strcmp(arg, "-d") == 0)
        handlerThreadDetails(argv[2]);

    // print process details from name or PID
    else
        handlerProcessDetails(arg);

    return 0;
}