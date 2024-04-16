#pragma once

#include <windows.h>
#include <TlHelp32.H>

#define THREAD_WAITING  0
#define THREAD_RUNNING  1
#define THREAD_ERROR 100

typedef struct ThreadList {
    THREADENTRY32* teThreadList;
    DWORD dwSize;
} ThreadList;

ThreadList getThreadsList(DWORD dwPid);

HANDLE getThreadHandle(THREADENTRY32 teThread, DWORD dwAccess);
DWORD  getThreadExitCode(HANDLE hThread);
BYTE   getThreadSimpleState(HANDLE hThread);