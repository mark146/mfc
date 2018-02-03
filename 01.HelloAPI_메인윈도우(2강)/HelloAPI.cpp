#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass= L"HelloAPI";

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszCmdParam,
					 int nCmdShow) {//윈도우 구조체
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;//만들어질 윈도우의 특성을 정의하는 구조체
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;//예약영역
	WndClass.cbWndExtra=0;//예약영역
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//윈도우의 배경색을 칠한 브러시 지정
	WndClass.hCursor=LoadCursor(NULL,IDC_WAIT );// 윈도우 마우스 커서 지정
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);// 윈도우 아이콘 지정
	WndClass.hInstance=hInstance;//프로그램의 객체 핸들
	WndClass.lpfnWndProc=(WNDPROC)WndProc;//윈도우 메시지 처리 함수 이름
	WndClass.lpszClassName=lpszClass;//윈도우 클래스 이름(문자열)
	WndClass.lpszMenuName=NULL;//프로그램이 사용할 메뉴 지정
	WndClass.style=CS_HREDRAW | CS_VREDRAW;//윈도우 스타일
	RegisterClass(&WndClass);//1.등록

	hWnd=CreateWindow(lpszClass,			//2.윈도우클래스 이름, 생성
					L"윈도우 프로그래밍",			    //윈도우타이틀
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우스타일
					200, 200,							//윈도우가 보일때 X Y좌표
					600, 600,							//윈도우의 폭과 높이				
					(HWND)NULL,							//부모윈도우 핸들
					(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
					hInstance,							//인스턴스핸들
					NULL);								//여분의 데이터

 	   ShowWindow(hWnd,nCmdShow);//3.보여줌
	
	while(GetMessage(&Message,0,0,0)) {/*
	1.메시지 큐에서 메시지를 읽어들임
	2. 읽은 메시지가 WM_QUIT인 경우에만 FALSE 리턴 -> 메시지 루프 종료
	*/
		TranslateMessage(&Message);//키보드 입력 메시지를 VM_CHAR 메시지로 변환
		DispatchMessage(&Message);//메시지를 OS로 전달하여 OS가 윈도우 프로시저를 호출하도록 함
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,WPARAM wParam, LPARAM lParam){//윈도우 프로시저
	LPCTSTR text = L"메인윈도우 생성";
	
	switch(iMessage) {
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd,&ps);
				TextOut(hdc,100,100,text,lstrlen(text));
				EndPaint(hWnd,&ps);
				return 0;
			}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
