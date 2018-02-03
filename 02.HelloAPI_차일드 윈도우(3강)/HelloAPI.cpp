#include <windows.h>//전처리문

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";//문자열을 저장하는 String변수, 유니코드 사용시 대문자 L을 앞에 붙여준다.
LPCTSTR ChildClassName  = L"ChildWin";

int APIENTRY WinMain(HINSTANCE hInstance,//애플리케이션의 현재 인스턴스의 핸들
					 HINSTANCE hPrevInstance,//애플리케이션의 이전 인스턴스의 핸들, Win32기반에서는 NULL값
					 LPSTR lpszCmdParam,//커맨드 라인의 인자값을 받는 포인터
					 int nCmdShow)//윈도우가 화면상에 보여질 때 어떤상태로 보여지는지 결정, NULL(default)
{
	HWND hWnd;//윈도우 핸들
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	//윈도우 구성요소의 속성값
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//윈도우 바탕색 지정
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);    
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;//인스턴스 핸들: 운영체제가 주는값이라 값내용은 모름
	WndClass.lpfnWndProc=(WNDPROC)WndProc;//** call back 함수
	WndClass.lpszClassName=lpszClass;//** 클래스 이름
	WndClass.lpszMenuName=NULL;//메뉴
	WndClass.style=CS_HREDRAW | CS_VREDRAW; //클래스의 스타일, 가로, 세로
	RegisterClass(&WndClass);//메인윈도우 클래스 등록

	WndClass.lpfnWndProc =ChildWndProc;      //차일드 윈도우 프로시저
	WndClass.lpszClassName =ChildClassName; //차일드 윈도우 클래스이름, 등록
	RegisterClass(&WndClass);//차일드윈도우 클래스 등록

	hWnd=CreateWindow(lpszClass,			//윈도우클래스 이름, 생성
					L"윈도우 프로그래밍",			    //윈도우타이틀바이름
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //윈도우타이틀바스타일
					200, 200,							//윈도우가 보일때 X Y좌표
					600, 600,							//윈도우의 폭과 높이				
					(HWND)NULL,							//부모윈도우 핸들
					(HMENU)NULL,						//윈도우가 가지는 메뉴핸들
					hInstance,							//인스턴스핸들
					NULL);								//여분의 데이터

 	   ShowWindow(hWnd,nCmdShow);//눈으로 보기위한 함수, 보여줌
	
	while(GetMessage(&Message,0,0,0)) {//메시지큐에서 메시지를 읽어들임,0은 default값, 읽은 메시지가 WM_QUIT인 경우에만 FALSE 리턴, 메시지 루프 종료
		TranslateMessage(&Message);//키보드를 눌렀다 떼었을 때 이를 WM_CHAR메시지로 변환
		DispatchMessage(&Message);//메시지를 운영체제로 전달하여 운영체제가 윈도우 프로시저를 호출하도록 함
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, //윈도우 핸들
						 UINT iMessage,//메시지
						 WPARAM wParam,//메시지 파라미터1
						 LPARAM lParam)//메시지 파라미터2
{
	LPCTSTR text = L"메인윈도우 생성";
	LPCTSTR text2 = L"메인윈도우2 생성";

	switch(iMessage) {//메시지를 읽어온다.
		case WM_PAINT://윈도우의 무언가를 그릴때 사용하는 메시지, 윈도우가 새로만들어지거나 움직일시 스스로 운영체제가 만들어줌
			{
				PAINTSTRUCT ps;//윈도우 클라이언트 영역에 그리는 정보를 갖고 있는 구조체, DC를 구한다.
				HDC hdc = BeginPaint(hWnd, &ps);//출력준비
				TextOut(hdc,100, 100, text, lstrlen(text));//핸들(divice context = dc:윈도우에 무언가를 출력하려면 여기에 입력해서 출력해야한다.출력을 위한 자료구조),윈도우 왼쪽상단 기준 X,Y,메시지를 출력, lstrlen:텍스트의 문자열 길이만큼 
				TextOut(hdc, 200, 200, text2, lstrlen(text2));//핸들(divice context = dc:윈도우에 무언가를 출력하려면 여기에 입력해서 출력해야한다.출력을 위한 자료구조),윈도우 왼쪽상단 기준 X,Y,메시지를 출력, lstrlen:텍스트의 문자열 길이만큼 잡아주는것
				EndPaint(hWnd,&ps);//출력끝
				return 0;
			}
		case WM_CREATE:
		{
			HWND hChildWnd = CreateWindow( 
				ChildClassName,     		// 차일드 윈도우 클래스 이름 
				L"차일드 윈도우",            	// 윈도우 타이틀 
				WS_OVERLAPPEDWINDOW | WS_CHILD,  // 윈도우  스타일 
				150,       		// 윈도우 보일 때 x 좌표 
				150,       		// 윈도우 보일 때 y 좌표 
				260,       		// 윈도우 폭
				200,       		// 윈도우 높이
				hWnd,         		// 부모 윈도우
				(HMENU) 1000,        	// 차일드 윈도우ID 
				g_hInst,           		// 인스턴스 핸들 
				(LPVOID) NULL);      	// 여분의 데이터

			if (!hChildWnd) 	return -1;

			ShowWindow(hChildWnd, SW_SHOW); 
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));//프로그래머는 꼭 필요한 메시지에 대해서만 처리한다. 나머지 기본메시지는 DefWindowProc 함수가 처리함
}
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LPCTSTR text = L"차일드 윈도우생성";
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