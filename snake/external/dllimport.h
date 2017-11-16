#include "dllexport.h"

#define MIN_FIELD_X 20
#define MAX_FIELD_X 80
#define	MIN_FIELD_Y 20
#define MAX_FIELD_Y 50

#define MIN_TAM 3  //tamanho minimo do nome
#define MAX_TAM 20  //tamanho maximo do nome
#define SNAKE_SIZE 3 //tamanho inicial da cobra
#define MIN_SNAKE_SIZE 3 //tamanho inicial da cobra
#define MAX_SNAKE_SIZE 10 //tamanho maximo da cobra
#define MAX_SNAKES 4
#define TAM 128

#define MAX_MAP_OBSTACLES 6
#define MAX_MAP_OBJECTS 6

#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_RIGHT 3
#define KEY_LEFT 4

#define PIPE_Cli_Serv TEXT("\\\\.\\pipe\\cliserv")
#define PIPE_Serv_Cli TEXT("\\\\.\\pipe\\servcli")

LPCTSTR DLL_IMPORT nMemory;

LPCTSTR DLL_IMPORT nWriteMemory;
LPCTSTR DLL_IMPORT nReadMemory;

//LPCTSTR DLL_IMPORT EventoPergunta;
//LPCTSTR DLL_IMPORT EventoResposta;

//LPCTSTR DLL_IMPORT MutexMem;

struct DLL_IMPORT game;

struct DLL_IMPORT map;

struct DLL_IMPORT snake;

struct DLL_IMPORT chat;

struct DLL_IMPORT keys;


DLL_IMPORT void gotoxy(int x, int y);

DLL_IMPORT void clrscr(void);