#include "utils.h"

void removeExtension(char* str)
{
    char* lastDot = strrchr(str, '.');

    if (lastDot != NULL)
        *lastDot = '\0';
}

BOOL isPID(char* str)
{
    for (int i = 0; i < strlen(str); i++)
        if (!isdigit(str[i]))
            return FALSE;

    return TRUE;
}

char* formatTime(DWORD timeInMilliseconds)
{
    DWORD seconds = timeInMilliseconds / 1000;
    DWORD minutes = seconds / 60;
    DWORD hours   = minutes / 60;

    seconds %= 60;
    minutes %= 60;

    char* formattedTime = (char*)malloc(25 * sizeof(char));
    sprintf(formattedTime, "%03lu:%lu:%lu.%lu", hours, minutes, seconds, timeInMilliseconds % 1000);

    return formattedTime;
}