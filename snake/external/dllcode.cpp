#include "dllexport.h"

LPCTSTR DLL_EXPORT NomeMemoria = { TEXT("Nome Memoria Partilhada") };

LPCTSTR DLL_EXPORT NomeSPodeEscreverMemoria = { TEXT("Semaforo Pode Escrever Memoria") };
LPCTSTR DLL_EXPORT NomeSPodeLerMemoria = { TEXT("Semaforo Pode Ler Memoria") };

LPCTSTR DLL_EXPORT EventoPergunta = { TEXT("EventoPergunta") };
LPCTSTR DLL_EXPORT EventoResposta = { TEXT("EventoResposta") };

LPCTSTR DLL_EXPORT MutexMem = { TEXT("Mutex Mem") };



DLL_EXPORT void gotoxy(int x, int y)
{
	static HANDLE hStdout = NULL;
	COORD coord;
	coord.X = x;
	coord.Y = y;
	if (!hStdout)
		hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hStdout, coord);
}

DLL_EXPORT void clrscr(void)
{
	HANDLE hConsoleOut = NULL;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	CHAR attribute = 0x07;

	COORD c;
	DWORD len, wr;

	if (!hConsoleOut) {
		hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	}

	len = csbiInfo.dwSize.X * csbiInfo.dwSize.Y;
	c.X = c.Y = 0;
	FillConsoleOutputCharacter(hConsoleOut, ' ', len, c, &wr);
	FillConsoleOutputAttribute(hConsoleOut, attribute, len, c, &wr);

	gotoxy(1, 1);
}