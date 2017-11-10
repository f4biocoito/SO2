#include <windows.h>
#include <tchar.h>
#include "resource.h"

LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);


TCHAR *szProgName = TEXT("Snake");


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;		
	MSG lpMsg;		
	WNDCLASSEX wcApp;
	BOOL ret;

	wcApp.cbSize = sizeof(WNDCLASSEX);	
	wcApp.hInstance = hInst;			
	wcApp.lpszClassName = szProgName;	
	wcApp.lpfnWndProc = TrataEventos;
	wcApp.style = CS_HREDRAW | CS_VREDRAW;
	wcApp.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SNAKE_ICON));
	wcApp.hIconSm = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SNAKE_ICON_Sm));
	wcApp.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(IDC_SNAKE_POINTER));
	wcApp.lpszMenuName = MAKEINTRESOURCE(IDR_SNAKE_MENU);
	wcApp.cbClsExtra = 0;				
	wcApp.cbWndExtra = 0;				
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	
	if (!RegisterClassEx(&wcApp))
		return(0);
	
	hWnd = CreateWindow(
		szProgName,			
		TEXT("Snake game client"),
		WS_OVERLAPPEDWINDOW,	
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		(HWND)HWND_DESKTOP,	
		(HMENU)NULL,			
		(HINSTANCE)hInst,		
		0);				

	ShowWindow(hWnd, nCmdShow);	
	UpdateWindow(hWnd);		

	while ((ret = GetMessage(&lpMsg, NULL, 0, 0)) != 0) {
		if (ret != -1) {
			TranslateMessage(&lpMsg);	
			DispatchMessage(&lpMsg);	
		}
	}
	
	return((int)lpMsg.wParam);	
}


LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {

	switch (messg) {
	case WM_CLOSE:		
		if (MessageBox(hWnd, TEXT("Do you want to leave? "), TEXT("Quit"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			//fechar o jogo
			PostQuitMessage(0);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)){
			case ID_FILE_EXIT:
				if (MessageBox(hWnd, TEXT("Do you want to leave? "), TEXT("Quit"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					//fechar o jogo
					PostQuitMessage(0);
				break;
			case ID_ABOUT:
				MessageBox(hWnd, TEXT("Sistemas Operativos 2 \nFábio Coito \n21240055"), TEXT("About"), MB_ICONINFORMATION);
				break;
		} 
		break;
		

	
	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam));
	}
	return(0);
}
