#include <windows.h>//�⺻���� �ڷ� Ÿ��, �Լ� ���� ���� ����, �� �� �ʿ��� ��� ������ ����

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass= L"HelloAPI";

int APIENTRY WinMain(HINSTANCE hInstance,//���α׷��� ��ü �ڵ��̴�.
					 HINSTANCE hPrevInstance,//���� ���α׷��� ��ü �ڵ�, ������� NULL�� �Ǹ� WIN32���� �׻� NULL�̴�. ȣȯ���� ���ؼ��� �����ϴ� �Ű������̴�.
					 LPSTR lpszCmdParam,//��������� �Էµ� ���α׷� �Ű������̴�.
					 int nCmdShow) {//���α׷��� ����� �����̸� �ּ�ȭ, ���� ��� ���� ���޵ȴ�.
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;//������� �������� Ư���� �����ϴ� ����ü
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;//���࿵��
	WndClass.cbWndExtra=0;//���࿵��
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);//�������� ������ ĥ�� �귯�� ����
	WndClass.hCursor=LoadCursor(NULL,IDC_WAIT );// ������ ���콺 Ŀ�� ����
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);// ������ ������ ����
	WndClass.hInstance=hInstance;//���α׷��� ��ü �ڵ�
	WndClass.lpfnWndProc=(WNDPROC)WndProc;//������ �޽��� ó�� �Լ� �̸�
	WndClass.lpszClassName=lpszClass;//������ Ŭ���� �̸�(���ڿ�)
	WndClass.lpszMenuName=NULL;//���α׷��� ����� �޴� ����
	WndClass.style=CS_HREDRAW | CS_VREDRAW;//������ ��Ÿ��
	RegisterClass(&WndClass);//1.���

	hWnd=CreateWindow(lpszClass,			//2.������Ŭ���� �̸�, ����
					L"������ ���α׷���",			    //������Ÿ��Ʋ
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,   //�����콺Ÿ��
					200, 200,							//�����찡 ���϶� X Y��ǥ
					600, 600,							//�������� ���� ����				
					(HWND)NULL,							//�θ������� �ڵ�
					(HMENU)NULL,						//�����찡 ������ �޴��ڵ�
					hInstance,							//�ν��Ͻ��ڵ�
					NULL);								//������ ������

 	   ShowWindow(hWnd,nCmdShow);//3.������
	
	while(GetMessage(&Message,0,0,0)) {/*
	1.�޽��� ť���� �޽����� �о����
	2. ���� �޽����� WM_QUIT�� ��쿡�� FALSE ���� -> �޽��� ���� ����
	*/
		TranslateMessage(&Message);//Ű���� �Է� �޽����� VM_CHAR �޽����� ��ȯ
		DispatchMessage(&Message);//�޽����� OS�� �����Ͽ� OS�� ������ ���ν����� ȣ���ϵ��� ��
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,//�޽����� ���޵� ������ �ڵ�
						 UINT iMessage,//�޽����� ����
						 WPARAM wParam,//�޽����� �ΰ� ����
	                     LPARAM lParam){//�޽����� �ΰ� ����
	LPCTSTR text = L"���������� ����";
	
	switch(iMessage) {
		case WM_PAINT://ȭ���� �ٽ� �׷��� �� �ʿ䰡 ���� �� �߻�
			{
				PAINTSTRUCT ps;//������ Ŭ���̾�Ʈ ������ �����ΰ��� �׸����� �� �� �ʿ��� ������ ��� �ִ� ����ü
				HDC hdc = BeginPaint(hWnd,&ps);//1.�� ����ü������ �ʿ��� ������ ä��� OS�� DC��û ���ϰ����� DC�ڵ��� �����´�.
				TextOut(hdc,100,100,text,lstrlen(text));//2.OS�� ������ DC�� �Ű��������ϴ� API�Լ��� ȣ���Ͽ� ���
				EndPaint(hWnd,&ps);//3.DC ����� �������� OS�� �˸���.
				return 0;
			}
		case WM_DESTROY://�����찡 �޸𸮿��� �ı��� �� �߻��Ѵ�.
			PostQuitMessage(0);//WM_QUIT �޽����� �ý��� ť�� ������ ���ϰ����� False�� �޾ƿ� ����ȴ�.
			return 0;
		}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));//WndProc���� ó������ ���� ������ �޽����� ���� ó����
}
