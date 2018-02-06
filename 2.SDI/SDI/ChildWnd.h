#pragma once


// CChildWnd

class CChildWnd : public CWnd //CWnd로부터 상속되었음을 나타낸다.
{
	DECLARE_DYNAMIC(CChildWnd)

public:
	CChildWnd();//생성자 함수
	virtual ~CChildWnd();//소멸자 함수

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


