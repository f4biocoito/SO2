#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <time.h>

#include "..\external\dllimport.h"

#define PIPE_Cli_Serv TEXT("\\\\.\\pipe\\cliserv")
#define PIPE_Serv_Cli TEXT("\\\\.\\pipe\\servcli")


#define MAXJ 1 //maximo de jogadores
#define MaxObjetos 2 //objetos no mapa
#define MinSnake 3 //tamanho inicial da cobra
#define MaxSnake 6 //tamanho maximo da cobra
#define TAM 128


int Jogadoresemjogo = 0;

HANDLE hPipes[MAXJ];
BOOL FIM = FALSE;
TCHAR buf[TAM]; //read pipe mensagem do cliente

BOOL desliga = TRUE;


HANDLE PodeEscreverMemoria;
HANDLE PodeLerMemoria;

HANDLE EventoP;
HANDLE EventoR;

HANDLE MutexMemoria;

HANDLE hMemoria;

int apresentacomandos(void);

DWORD WINAPI RecebeJogadores(LPVOID param);

DWORD WINAPI AtendeJogadores(LPVOID param);

//void Mensagemparacliente(HANDLE pipe, comandos cm);

//comandos Respostadocliente(HANDLE pipe);

DWORD WINAPI AtualizaMemoria(LPVOID param);