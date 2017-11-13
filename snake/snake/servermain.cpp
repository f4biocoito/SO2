#include "serverheader.h"

int _tmain(int argc, LPTSTR argv[]) {
	HANDLE hTcomunica;
	HANDLE hTmemoria;

	map * PtrMemoria; // mudar para game
	snake * PtrSMemoria;

	PodeEscreverMemoria = CreateSemaphore(NULL, MAXJ, MAXJ, NomeSPodeEscreverMemoria);
	PodeLerMemoria = CreateSemaphore(NULL, 0, MAXJ, NomeSPodeLerMemoria);

	EventoP = CreateEvent(NULL, TRUE, FALSE, EventoPergunta);
	EventoR = CreateEvent(NULL, TRUE, FALSE, EventoResposta);

	MutexMemoria = CreateMutex(NULL, FALSE, MutexMem);

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	_tprintf(TEXT("Bemvindo ao servidor"));
	Sleep(2000);
	//clrscr();



	gotoxy(0, 2);

	hTcomunica = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RecebeJogadores, NULL, 0, NULL);

	hMemoria = CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, sizeof(map), NomeMemoria);
	if (hMemoria == NULL) {
		_tprintf(TEXT("[Erro]Criacao de objectos do Windows(%d)\n"), GetLastError());
		return -1;
	}

	PtrMemoria = (map *)MapViewOfFile(hMemoria, FILE_MAP_WRITE, 0, 0, sizeof(map));
	if (PtrMemoria == NULL) {
		_tprintf(TEXT("[Erro]Mapeamento da memoria partilhada(%d)\n"), GetLastError());
		return -1;
	}
	hTmemoria = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AtualizaMemoria, (LPVOID)PtrMemoria, 0, NULL);

	/*
	comandos = apresentacomandos();
	if(comandos == 0)
	_tprintf(TEXT("escolha %d"), comandos);
	else if(comandos == 1)
	_tprintf(TEXT("escolha %d"), comandos);
	*/
	//FIM = TRUE;


	WaitForSingleObject(hTcomunica, INFINITE);
	CloseHandle(hTcomunica);
	WaitForSingleObject(hTmemoria, INFINITE);
	CloseHandle(hTmemoria);

	clrscr();
	gotoxy(0, 1);
	_tprintf(TEXT("O servidor vai fechar"));
	UnmapViewOfFile(PtrMemoria);
	CloseHandle(PodeEscreverMemoria);
	CloseHandle(PodeLerMemoria);
	CloseHandle(hMemoria);
	CloseHandle(EventoR);
	CloseHandle(EventoP);
	CloseHandle(MutexMemoria);
	Sleep(2000);
	exit(0);
}



int apresentacomandos(void) {
	int opcao = -1;
	gotoxy(0, 1);
	_tprintf(TEXT("\n0 - Listar jogadores"));
	_tprintf(TEXT("\n1 - Listar variaveis"));
	_tprintf(TEXT("\n2 - Sair"));
	do {
		fflush(stdin);
		fflush(stdout);
		_tprintf(TEXT("\n > "));
		_tscanf_s(TEXT("%d"), &opcao);
	} while (_istdigit(opcao) || opcao < 0 || opcao > 2);
	return opcao;
}


DWORD WINAPI RecebeJogadores(LPVOID param) {
	HANDLE hPipeCliServ, hPipeServCli;
	for (int i = 0; i < MAXJ; i++)
		hPipes[i] = INVALID_HANDLE_VALUE;
	HANDLE hTT;
	//gotoxy(0, 14);
	while (desliga) {
		if (Jogadoresemjogo < MAXJ) {
			//_tprintf(TEXT("[SERVIDOR] Vou passar a criacao de copias do pipe ... (CreateNamedPipe)\n"));
			hPipeServCli = CreateNamedPipe(PIPE_Serv_Cli, PIPE_ACCESS_OUTBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, MAXJ, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR), 1000, NULL);
			if (hPipeServCli == INVALID_HANDLE_VALUE) {
				_tprintf(TEXT("Erro na ligacao ao cliente!"));
				continue;
			}

			hPipeCliServ = CreateNamedPipe(PIPE_Cli_Serv, PIPE_ACCESS_INBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, MAXJ, TAM * sizeof(TCHAR), TAM * sizeof(TCHAR), 1000, NULL);
			if (hPipeCliServ == INVALID_HANDLE_VALUE) {
				_tprintf(TEXT("Erro na ligacao ao cliente!"));
				continue;
			}

			//_tprintf(TEXT("[SERVIDOR] Esperar ligacao de um clientes... (ConnectNamedPipe)\n"));
			if (!ConnectNamedPipe(hPipeCliServ, NULL)) {
				_tprintf(TEXT("Erro na ligacao ao cliente!"));
				exit(-1);
			}

			hPipes[0] = hPipeServCli;
			Jogadoresemjogo++;

			hTT = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)AtendeJogadores, (LPVOID)hPipeCliServ, 0, NULL);
			WaitForSingleObject(hTT, INFINITE);
			break;

			//if (FIM)
			//break;
			//Ir a procura de uma posicao livre
			//for (int i = 0; i < MAXJ; i++) {
			//if (hPipes[i] == INVALID_HANDLE_VALUE) {
			//hPipes[0] = hPipeServCli;
			//Jogadoresemjogo++;
			//break;
			//}
			//}
		}
		//else {
		//	Sleep(2000);
		//}
	}

	//for (int i = 0; i < MAXJ; i++) {
	DisconnectNamedPipe(hPipes[0]);
	_tprintf(TEXT("\n[SERVIDOR] Vou desligar o pipe... (CloseHandle)\n"));
	CloseHandle(hPipes[0]);
	//}
	return 0;
}


