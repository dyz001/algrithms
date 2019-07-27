// jishuiDoc.cpp : implementation of the CJishuiDoc class
//

#include "stdafx.h"
#include "jishui.h"

#include "jishuiDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJishuiDoc

IMPLEMENT_DYNCREATE(CJishuiDoc, CDocument)

BEGIN_MESSAGE_MAP(CJishuiDoc, CDocument)
	//{{AFX_MSG_MAP(CJishuiDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJishuiDoc construction/destruction

CJishuiDoc::CJishuiDoc()
{
	// TODO: add one-time construction code here
	this->rowLen = 0;
	this->colLen = 0;
	memset(this->dataBuf, 0, 1024*sizeof(int));
}

CJishuiDoc::~CJishuiDoc()
{
}

BOOL CJishuiDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

int CJishuiDoc::getElement(int r, int c)
{
	return this->dataBuf[this->colLen * r + c];
}
int CJishuiDoc::getRowLen()
{
	return this->rowLen;
}
int CJishuiDoc::getColLen()
{
	return this->colLen;
}

BOOL CJishuiDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	FILE* fp = fopen(lpszPathName, "rb");
	char buf[1024];
	int max = 1024;
	memset(buf, 0, 1024);
	int readCnt = fread(buf, 1, 1024, fp);
	fclose(fp);
	int idx = 0; //record \r\n
	int dIdx = 0;
	for (int i = 0; i < readCnt; ++i)
	{
		if (buf[i] == '\r' || buf[i] == '\n')
		{
			if (idx != 0){
				this->rowLen++;
			}
			idx = 0;
			continue;
		}
		this->dataBuf[dIdx++] = buf[i] - '0';
		idx++;
		if (this->rowLen == 0){
			this->colLen++;
		}
	}
	return TRUE;
	/*idx = 0;
	this->wallArray = new int[row][col];
	for (int i = 0; i < row; ++i)
		for(int j = 0; j < col; ++j)
		{
			while (readInt[idx] == -1)
			{
				idx++;
			}
			this->wallArray[i][j] = readInt[idx++];
		}*/
}



/////////////////////////////////////////////////////////////////////////////
// CJishuiDoc serialization

void CJishuiDoc::Serialize(CArchive& ar)
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
// CJishuiDoc diagnostics

#ifdef _DEBUG
void CJishuiDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CJishuiDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJishuiDoc commands
