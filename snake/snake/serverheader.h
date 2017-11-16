#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

#include "..\external\dllimport.h"



//int Jogadoresemjogo = 0;

//HANDLE hPipes[MAX_SNAKES];
//BOOL FIM = FALSE;
//TCHAR buf[TAM]; //read pipe mensagem do cliente

//BOOL desliga = TRUE;


HANDLE hMemory;
LPCTSTR pBufMap, pBufGame, pBufKeys;

HANDLE hWriteMemory;
HANDLE hReadMemory;

//HANDLE EventoP;
//HANDLE EventoR;

//HANDLE MutexMemoria;



int apresentacomandos(void);

DWORD WINAPI RecebeJogadores(LPVOID param);

DWORD WINAPI AtendeJogadores(LPVOID param);

//void Mensagemparacliente(HANDLE pipe, comandos cm);

//comandos Respostadocliente(HANDLE pipe);

DWORD WINAPI AtualizaMemoria(LPVOID param);