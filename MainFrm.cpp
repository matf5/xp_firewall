// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "fire.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_ICON_NOTIFY			WM_APP + 10

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_POPUP_EXIT, OnPopupExit)
	ON_COMMAND(ID_POPUP_MINIMIZE, OnPopupMinimize)
	ON_COMMAND(ID_POPUP_MAXIMIZE, OnPopupMaximize)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
	ID_INDICATOR_ONLINELED,
	ID_INDICATOR_OFFLINELED
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{	
}

CMainFrame::~CMainFrame()
{
}

//主界面启动
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;// fail to create
	}
	//****************************************************************
	//设置防火墙状态图标
	int iTBCtlID;
	iTBCtlID = m_wndToolBar.CommandToIndex(ID_ICON);
	m_wndToolBar.SetButtonStyle(iTBCtlID, TBBS_GROUP);
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetPaneInfo(0, m_wndStatusBar.GetItemID(0), SBPS_STRETCH, NULL );
	SetOnlineLed(FALSE);
	SetOfflineLed(TRUE);
	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(ID_INDICATOR_ONLINELED),ID_INDICATOR_ONLINELED, SBPS_NOBORDERS, 14);
	m_wndStatusBar.SetPaneInfo(m_wndStatusBar.CommandToIndex(ID_INDICATOR_OFFLINELED),ID_INDICATOR_OFFLINELED, SBPS_NOBORDERS, 14);

	//***************************************************************
	//设置右下角图标
	HICON hIcon = ::LoadIcon (AfxGetResourceHandle (),
							MAKEINTRESOURCE(IDI_MAINFRAME)); //Icon to be Used
	if(!m_SysTray.Create(NULL,		 // Let icon deal with its own messages
						WM_ICON_NOTIFY,		// Icon notify message to use
						_T("Firewall Running"),		// tooltip
						hIcon,
						IDR_MENU1,					// ID of tray Menu
						FALSE))
	CSystemTray::MinimiseToTray(this);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_MAXIMIZEBOX;
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//点击关闭程序
void CMainFrame::OnClose() 
{	
	CFrameWnd::OnClose();
}
void CMainFrame::OnExit() 
{
	CFrameWnd::OnClose();
}
//右下角图标关闭程序
void CMainFrame::OnPopupExit() 
{
	CFrameWnd::OnClose();
}
//右下角图标最小化
void CMainFrame::OnPopupMinimize() 
{
	CSystemTray::MinimiseToTray(this);
	m_SysTray.SetMenuDefaultItem (ID_POPUP_MAXIMIZE,FALSE);

}
//右下角图标最大化
void CMainFrame::OnPopupMaximize() 
{
	CSystemTray ::MaximiseFromTray(this);
	m_SysTray.SetMenuDefaultItem (ID_POPUP_MINIMIZE,FALSE);	
}


/********************************************************************/
/*																	*/
/* Function name : SetOnlineLed										*/	
/* Description   : Turn online LED on/off.							*/
/*																	*/
/********************************************************************/
void CMainFrame::SetOnlineLed(BOOL bOnline)
{
	HICON hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(),
				bOnline ? MAKEINTRESOURCE(IDI_LED_GREEN) : MAKEINTRESOURCE(IDI_LED_OFF),
				 IMAGE_ICON, 16, 16, LR_SHARED);
	m_wndStatusBar.GetStatusBarCtrl().SetIcon(m_wndStatusBar.CommandToIndex(ID_INDICATOR_ONLINELED), hIcon);
	m_wndStatusBar.GetStatusBarCtrl().Invalidate();
	m_wndStatusBar.GetStatusBarCtrl().UpdateWindow();
	DestroyIcon(hIcon);
}


/********************************************************************/
/*																	*/
/* Function name : SetOfflineLed									*/	
/* Description   : Turn offline LED on/off.							*/
/*																	*/
/********************************************************************/
void CMainFrame::SetOfflineLed(BOOL bOffline)
{
	HICON hIcon = (HICON)::LoadImage(AfxGetInstanceHandle(),
				bOffline ? MAKEINTRESOURCE(IDI_LED_RED) : MAKEINTRESOURCE(IDI_LED_OFF),
				 IMAGE_ICON, 16, 16, LR_SHARED);
	m_wndStatusBar.GetStatusBarCtrl().SetIcon(m_wndStatusBar.CommandToIndex(ID_INDICATOR_OFFLINELED), hIcon);
	m_wndStatusBar.GetStatusBarCtrl().Invalidate();
	m_wndStatusBar.GetStatusBarCtrl().UpdateWindow();
	DestroyIcon(hIcon);
}


