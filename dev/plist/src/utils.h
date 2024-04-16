#pragma once

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void removeExtension(char* str);
BOOL isPID(char* str);
char* formatTime(DWORD timeInMilliseconds);