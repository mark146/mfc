// ChildWnd.cpp : ���� �����Դϴ�.
#include "stdafx.h"
#include "SDI.h"
#include "ChildWnd.h"


// CChildWnd
IMPLEMENT_DYNAMIC(CChildWnd, CWnd)

CChildWnd::CChildWnd()
{
}

CChildWnd::~CChildWnd()
{
}


BEGIN_MESSAGE_MAP(CChildWnd, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CChildWnd �޽��� ó�����Դϴ�.
void CChildWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	// �׸��� �޽����� ���ؼ��� CWnd::OnPaint()��(��) ȣ������ ���ʽÿ�.
	dc.TextOut(20,20, _T(" ���ϵ� ������ �Դϴ�"));
}