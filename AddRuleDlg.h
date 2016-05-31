#if !defined(AFX_ADDRULEDLG_H__BFC04DB5_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
#define AFX_ADDRULEDLG_H__BFC04DB5_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddRuleDlg.h : header file
//
//*********************************************************************
#include "DrvFltIp.h"
#include "TDriver.h"

/////////////////////////////////////////////////////////////////////////////
// CAddRuleDlg dialog

class CAddRuleDlg : public CDialog
{
private:
	BOOL Verify(CString);			  // Check wether given rule is valid
// Construction
	//These are various file operations that are to performed on files
	BOOL NewFile(void);			// open new or existing file
	DWORD GotoEnd(void);		//move to end of the file
	
/* This is the handle for the file which will be created for saving 
   the user defined rules
*/
	HANDLE _hFile;			
	DWORD SaveFile(char*);
	BOOL CloseFile();

public:
	CAddRuleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddRuleDlg)
	enum { IDD = IDD_ADDRULE };
	CComboBox	m_protocol;
	CComboBox	m_action;
	CString	m_sdadd;
	CString	m_sdport;
	CString	m_ssadd;
	CString	m_ssport;
	//}}AFX_DATA
//**********************************************************************
	TDriver		ipFltDrv;
	DWORD AddFilter(IPFilter );
//**********************************************************************
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddRuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAddRuleDlg)
	afx_msg void OnKillfocusSadd();
	afx_msg void OnKillfocusDadd();
	afx_msg void OnAddsave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDRULEDLG_H__BFC04DB5_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
