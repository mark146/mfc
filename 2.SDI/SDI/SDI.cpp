// SDI.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 표준 인쇄 설정 명령입니다.
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CSDIApp 생성
CSDIApp::CSDIApp()
{
	m_bHiColorIcons = TRUE;
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CSDIApp 개체입니다.
CSDIApp theApp;



// CSDIApp 초기화
BOOL CSDIApp::InitInstance()
{/* 가: 응용프로그램에서 사용할 클래스를 등록하고 메인 윈도우 클래스의 객체를 생성한 다음 메인 윈도우를 화면에 보여준다. */

	// 응용 프로그램 매니페스트가 ComCtl32.dll 버전 6 이상을 사용하여 비주얼 스타일을
	// 사용하도록 지정하는 경우, Windows XP 상에서 반드시 InitCommonControlsEx()가 필요합니다. 
	// InitCommonControlsEx()를 사용하지 않으면 창을 만들 수 없습니다.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 응용 프로그램에서 사용할 모든 공용 컨트롤 클래스를 포함하도록 이 항목을 설정하십시오.

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// OLE 라이브러리를 초기화합니다.
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));//호출해서 프로그램 정보를 레지스트리에 저장할 수 있도록 레지스트리 키를 설정
	LoadStdProfileSettings(0);//가장 최근에 사용한 파일의 목록을 가져오기 위해 INI 파일을 사용하기 위한 기능을 제공
	InitContextMenuManager();
	InitShellManager();
	InitKeyboardManager();
	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);



	// 응용 프로그램의 문서 템플릿을 등록합니다. 문서 템플릿은 문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	// 나: 어떠한 클래스들을 사용할 것인지 여기에서 등록한다. 
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CSDIDoc),//도큐먼트는 CSDIDoc 클래스
		RUNTIME_CLASS(CMainFrame),//메인 윈도우는 CMainFrame 클래스
		RUNTIME_CLASS(CSDIView));//뷰 윈도우는 CDIView 클래스
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	/* 다: ProcessShellCommand() 함수에는 (가)에서 등록한 템플릿을 이용해서 CSDIDoc 클래스와 
	CMainFrame 클래스의 객체를 생성한 후, CWinApp의 멤버 데이터인 m_pMainWnd에 CMainFrame의 객체를 대입한다. */
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
	if (!ProcessShellCommand(cmdInfo)) 
		return FALSE;



	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	/* 라: 다) 과정으로 생성된 메인 윈도우 클래스인 m_pMainWnd를 이용해서 메인프레임윈도우를 화면에 보인다.(m_pMainWnd->ShowWindow()) */
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 접미사가 있을 경우에만 DragAcceptFiles를 호출합니다.
	//  SDI 응용 프로그램에서는 ProcessShellCommand 후에 이러한 호출이 발생해야 합니다.
	return TRUE;
}



// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CSDIApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CSDIApp 사용자 지정 로드/저장 메서드

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

// CSDIApp 메시지 처리기