#include "print.h"

void printProcessHeader()
{
    printf("%-30s | %-10s | %-10s | %-10s | %-10s | %-20s | %-20s |\n",
    "Name", "PID", "Priority", "Threads", "Priv (Kb)", "User CPU Time", "Kernel CPU Time");
    for (int i = 0; i < 130; i++) printf("=");
    puts("");

}

void printProcesses(ProcessList processList)
{
    printProcessHeader();

    // loop over array
    for (int i = 0; i < processList.dwSize; i++)
        printProcess(processList.peProcessList[i]);

    free(processList.peProcessList);
}

void printProcess(PROCESSENTRY32 peProcess)
{
    // get handle to process
    HANDLE hProcess = getProcessHandle(
        peProcess,
        PROCESS_QUERY_LIMITED_INFORMATION
    );

    // debugging handles
    // printf("HANDLE on %-20s : %p (pid %-5lu) => ERR %lu\n",
        // peProcess.szExeFile,
        // hProcess,
        // peProcess.th32ProcessID,
        // GetLastError()
    // );

    if (hProcess == NULL)
    {
        CloseHandle(hProcess);
        return;
    }

    // get process private memory usage
    PROCESS_MEMORY_COUNTERS_EX pmc = getProcessMemoryUsage(hProcess);

    // get cpu time
    CPUTime cpuTime = getCPUTimes(hProcess);

    char* formatedUserCPUTime   = formatTime(cpuTime.userCPUTime);
    char* formatedKernelCPUTime = formatTime(cpuTime.kernelCPUTime);

    printf("%-30s | %-10lu | %-10lu | %-10lu | %-10llu | %-20s | %-20s |\n",
        peProcess.szExeFile,
        peProcess.th32ProcessID,
        peProcess.pcPriClassBase,
        peProcess.cntThreads,
        pmc.PrivateUsage / 1024, // Kb
        formatedUserCPUTime,
        formatedKernelCPUTime
    );

    CloseHandle(hProcess);
    free(formatedUserCPUTime);
    free(formatedKernelCPUTime);
}

void printThreadHeader()
{
    printf("%-10s | %-8s | %-10s | %-20s | %-20s |\n",
    "TID", "Priority", "Last error", "State", "Entrypoint");
    for (int i = 0; i < 82; i++) printf("=");
    puts("");
}

void printThreads(ThreadList threadList)
{
    printThreadHeader();

    // loop over array
    for (int i = 0; i < threadList.dwSize; i++)
        printThread(threadList.teThreadList[i]);

    free(threadList.teThreadList);
}

void printThread(THREADENTRY32 teThread)
{
    // get handle to thread
    HANDLE hThread = getThreadHandle(
        teThread,
        THREAD_QUERY_INFORMATION
    );

    if (hThread == NULL)
    {
        CloseHandle(hThread);
        return;
    }

    DWORD dwThreadExitCode   = getThreadExitCode(hThread);
    BYTE  bThreadSimpleState = getThreadSimpleState(hThread);

    printf("%-10lu | %-8lu | %-10lu | %-20d | %-20s |\n",
        teThread.th32ThreadID,
        teThread.tpBasePri,
        dwThreadExitCode,
        bThreadSimpleState,
        "." // entrypoint
    );

    CloseHandle(hThread);
}