#pragma once

#include <windows.h>
#include <stdio.h>
#include "process.h"
#include "thread.h"

void printProcessHeader();
void printProcesses(ProcessList peProcessList);
void printProcess(PROCESSENTRY32 peProcess);

void printThreadHeader();
void printThreads(ThreadList threadList);
void printThread(THREADENTRY32 teThread);