
// ZegoExpressQuickStartDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ZegoExpressQuickStart.h"
#include "ZegoExpressQuickStartDlg.h"
#include "ZegoConfigManager.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CZegoExpressQuickStartDlg dialog



CZegoExpressQuickStartDlg::CZegoExpressQuickStartDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ZEGOEXPRESSQUICKSTART_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CZegoExpressQuickStartDlg::~CZegoExpressQuickStartDlg()
{
	if (engine)
	{
		ZegoExpressSDK::destroyEngine(engine);
		engine = nullptr;
	}
}

void CZegoExpressQuickStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG_VIEW, log_list_);
}

BEGIN_MESSAGE_MAP(CZegoExpressQuickStartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE_ENGINE, &CZegoExpressQuickStartDlg::OnBnClickedButtonCreateEngine)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN_ROOM, &CZegoExpressQuickStartDlg::OnBnClickedButtonLoginRoom)
	ON_BN_CLICKED(IDC_BUTTON_PUBLISH_STREAM, &CZegoExpressQuickStartDlg::OnBnClickedButtonPublishStream)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_STREAM, &CZegoExpressQuickStartDlg::OnBnClickedButtonPlayStream)
END_MESSAGE_MAP()


// CZegoExpressQuickStartDlg message handlers

BOOL CZegoExpressQuickStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	CString str;
	str.Format(_T("%u"), ZegoConfigManager::instance()->getAppID());
	((CStatic*)GetDlgItem(IDC_STATIC_APP_ID))->SetWindowText(str);

	str = CString(CStringA(ZegoConfigManager::instance()->getAppSign().c_str()));
	((CStatic*)GetDlgItem(IDC_STATIC_APP_SIGN))->SetWindowText(str);

	((CButton*)GetDlgItem(IDC_RADIO_IS_TEST_ENV))->SetCheck(ZegoConfigManager::instance()->isTestEnviroment());

	str = CString(CStringA(ZegoConfigManager::instance()->getRoomID().c_str()));
	((CStatic*)GetDlgItem(IDC_STATIC_ROOM_ID))->SetWindowText(str);

	str = CString(CStringA(ZegoConfigManager::instance()->getUserID().c_str()));
	((CStatic*)GetDlgItem(IDC_STATIC_USER_ID))->SetWindowText(str);

	str = CString(CStringA(ZegoConfigManager::instance()->getUserID().c_str()));
	((CStatic*)GetDlgItem(IDC_STATIC_USER_NAME))->SetWindowText(str);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CZegoExpressQuickStartDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CZegoExpressQuickStartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CZegoExpressQuickStartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CZegoExpressQuickStartDlg::OnBnClickedButtonCreateEngine()
{
	if (engine == nullptr) {

		PrintLog("Do Step1: Create Engine");

		CString text;
		
		GetDlgItem(IDC_STATIC_APP_ID)->GetWindowTextW(text);
		std::string AppID = CStringA(text.GetBuffer());
		unsigned int appID = atoi(AppID.c_str());

		GetDlgItem(IDC_STATIC_APP_SIGN)->GetWindowTextW(text);
		std::string appSign = CStringA(text.GetBuffer());
	
		bool isTestEnv = ((CButton*)GetDlgItem(IDC_RADIO_IS_TEST_ENV))->GetCheck();

		engine = ZegoExpressSDK::createEngine(appID, appSign, isTestEnv, ZEGO_SCENARIO_GENERAL, nullptr);

 		eventHandler = std::make_shared<MyEventHandler>(this);
  		engine->setEventHandler(eventHandler);
	}
}


void CZegoExpressQuickStartDlg::OnBnClickedButtonLoginRoom()
{
	if (engine != nullptr) {

		PrintLog("Do Step2: Login Room");


		CString text;

		GetDlgItem(IDC_STATIC_ROOM_ID)->GetWindowTextW(text);
		std::string RoomID = CStringA(text.GetBuffer());

		GetDlgItem(IDC_STATIC_USER_ID)->GetWindowTextW(text);
		std::string UserID = CStringA(text.GetBuffer());

		GetDlgItem(IDC_STATIC_USER_NAME)->GetWindowTextW(text);
		std::string UserName = CStringA(text.GetBuffer());
	
		ZegoUser user;
		user.userID = UserID;
		user.userName = UserName;
		engine->loginRoom(RoomID, user);
	}
}

