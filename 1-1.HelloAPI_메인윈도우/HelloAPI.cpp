#include <windows.h>//기본적인 자료 타입, 함수 원형 등을 정의, 그 외 필요한 헤더 파일을 포함

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass= L"HelloAPI";

int APIENTRY WinMain(HINSTANCE hInstance,//프로그램의 객체 핸들이다.
					 HINSTANCE hPrevInstance,//현재 프로그램의 객체 핸들, 없을경우 NULL이 되며 WIN32에선 항상 NULL이다. 호환성을 위해서만 존재하는 매개변수이다.
					 LPSTR lpszCmdParam,//명령행으로 입력된 프로그램 매개변수이다.
					 int nCmdShow) {//프로그램이 실행될 형태이며 최소화, 보통 모양 등이 전달된다.
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

LRESULT CALLBACK WndProc(HWND hWnd,//메시지가 전달될 윈도우 핸들
						 UINT iMessage,//메시지의 종류
						 WPARAM wParam,//메시지의 부가 정보
	                     LPARAM lParam){//메시지의 부가 정보
	LPCTSTR text = L"메인윈도우 생성";
	
	switch(iMessage) {
		case WM_PAINT://화면을 다시 그려야 할 필요가 있을 때 발생
			{
				PAINTSTRUCT ps;//윈도우 클라이언트 영역에 무엇인가를 그리려고 할 때 필요한 정보를 담고 있는 구조체
				HDC hdc = BeginPaint(hWnd,&ps);//1.위 구조체생성에 필요한 정보를 채우고 OS에 DC요청 리턴값으로 DC핸들을 가져온다.
				TextOut(hdc,100,100,text,lstrlen(text));//2.OS가 제공한 DC를 매개변수로하는 API함수를 호출하여 출력
				EndPaint(hWnd,&ps);//3.DC 사용이 끝났음을 OS에 알린다.
				return 0;
			}
		case WM_DESTROY://윈도우가 메모리에서 파괴될 때 발생한다.
			PostQuitMessage(0);//WM_QUIT 메시지를 시스템 큐에 보내서 리턴값으로 False로 받아와 종료된다.
			return 0;
		}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));//WndProc에서 처리하지 않은 나머지 메시지에 관해 처리함
}
