// mfcDoc.cpp : implementation of the CMfcDoc class
//

#include "stdafx.h"
#include "mfc.h"

#include "mfcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcDoc

IMPLEMENT_DYNCREATE(CMfcDoc, CDocument)

BEGIN_MESSAGE_MAP(CMfcDoc, CDocument)
	//{{AFX_MSG_MAP(CMfcDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcDoc construction/destruction

CMfcDoc::CMfcDoc()
{
	// TODO: add one-time construction code here

}

CMfcDoc::~CMfcDoc()
{
}

BOOL CMfcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMfcDoc serialization

void CMfcDoc::Serialize(CArchive& ar)
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
// CMfcDoc diagnostics

#ifdef _DEBUG
void CMfcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMfcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcDoc commands
