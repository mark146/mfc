// SDIView.h : CSDIView Ŭ������ �������̽�
//


#pragma once


#include "ChildWnd.h"
class CSDIView : public CView
{
protected: // serialization������ ��������ϴ�.
	CSDIView();
	DECLARE_DYNCREATE(CSDIView)

// Ư���Դϴ�.
public:
	CSDIDoc* GetDocument() const;

// �۾��Դϴ�.
public:
	CChildWnd	m_Wnd01;
	CChildWnd	m_Wnd02; 

	CButton		m_Decrease_Btn;//��ư ����
    CButton		m_Increase_Btn;//��ư ����

  	CListBox    m_ListBox;

	CProgressCtrl m_ProgressBar;

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDecreaseButton();
	afx_msg void OnIncreaseButton();
};

#ifndef _DEBUG  // SDIView.cpp�� ����� ����
inline CSDIDoc* CSDIView::GetDocument() const
   { return reinterpret_cast<CSDIDoc*>(m_pDocument); }
#endif