void CZegoExpressQuickStartDlg::OnBnClickedButtonPublishStream()
{
	if (engine != nullptr) {

		PrintLog("Do Step3: Publish Stream");

		CString text;
		GetDlgItem(IDC_EDIT_PUBLISH_STREAM_ID)->GetWindowTextW(text);
		std::string streamID = CStringA(text.GetBuffer());

		engine->startPublishing(streamID);

		ZegoCanvas canvas(GetDlgItem(IDC_STATIC_PREVIEW_VIEW)->GetSafeHwnd());
		engine->startPreview(&canvas);
	}
}


void CZegoExpressQuickStartDlg::OnBnClickedButtonPlayStream()
{
	if (engine != nullptr) {
		PrintLog("Do Step4: Play Stream");

		CString text;
		GetDlgItem(IDC_EDIT_PLAY_STREAM_ID)->GetWindowTextW(text);
		std::string streamID = CStringA(text.GetBuffer());

		ZegoCanvas canvas(GetDlgItem(IDC_STATIC_PLAY_VIEW)->GetSafeHwnd());
		engine->startPlayingStream(streamID, &canvas);
	}
}

static std::wstring utf8ToWstring(const std::string& str)
{
	std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
	return strCnv.from_bytes(str);
}
void CZegoExpressQuickStartDlg::PrintLog(std::string log)
{
	std::wstring wlog = utf8ToWstring(log);
	log_list_.AddString(wlog.c_str());
	SetHScroll();

}

void CZegoExpressQuickStartDlg::SetHScroll()
{
	CDC* dc = GetDC();
	SIZE s;
	int index;
	CString str;
	long temp;
	for (index = 0; index < log_list_.GetCount(); index++)
	{
		log_list_.GetText(index, str);
		s = dc->GetTextExtent(str, str.GetLength() + 1);
		temp = (long)SendDlgItemMessage(IDC_LIST_LOG_VIEW, LB_GETHORIZONTALEXTENT, 0, 0);
		if (s.cx > temp)
		{
			SendDlgItemMessage(IDC_LIST_LOG_VIEW, LB_SETHORIZONTALEXTENT, (WPARAM)s.cx + 1000, 0);
		}
	}
	ReleaseDC(dc);
}


MyEventHandler::MyEventHandler(CZegoExpressQuickStartDlg* dlg)
	: dlg(dlg)
{

}

MyEventHandler::~MyEventHandler()
{

}

void MyEventHandler::PrintLog(const char * format, ...)
{
	if (dlg) {

		char log_buf[1024] = { 0 };
		va_list la;
		va_start(la, format);
		vsprintf_s(log_buf, format, la);
		va_end(la);
	
		dlg->PrintLog(log_buf);
	}
}

void MyEventHandler::onDebugError(int errorCode, const std::string& funcName, const std::string& info)
{
	PrintLog("onDebugError: errorCode=%d, funcName=%s, info=%s", errorCode, funcName.c_str(), info.c_str());
}

void MyEventHandler::onRoomStateUpdate(const std::string& roomID, ZegoRoomState state, int errorCode, const std::string& extendData)
{
	PrintLog("onRoomStateUpdate: roomId=%s, state=%d, errorCode=%d, extendData=%s", roomID.c_str(), state, errorCode, extendData.c_str());
}

void MyEventHandler::onPublisherStateUpdate(const std::string& streamID, ZegoPublisherState state, int errorCode, const std::string& extendData)
{
	PrintLog("onPublisherStateUpdate: streamID=%s, state=%d, errorCode=%d, extendData=%s", streamID.c_str(), state, errorCode, extendData.c_str());
}

void MyEventHandler::onPlayerStateUpdate(const std::string& streamID, ZegoPlayerState state, int errorCode, const std::string& extendData)
{
	PrintLog("onPlayerStateUpdate: streamID=%s, state=%d, errorCode=%d, extendData=%s", streamID.c_str(), state, errorCode, extendData.c_str());
}


