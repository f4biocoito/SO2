#include "serverheader.h"

int _tmain(int argc, LPTSTR argv[]) {

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	gotoxy(10, 10);
	_tprintf(TEXT("Bemvindo ao servidor"));
	Sleep(2000);
	//clrscr();
	exit(0);
}