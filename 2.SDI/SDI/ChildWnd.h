#pragma once


// CChildWnd

class CChildWnd : public CWnd //CWnd�κ��� ��ӵǾ����� ��Ÿ����.
{
	DECLARE_DYNAMIC(CChildWnd)

public:
	CChildWnd();//������ �Լ�
	virtual ~CChildWnd();//�Ҹ��� �Լ�

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


