// SDIDoc.cpp : CSDIDoc Ŭ������ ����
//

#include "stdafx.h"
#include "SDI.h"
#include "SDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSDIDoc
IMPLEMENT_DYNCREATE(CSDIDoc, CDocument)
BEGIN_MESSAGE_MAP(CSDIDoc, CDocument)
END_MESSAGE_MAP()


// CSDIDoc ����/�Ҹ�
CSDIDoc::CSDIDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.
}

CSDIDoc::~CSDIDoc() {}

BOOL CSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.
	return TRUE;
}


// CSDIDoc serialization
void CSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}


// CSDIDoc ����
#ifdef _DEBUG
void CSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSDIDoc ���