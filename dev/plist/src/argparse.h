#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "process.h"
#include "print.h"

void handlerProcessesList();
void handlerHelp();
void handlerThreadDetails(char* arg);
void handlerProcessDetails(char* arg);
int  parseArguments(int argc, char** argv);
