// fireDoc.cpp : implementation of the CFireDoc class
//此文件与主要任务无关，可不必修改

#include "stdafx.h"
#include "fire.h"

#include "fireDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFireDoc

IMPLEMENT_DYNCREATE(CFireDoc, CDocument)

BEGIN_MESSAGE_MAP(CFireDoc, CDocument)
	//{{AFX_MSG_MAP(CFireDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFireDoc construction/destruction

CFireDoc::CFireDoc()
{
	// TODO: add one-time construction code here

}

CFireDoc::~CFireDoc()
{
}

BOOL CFireDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CFireDoc serialization

void CFireDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CFireDoc diagnostics

#ifdef _DEBUG
void CFireDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFireDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFireDoc commands
