#include "dllexport.h"

LPCTSTR DLL_IMPORT NomeMemoria;

LPCTSTR DLL_IMPORT NomeSPodeEscreverMemoria;
LPCTSTR DLL_IMPORT NomeSPodeLerMemoria;

LPCTSTR DLL_IMPORT EventoPergunta;
LPCTSTR DLL_IMPORT EventoResposta;

LPCTSTR DLL_IMPORT MutexMem;

struct DLL_IMPORT game;

struct DLL_IMPORT map;

struct DLL_IMPORT snake;

struct DLL_IMPORT chat;

struct DLL_IMPORT keys;


DLL_IMPORT void gotoxy(int x, int y);

DLL_IMPORT void clrscr(void);