
#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)

#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

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



struct DLL_EXPORT map {
	int sizex = 30;
	int sizey = 30;
	int objects = 4;
	int obstacles = 4;
	int mapobject[MAX_MAP_OBJECTS][2]; // (x,y) coords
	int mapobstacles[MAX_MAP_OBSTACLES][2]; // (x,y) coords
};////

struct DLL_EXPORT snake {
	TCHAR username[MAX_TAM];
	int snakeSize = SNAKE_SIZE;		// snake size
	int coords[MAX_SNAKE_SIZE][2];	// (x,y) coords
	int invertKeys;					// invert input keys
	int oil;						// raise speed
	int glue;						// decrease speed
	int died;						// 1 - died
	int points;						// Current pontuation
	int currentDirection;			// 1-Up 2-Down 3-Right 4-Left
};////

struct DLL_EXPORT game {
	map map;
	snake snake[MAX_SNAKES];
	int numPlayers;
	int numBots;
};////


struct DLL_EXPORT chat {
	HANDLE owner;
	HANDLE players[MAX_SNAKES - 1];
	TCHAR cmd[TAM];
};


struct DLL_EXPORT keys {
	TCHAR username[MAX_TAM];
	TCHAR left;
	TCHAR rigth;
	TCHAR bottom;
	TCHAR top;
};////