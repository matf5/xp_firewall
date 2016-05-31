// MainFrm.h : interface of the CMainFrame class
//

#if !defined(AFX_MAINFRM_H__BFC04DA9_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
#define AFX_MAINFRM_H__BFC04DA9_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif
#include "SystemTray.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	CSystemTray m_SysTray;
	void SetOnlineLed(BOOL bOnline);
	void SetOfflineLed(BOOL bOffline);

// Operations
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	BOOL m_bInitialized;
	HICON m_hIcon;
//****************************************************

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnPopupExit();
	afx_msg void OnPopupMinimize();
	afx_msg void OnPopupMaximize();
	afx_msg void OnExit();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	DECLARE_MESSAGE_MAP()
};


#endif // !defined(AFX_MAINFRM_H__BFC04DA9_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
