// SDIView.cpp : CSDIView Ŭ������ ����
#include "stdafx.h"
#include "SDI.h"
#include "SDIDoc.h"
#include "SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_DECREASE_BUTTON	3000//id ��ȣ
#define ID_INCREASE_BUTTON	3100
#define ID_LISTBOX	        3200
#define ID_PROGBAR          3300

// CSDIView
IMPLEMENT_DYNCREATE(CSDIView, CView)

BEGIN_MESSAGE_MAP(CSDIView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSDIView::OnFilePrintPreview)
	ON_WM_CREATE()
	 ON_COMMAND(ID_DECREASE_BUTTON, OnDecreaseButton)
	 ON_COMMAND(ID_INCREASE_BUTTON, OnIncreaseButton)
END_MESSAGE_MAP()

// CSDIView ����/�Ҹ�
CSDIView::CSDIView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
}

CSDIView::~CSDIView(){}

BOOL CSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡�� Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	return CView::PreCreateWindow(cs);
}

// CSDIView �׸���
void CSDIView::OnDraw(CDC* /*pDC*/)
{
	CSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CSDIView �μ�
void CSDIView::OnFilePrintPreview()
{
	AFXPrintPreview(this);
}

BOOL CSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void CSDIView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CSDIView ����
#ifdef _DEBUG
void CSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIDoc* CSDIView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIDoc)));
	return (CSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSDIView �޽��� ó����
int CSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	m_Wnd01.Create(AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW), 
 		 			_T("ù��° ���ϵ�������"),
 					WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CHILD,
 					CRect(40,40,250,200),
 					this,
 					1010);
	ASSERT(m_Wnd01.m_hWnd != NULL);


	m_Wnd02.Create(AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW),
				_T("�ι�° ���ϵ�������"),
				WS_OVERLAPPEDWINDOW|WS_VISIBLE|WS_CHILD,
				CRect(350,50,540,250),
				this,
				1020);


	m_ProgressBar.Create(WS_DLGFRAME|WS_VISIBLE, CRect(50,230,290,270),this, ID_PROGBAR);
	m_ProgressBar.SetRange(0,10);//��������
    m_ProgressBar.SetPos(2);//������ġ ����

	m_Increase_Btn.Create(_T("����"),WS_VISIBLE,CRect(400,300,550,330),//��ư
 	                      this,ID_INCREASE_BUTTON);
 	m_Decrease_Btn.Create(_T("����"),WS_VISIBLE,CRect(400,350,550,380),
	                      this,ID_DECREASE_BUTTON);


	m_ListBox.Create(WS_DLGFRAME|WS_VISIBLE, CRect(50,300,300,500),//����Ʈ�ڽ�
                          this, ID_LISTBOX);
	m_ListBox.AddString(_T("������ �׽�Ʈ !"));
	return 0;
}

void CSDIView::OnDecreaseButton()
{
	int count = m_ListBox.GetCount();

	if(count > 0)
	{
		m_ListBox.DeleteString(count-1);
		m_ProgressBar.SetPos(count-1);
	}
	else
	{
		AfxMessageBox(_T("���� �������� �����ϴ�"));
	}
}

void CSDIView::OnIncreaseButton()
{
	int count = m_ListBox.GetCount();

	if(count < 10)
	{
		m_ListBox.AddString(_T("������ �׽�Ʈ !"));
		m_ProgressBar.SetPos(count+1);
	}
	else
	{
		AfxMessageBox(_T("���̻� �߰��� �� �����ϴ�"));
	}
}