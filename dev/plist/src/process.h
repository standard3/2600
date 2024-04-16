#pragma once

#include <windows.h>
#include <TlHelp32.h>
#include <psapi.h>
#include <string.h>
#include "utils.h"

typedef struct ProcessList {
    PROCESSENTRY32* peProcessList;
    DWORD dwSize;
} ProcessList;

typedef struct CPUTime {
    ULONGLONG userCPUTime;
    ULONGLONG kernelCPUTime;
} CPUTime;

ProcessList    getProcessesList();
PROCESSENTRY32 getProcessFromName(char* sProcessName);
PROCESSENTRY32 getProcessFromPID(DWORD dwPid);

HANDLE getProcessHandle(PROCESSENTRY32 peProcess, DWORD dwAccess);
PROCESS_MEMORY_COUNTERS_EX getProcessMemoryUsage(HANDLE hProcess);
CPUTime getCPUTimes(HANDLE hProcess);