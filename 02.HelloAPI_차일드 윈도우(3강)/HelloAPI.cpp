#include <windows.h>//��ó����

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"HelloAPI";//���ڿ��� �����ϴ� String����, �����ڵ� ���� �빮�� L�� �տ� �ٿ��ش�.
LPCTSTR ChildClassName  = L"ChildWin";

int APIENTRY WinMain(HINSTANCE hInstance,//���ø����̼��� ���� �ν��Ͻ��� �ڵ�
					 HINSTANCE hPrevInstance,//���ø����̼��� ���� �ν��Ͻ��� �ڵ�, Win32��ݿ����� NULL��
					 LPSTR lpszCmdParam,//Ŀ�ǵ� ������ ���ڰ��� �޴� ������
					 int nCmdShow)//�����찡 ȭ��� ������ �� ����·� ���������� ����, NULL(default)
{
	HWND hWnd;//������ �ڵ�
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	//������ ��������� �Ӽ���
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//������ ������ ����
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);    
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;//�ν��Ͻ� �ڵ�: �ü���� �ִ°��̶� �������� ��
	WndClass.lpfnWndProc=(WNDPROC)WndProc;//** call back �Լ�
	WndClass.lpszClassName=lpszClass;//** Ŭ���� �̸�
	WndClass.lpszMenuName=NULL;//�޴�
	WndClass.style=CS_HREDRAW | CS_VREDRAW; //Ŭ������ ��Ÿ��, ����, ����
	RegisterClass(&WndClass);//���������� Ŭ���� ���

	WndClass.lpfnWndProc =ChildWndProc;      //���ϵ� ������ ���ν���
	WndClass.lpszClassName =ChildClassName; //���ϵ� ������ Ŭ�����̸�, ���
	RegisterClass(&WndClass);//���ϵ������� Ŭ���� ���

	hWnd=CreateWindow(lpszClass,			//������Ŭ���� �̸�, ����
					L"������ ���α׷���",			    //������Ÿ��Ʋ���̸�
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //������Ÿ��Ʋ�ٽ�Ÿ��
					200, 200,							//�����찡 ���϶� X Y��ǥ
					600, 600,							//�������� ���� ����				
					(HWND)NULL,							//�θ������� �ڵ�
					(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
					hInstance,							//�ν��Ͻ��ڵ�
					NULL);								//������ ������

 	   ShowWindow(hWnd,nCmdShow);//������ �������� �Լ�, ������
	
	while(GetMessage(&Message,0,0,0)) {//�޽���ť���� �޽����� �о����,0�� default��, ���� �޽����� WM_QUIT�� ��쿡�� FALSE ����, �޽��� ���� ����
		TranslateMessage(&Message);//Ű���带 ������ ������ �� �̸� WM_CHAR�޽����� ��ȯ
		DispatchMessage(&Message);//�޽����� �ü���� �����Ͽ� �ü���� ������ ���ν����� ȣ���ϵ��� ��
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, //������ �ڵ�
						 UINT iMessage,//�޽���
						 WPARAM wParam,//�޽��� �Ķ����1
						 LPARAM lParam)//�޽��� �Ķ����2
{
	LPCTSTR text = L"���������� ����";
	LPCTSTR text2 = L"����������2 ����";

	switch(iMessage) {//�޽����� �о�´�.
		case WM_PAINT://�������� ���𰡸� �׸��� ����ϴ� �޽���, �����찡 ���θ�������ų� �����Ͻ� ������ �ü���� �������
			{
				PAINTSTRUCT ps;//������ Ŭ���̾�Ʈ ������ �׸��� ������ ���� �ִ� ����ü, DC�� ���Ѵ�.
				HDC hdc = BeginPaint(hWnd, &ps);//����غ�
				TextOut(hdc,100, 100, text, lstrlen(text));//�ڵ�(divice context = dc:�����쿡 ���𰡸� ����Ϸ��� ���⿡ �Է��ؼ� ����ؾ��Ѵ�.����� ���� �ڷᱸ��),������ ���ʻ�� ���� X,Y,�޽����� ���, lstrlen:�ؽ�Ʈ�� ���ڿ� ���̸�ŭ 
				TextOut(hdc, 200, 200, text2, lstrlen(text2));//�ڵ�(divice context = dc:�����쿡 ���𰡸� ����Ϸ��� ���⿡ �Է��ؼ� ����ؾ��Ѵ�.����� ���� �ڷᱸ��),������ ���ʻ�� ���� X,Y,�޽����� ���, lstrlen:�ؽ�Ʈ�� ���ڿ� ���̸�ŭ ����ִ°�
				EndPaint(hWnd,&ps);//��³�
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

			if (!hChildWnd) 	return -1;

			ShowWindow(hChildWnd, SW_SHOW); 
			return 0;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));//���α׷��Ӵ� �� �ʿ��� �޽����� ���ؼ��� ó���Ѵ�. ������ �⺻�޽����� DefWindowProc �Լ��� ó����
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