// ChildWnd.cpp : 구현 파일입니다.
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



// CChildWnd 메시지 처리기입니다.
void CChildWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CWnd::OnPaint()을(를) 호출하지 마십시오.
	dc.TextOut(20,20, _T(" 차일드 윈도우 입니다"));
}