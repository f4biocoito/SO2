#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include "..\external\dllimport.h"

HANDLE hMemoryCli;
LPCTSTR pBufMapCli, pBufGameCli, pBufKeysCli;

HANDLE hWriteMemoryCli;
HANDLE hReadMemoryCli;