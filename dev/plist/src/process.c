#include "process.h"
#include <stdio.h>

#define MEMORY_CHUNKS 10

// todo: reduire le code dupliqué

ProcessList getProcessesList()
{
    ProcessList result = {
        .peProcessList = NULL,
        .dwSize = 0
    };

    // create our process list snapshot
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnapshot == INVALID_HANDLE_VALUE)
        return result;

    PROCESSENTRY32* peProcessList = NULL;

    PROCESSENTRY32 peProcess;
    peProcess.dwSize = sizeof(PROCESSENTRY32);

    DWORD dwSize = 0;
    DWORD dwProcessCount = 0;

    if (!Process32First(hSnapshot, &peProcess))
        return result;

    do
    {
        // small optimization to reduce number of time we
        // resize the dynamic array
        if (dwProcessCount >= dwSize)
        {
            dwSize += MEMORY_CHUNKS;

            peProcessList = (PROCESSENTRY32*)realloc(peProcessList, dwSize * sizeof(PROCESSENTRY32));
            if (peProcessList == NULL)
            {
                free(peProcessList);
                return result;
            }
        }

        if (peProcess.th32ProcessID == 0)
            continue;

        // add current process to list
        *(peProcessList + dwProcessCount) = peProcess;
        dwProcessCount++;

    } while (Process32Next(hSnapshot, &peProcess));

    CloseHandle(hSnapshot);

    result.peProcessList = peProcessList;
    result.dwSize = dwProcessCount;

    return result;
}

PROCESSENTRY32 getProcessFromName(char* sProcessName)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 error = { .dwSize = 0 };

    if (hSnapshot == INVALID_HANDLE_VALUE)
        return error;

    PROCESSENTRY32 peProcess;
    peProcess.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &peProcess))
        return error;

    do
    {
        char sCurrentProcessName[255];

        strcpy(sCurrentProcessName, peProcess.szExeFile);
        removeExtension(sCurrentProcessName);

        if (strcmp(sCurrentProcessName, sProcessName) == 0)
        {
            CloseHandle(hSnapshot);
            return peProcess;
        }

    } while (Process32Next(hSnapshot, &peProcess));

    return error;
}

PROCESSENTRY32 getProcessFromPID(DWORD dwPid)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 error = { .dwSize = 0 };
    if (hSnapshot == INVALID_HANDLE_VALUE)
        return error;

    PROCESSENTRY32 peProcess;
    peProcess.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnapshot, &peProcess))
        return error;

    do
    {
        if (peProcess.th32ProcessID == dwPid)
        {
            CloseHandle(hSnapshot);
            return peProcess;
        }

    } while (Process32Next(hSnapshot, &peProcess));

    return error;
}

HANDLE getProcessHandle(PROCESSENTRY32 peProcess, DWORD dwAccess)
{
    // can be NULL
    return OpenProcess(dwAccess, FALSE, peProcess.th32ProcessID);
}

PROCESS_MEMORY_COUNTERS_EX getProcessMemoryUsage(HANDLE hProcess)
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

    GetProcessMemoryInfo(hProcess, (PROCESS_MEMORY_COUNTERS*)&pmc, pmc.cb);

    return pmc;
}

CPUTime getCPUTimes(HANDLE hProcess)
{
    FILETIME creationTime, exitTime, kernelTime, userTime;
    CPUTime times = { .userCPUTime = 0, .kernelCPUTime = 0 };

    BOOL isSuccess = GetProcessTimes(hProcess, &creationTime, &exitTime, &kernelTime, &userTime);

    if (!isSuccess)
        return times;

    times.userCPUTime = ((ULONGLONG)userTime.dwHighDateTime << 32) + userTime.dwLowDateTime;
    times.kernelCPUTime = ((ULONGLONG)kernelTime.dwHighDateTime << 32) + kernelTime.dwLowDateTime;

    return times;
}