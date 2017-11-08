#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);


TCHAR *szProgName = TEXT("cliente");


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
	wcApp.hIcon = LoadIcon(NULL, IDI_ICON1);
												  
												  
	wcApp.hIconSm = LoadIcon(NULL, IDI_INFORMATION);
													
													
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);	
													
													
	wcApp.lpszMenuName = NULL;			
										
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
	TCHAR str[100]; int x, y; HDC device; static int xi = 0, yi = 0;
	static BOOL comecou = FALSE;
	TCHAR letra = 'a';
	PAINTSTRUCT pt;

	switch (messg) {
	case WM_CLOSE:		
		if (MessageBox(hWnd, TEXT("Quer sair? "), TEXT("Fim da Aplicacao"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			PostQuitMessage(0);
		break;

	
	default:
		return(DefWindowProc(hWnd, messg, wParam, lParam));
	}
	return(0);
}
