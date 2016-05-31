// fireView.h : interface of the CFireView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREVIEW_H__BFC04DAD_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
#define AFX_FIREVIEW_H__BFC04DAD_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Addruledlg.h"
#include "tdriver.h"
#include "MainFrm.h"

class CFireView : public CFormView
{
protected: // create from serialization only
	CFireView();
	
	DECLARE_DYNCREATE(CFireView)


public:
	enum { IDD = IDD_FIRE_FORM };
	CListCtrl	m_cResult;
	CButton	m_cvrules;
	CButton	m_cping;
	CButton	m_cblockall;
	CButton	m_cstart;
// Attributes
public:
	//**********************************************************

	HANDLE		hFile;						// handle to the rule file
	TDriver		m_filterDriver;
	TDriver		m_ipFltDrv;
	CAddRuleDlg m_Addrule;					//加入规则
	BOOL		ImplementRule(void);		// to implement predefined rules

protected:
	BOOL		start;
	BOOL		block;
	BOOL		allow;
	BOOL		ping;
	CMainFrame* m_parent;
	HICON m_hIcon;
	void ParseToIp(CString str);
	int		_rows;					// keep the track of the no of rows in the grid

	//************************************************
	//list Control
	//Shows the headers of member variable m_cResult (See below)
	void ShowHeaders(void);
	//Adds some new headers to m_cResult.
	void AddHeader(LPTSTR hdr);
	//Adds a new item to m_cResult
	AddItem(int nItem,int nSubItem,LPCTSTR strItem,int nImageIndex = -1);
	//Adds a new column to m_cResult
	AddColumn(LPCTSTR strItem, int nItem, int nSubItem = -1, int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM, int nFmt = LVCFMT_LEFT);
	//titles of columns of m_cResult
	CStringList* m_pColumns;
public:

	public:
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
		virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);// DDX/DDV support
		virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CFireView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//*************************************************************
	COLORREF m_clrBk,
			 m_clrText;
		
///////////////////////////////////////////

///////////////////////////////////////////

// Generated message map functions
protected:
	//{{AFX_MSG(CFireView)
	afx_msg void OnAddrule();
	afx_msg void OnStart();
	afx_msg void OnBlockping();
	afx_msg void OnBlockall();
	afx_msg void OnAllowall();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnViewrules();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnUpdateStart(CCmdUI* pCmdUI);
	afx_msg void OnStop();
	afx_msg void OnUpdateStop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAllowall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBlockall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBlockping(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
		CBrush* m_pBrush;
};

#ifndef _DEBUG  // debug version in fireView.cpp
inline CFireDoc* CFireView::GetDocument()
   { return (CFireDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIREVIEW_H__BFC04DAD_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