DWORD WINAPI AtendeJogadores(LPVOID param) {
	HANDLE pipe = (HANDLE)param;
	/* ALTEREI A ESTRUTURA
	comandos cm;
	comandos cmresp;

	while (desliga) {
		WaitForSingleObject(EventoP, INFINITE);
		cm = Respostadocliente(pipe);
		gotoxy(0, 12);
		_tprintf(TEXT("mensagem do cliente\n"));
		_tprintf(TEXT("id %d "), cm.id_jog);
		_tprintf(TEXT("tipo %d "), cm.tipo);
		_tprintf(TEXT("mensagem %s "), cm.cmd);

		if (cm.tipo == 1) {
			jogo.jogador[0].id_jog = 1;
			_tcscpy_s(jogo.jogador[0].nome, cm.cmd);
			jogo.jogador[0].pontuacao = 0;
			cmresp.id_jog = jogo.jogador[0].id_jog;
			cmresp.tipo = 0;
			_tcscpy_s(cmresp.cmd, TEXT("OK"));

			jogo.snake->cor = 'R';
			jogo.snake->direcao = 2;
			jogo.snake->id_jog = jogo.jogador[0].id_jog;

			int x = -1;
			int y = -1;
			x = rand() % jogo.mapa.largura;
			y = rand() % jogo.mapa.altura;
			for (int i = 0; i < MinSnake; i++) {
				jogo.snake->pos_snake[0][i] = { x - i };
				jogo.snake->pos_snake[1][i] = { y - i };
			}
			for (int i = 0; i < MaxObjetos; i++) {
				x = rand() % jogo.mapa.largura;
				y = rand() % jogo.mapa.altura;
				jogo.mapa.objetos[0][i] = x;
				jogo.mapa.objetos[1][i] = y;
			}
			ReleaseMutex(MutexMemoria);

		}
		if (cm.tipo == 2) {

			//cmresp.id_jog = jogadores[0].id_jog;
			cmresp.id_jog = jogo.jogador[0].id_jog;
			cmresp.tipo = 0;
			_tcscpy_s(cmresp.cmd, TEXT("OK"));
			jogo.mapa.aguarda = 0; //apresenta snakes

		}
		if (cm.tipo == 9) {

			//cmresp.id_jog = jogadores[0].id_jog;
			cmresp.id_jog = jogo.jogador[0].id_jog;
			cmresp.tipo = 0;
			_tcscpy_s(cmresp.cmd, TEXT("OK"));
			desliga = FALSE;

		}

		Mensagemparacliente(hPipes[0], cmresp);
		//Sleep(2000);
		SetEvent(EventoR);
		ResetEvent(EventoR);
	}
	DisconnectNamedPipe(pipe);
	CloseHandle(pipe);
	*/
	return 0;
}

/*
//
void Mensagemparacliente(HANDLE pipe, comandos cm) {
	DWORD n = 0;
	WriteFile(pipe, &cm.id_jog, sizeof(int), &n, NULL);
	n = 0;
	WriteFile(pipe, &cm.tipo, sizeof(int), &n, NULL);
	n = 0;
	WriteFile(pipe, &cm.cmd, _tcslen(cm.cmd) * sizeof(TCHAR), &n, NULL);
}
*/
/*
//
comandos Respostadocliente(HANDLE pipe) {
	comandos cm;
	DWORD n = 0;
	ReadFile(pipe, &cm.id_jog, sizeof(int), &n, NULL);
	n = 0;
	ReadFile(pipe, &cm.tipo, sizeof(int), &n, NULL);
	n = 0;
	ReadFile(pipe, &cm.cmd, _tcslen(cm.cmd) * sizeof(TCHAR), &n, NULL);
	cm.cmd[n / sizeof(TCHAR)] = '\0';
	return cm;
}
*/

DWORD WINAPI AtualizaMemoria(LPVOID param) {
	map * ptr = (map *)param;
	WaitForSingleObject(MutexMemoria, INFINITE);
	//usar os semaforos
	while (desliga) {
		WaitForSingleObject(PodeEscreverMemoria, INFINITE);
		//memcpy(ptr, &jogo, sizeof(map));
		ReleaseSemaphore(PodeLerMemoria, 1, NULL);
		if (desliga) {
			break;
		}
		//movimento da cobra
	}
	return 0;
}
