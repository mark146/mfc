#include <windows.h>

#define ID_OK_BTN	2000

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";
LPCTSTR ChildClassName  = L"ChildWin";


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR lpszCmdParam,
					 int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); 
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);    
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=(WNDPROC)WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);     //���������� Ŭ���� ���

	WndClass.lpfnWndProc =ChildWndProc;      //���ϵ� ������ ���ν���
	WndClass.lpszClassName =ChildClassName; //���ϵ� ������ Ŭ�����̸�
	RegisterClass(&WndClass); 

	hWnd=CreateWindow(lpszClass,			//������Ŭ���� �̸�
					L"������ ���α׷���",			    //������Ÿ��Ʋ
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //�����콺Ÿ��
					200, 200,							//�����찡 ���϶� X Y��ǥ
					600, 600,							//�������� ���� ����				
					(HWND)NULL,							//�θ������� �ڵ�
					(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
					hInstance,							//�ν��Ͻ��ڵ�
					NULL);								//������ ������

 	   ShowWindow(hWnd,nCmdShow);
	
	while(GetMessage(&Message,0,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
						 WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���������� ����";
	switch(iMessage) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				TextOut(hdc,100, 100, text, lstrlen(text));
				EndPaint(hWnd,&ps);
				return 0;
			}
		case WM_CREATE:
		{
			HWND hChildWnd = CreateWindow( 
							ChildClassName,     		// ���ϵ� ������ Ŭ���� �̸� 
							L"���ϵ� ������",            	// ������ Ÿ��Ʋ 
							WS_OVERLAPPEDWINDOW | WS_CHILD,  // ������  ��Ÿ�� 
							150,       		// ������ ���� �� x ��ǥ 
							150,       		// ������ ���� �� y ��ǥ 
							260,       		// ������ ��
							200,       		// ������ ����
							hWnd,         		// �θ� ������
							(HMENU) 1000,        	// ���ϵ� ������ID 
							g_hInst,           		// �ν��Ͻ� �ڵ� 
							(LPVOID) NULL);      	// ������ ������			

			ShowWindow(hChildWnd, SW_SHOW); 

			hChildWnd = CreateWindow(
							L"button",        		// ������� �ϴ� �������� Ŭ����
							L"�׽�Ʈ",			// ������ Ÿ��Ʋ, ��Ʈ�ѿ� ���� ĸ���� ��ġ�� �޶�����.
							WS_CHILD|WS_VISIBLE, 	// ������ ��Ÿ�� �Ӽ���,WS_VISIBLE�� �־�� ShowWindow �Լ��� ȣ����ص� ��Ʈ���� ȭ�鿡 �����
							20, 400,      		// ������ ���� �� x,y ��ǥ 
							100, 30,      		// ������ ��, ����
							hWnd,         		// �θ� �����츦 �����ϸ�, �ݵ�� �θ� �����찡 �־�� �Ѵ�.
							(HMENU) ID_OK_BTN,   	// ��Ʈ�� ID, ���ϵ� ��Ʈ���� ��� �޴��� �������ʴ´�.
							g_hInst,           		// �ν��Ͻ� �ڵ� 
							(LPVOID) NULL);      	// ������ ������

			if (!hChildWnd) 	return -1;
			return 0;
		}
		case WM_COMMAND:
		{
			if(LOWORD(wParam) == ID_OK_BTN)
			{
				MessageBox(hWnd,L"[�׽�Ʈ] ��ư�� Ŭ���Ǿ���",L"�׽�Ʈ",MB_OK);
			}

			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"���ϵ� ���������";
	switch(message)
	{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd,&ps);
			TextOut(hdc,10, 10, text, lstrlen(text));
			EndPaint(hWnd,&ps);
			return 0;
		}

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}