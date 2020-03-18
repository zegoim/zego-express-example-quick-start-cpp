
// ZegoExpressQuickStartDlg.h : header file
//

#pragma once

#include "ZegoExpressSDK.h"
using namespace ZEGO::EXPRESS;

class CZegoExpressQuickStartDlg;
class MyEventHandler : public IZegoEventHandler {
public:
	MyEventHandler(CZegoExpressQuickStartDlg* dlg);
	~MyEventHandler();

	void onDebugError(int errorCode, const std::string& funcName, const std::string& info) override;
	void onRoomStateUpdate(const std::string& roomID, ZegoRoomState state, int errorCode, const std::string& extendData) override;
	void onPublisherStateUpdate(const std::string& streamID, ZegoPublisherState state, int errorCode, const std::string& extendData) override;
	void onPlayerStateUpdate(const std::string& streamID, ZegoPlayerState state, int errorCode, const std::string& extendData) override;

private:
	void PrintLog(const char * format, ...);
	CZegoExpressQuickStartDlg* dlg = nullptr;
};

// CZegoExpressQuickStartDlg dialog
class CZegoExpressQuickStartDlg : public CDialogEx
{
// Construction
public:
	CZegoExpressQuickStartDlg(CWnd* pParent = NULL);	// standard constructor
	~CZegoExpressQuickStartDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ZEGOEXPRESSQUICKSTART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCreateEngine();
	afx_msg void OnBnClickedButtonLoginRoom();
	afx_msg void OnBnClickedButtonPublishStream();
	afx_msg void OnBnClickedButtonPlayStream();
	void PrintLog(std::string log);

	void SetHScroll();
private:
	std::shared_ptr<IZegoEventHandler> eventHandler = nullptr;
	ZEGO::EXPRESS::IZegoExpressEngine *engine = nullptr;
	CListBox log_list_;

};
