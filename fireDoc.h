// fireDoc.h : interface of the CFireDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIREDOC_H__BFC04DAB_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
#define AFX_FIREDOC_H__BFC04DAB_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CFireDoc : public CDocument
{
protected: // create from serialization only
	CFireDoc();
	DECLARE_DYNCREATE(CFireDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFireDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CFireDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CFireDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIREDOC_H__BFC04DAB_65C6_11D7_9C14_CE97B9E6B96A__INCLUDED_)
