#include <windows.h>
#include "argparse.h"

#pragma comment(lib, "user32.lib")

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev,
    PSTR lpCmdLine, int nCmdShow)
{
    int argc = 0;
    LPWSTR argv = CommandLineToArgvW(GetCommandLine(), &argc);

    int rc = main(argc, argv);

    LocalFree(argv);

    return rc;
}

int main(int argc, char** argv)
{
    int rc = parseArguments(argc, argv);

    return rc;
}