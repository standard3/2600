#include "thread.h"
#include <stdio.h>

#define MEMORY_CHUNKS 10

ThreadList getThreadsList(DWORD dwPid)
{
    ThreadList result = {
        .teThreadList = NULL,
        .dwSize = 0
    };

    // create our thread list snapshot
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, dwPid);

    if (hSnapshot == INVALID_HANDLE_VALUE)
        return result;

    THREADENTRY32* teThreadList = NULL;

    THREADENTRY32 teThread;
    teThread.dwSize = sizeof(THREADENTRY32);

    DWORD dwSize = 0;
    DWORD dwThreadCount = 0;

    if (!Thread32First(hSnapshot, &teThread))
        return result;

    do
    {
        // parent process is our PID
        if (teThread.th32OwnerProcessID == dwPid)
        {
            // small optimization to reduce number of time we
            // resize the dynamic array
            if (dwThreadCount >= dwSize)
            {
                dwSize += MEMORY_CHUNKS;

                teThreadList = (THREADENTRY32*)realloc(teThreadList, dwSize * sizeof(THREADENTRY32));
                if (teThreadList == NULL)
                {
                    free(teThreadList);
                    return result;
                }
            }
            // add current thread to list
            *(teThreadList + dwThreadCount) = teThread;
            dwThreadCount++;
        }

    } while (Thread32Next(hSnapshot, &teThread));

    CloseHandle(hSnapshot);

    result.teThreadList = teThreadList;
    result.dwSize = dwThreadCount;

    return result;
}

HANDLE getThreadHandle(THREADENTRY32 teThread, DWORD dwAccess)
{
    // can be NULL
    return OpenThread(dwAccess, FALSE, teThread.th32ThreadID);
}

DWORD getThreadExitCode(HANDLE hThread)
{
    DWORD dwExitCode = 0;
    GetExitCodeThread(hThread, &dwExitCode);
    return dwExitCode;
}

BYTE getThreadSimpleState(HANDLE hThread)
{
    DWORD dwExitCode = getThreadExitCode(hThread);

    if (dwExitCode == STILL_ACTIVE)
    {
        // absolutely evil code
        // we should look into _KTHREAD_STATE
        // https://www.vergiliusproject.com/kernels/x64/Windows%2010%20%7C%202016/2110%2021H2%20(November%202021%20Update)/_KTHREAD_STATE
        DWORD dwSuspendCount = SuspendThread(hThread);

        ResumeThread(hThread); // ??

        return dwSuspendCount > 0 ? THREAD_WAITING : THREAD_RUNNING;
    }

    return THREAD_ERROR;
}
