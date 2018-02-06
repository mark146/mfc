// SDI.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
#include "stdafx.h"
#include "afxwinappex.h"
#include "SDI.h"
#include "MainFrm.h"
#include "SDIDoc.h"
#include "SDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSDIApp
BEGIN_MESSAGE_MAP(CSDIApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CSDIApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// ǥ�� �μ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSDIApp ����
CSDIApp::CSDIApp()
{
	m_bHiColorIcons = TRUE;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CSDIApp ��ü�Դϴ�.
CSDIApp theApp;



// CSDIApp �ʱ�ȭ
BOOL CSDIApp::InitInstance()
{/* ��: �������α׷����� ����� Ŭ������ ����ϰ� ���� ������ Ŭ������ ��ü�� ������ ���� ���� �����츦 ȭ�鿡 �����ش�. */

	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�. 
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ��� �� �׸��� �����Ͻʽÿ�.

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));//ȣ���ؼ� ���α׷� ������ ������Ʈ���� ������ �� �ֵ��� ������Ʈ�� Ű�� ����
	LoadStdProfileSettings(0);//���� �ֱٿ� ����� ������ ����� �������� ���� INI ������ ����ϱ� ���� ����� ����
	InitContextMenuManager();
	InitShellManager();
	InitKeyboardManager();
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);



	// ���� ���α׷��� ���� ���ø��� ����մϴ�. ���� ���ø��� ����, ������ â �� �� ������ ���� ������ �մϴ�.
	// ��: ��� Ŭ�������� ����� ������ ���⿡�� ����Ѵ�. 
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSDIDoc),//��ť��Ʈ�� CSDIDoc Ŭ����
		RUNTIME_CLASS(CMainFrame),//���� ������� CMainFrame Ŭ����
		RUNTIME_CLASS(CSDIView));//�� ������� CDIView Ŭ����
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	/* ��: ProcessShellCommand() �Լ����� (��)���� ����� ���ø��� �̿��ؼ� CSDIDoc Ŭ������ 
	CMainFrame Ŭ������ ��ü�� ������ ��, CWinApp�� ��� �������� m_pMainWnd�� CMainFrame�� ��ü�� �����Ѵ�. */
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo)) 
		return FALSE;



	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	/* ��: ��) �������� ������ ���� ������ Ŭ������ m_pMainWnd�� �̿��ؼ� ���������������츦 ȭ�鿡 ���δ�.(m_pMainWnd->ShowWindow()) */
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// ���̻簡 ���� ��쿡�� DragAcceptFiles�� ȣ���մϴ�.
	//  SDI ���� ���α׷������� ProcessShellCommand �Ŀ� �̷��� ȣ���� �߻��ؾ� �մϴ�.
	return TRUE;
}



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CSDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSDIApp ����� ���� �ε�/���� �޼���

void CSDIApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CSDIApp::LoadCustomState()
{
}

void CSDIApp::SaveCustomState()
{
}

// CSDIApp �޽��� ó����