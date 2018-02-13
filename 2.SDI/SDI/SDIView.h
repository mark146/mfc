// SDIView.h : CSDIView 클래스의 인터페이스
//


#pragma once


#include "ChildWnd.h"
class CSDIView : public CView
{
protected: // serialization에서만 만들어집니다.
	CSDIView();
	DECLARE_DYNCREATE(CSDIView)

// 특성입니다.
public:
	CSDIDoc* GetDocument() const;

// 작업입니다.
public:
	CChildWnd	m_Wnd01;
	CChildWnd	m_Wnd02; 

	CButton		m_Decrease_Btn;//버튼 감소
    CButton		m_Increase_Btn;//버튼 증가

  	CListBox    m_ListBox;

	CProgressCtrl m_ProgressBar;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // SDIView.cpp의 디버그 버전
inline CSDIDoc* CSDIView::GetDocument() const
   { return reinterpret_cast<CSDIDoc*>(m_pDocument); }
#endif

