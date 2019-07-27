// jishuiView.cpp : implementation of the CJishuiView class
//

#include "stdafx.h"
#include "jishui.h"

#include "jishuiDoc.h"
#include "jishuiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CJishuiView

IMPLEMENT_DYNCREATE(CJishuiView, CView)

BEGIN_MESSAGE_MAP(CJishuiView, CView)
	//{{AFX_MSG_MAP(CJishuiView)
	ON_COMMAND(ID_SOLVE, OnSolve)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJishuiView construction/destruction

CJishuiView::CJishuiView()
{
	// TODO: add construction code here
	this->hasSolved = false;
}

CJishuiView::~CJishuiView()
{
}

BOOL CJishuiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CJishuiView::solve()
{
	CJishuiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int rowLen = pDoc->getRowLen();
	int colLen = pDoc->getColLen();
	int max = 0;
	//init array
	this->totalWater = (int**)malloc(sizeof(int*)*rowLen);
	for(int i = 0; i < rowLen; ++i)
	{
		this->totalWater[i] = (int*)malloc(sizeof(int)*colLen);
		for(int j = 0; j < colLen; ++j)
		{
			int tmp = pDoc->getElement(i, j);
			max = max < tmp ? tmp : max;
			this->totalWater[i][j] = 0;
		}
	}
	// enter water
	//init 
	for(i = 1; i < rowLen - 1; ++i)
		for(int j = 1; j < colLen - 1; ++j)
		{
			this->totalWater[i][j] = (max - pDoc->getElement(i, j));
		}
	// remove water
	while(true)
	{
		bool tag = false;
		for(i = 1; i < rowLen - 1; ++i)
		for(int j = 1; j < colLen - 1; ++j)
		{
			if(this->removeWater(i, j))
			{
				tag = true;
			}
		}
		if(!tag)break;
	}

	//collect water
	this->result = 0;
	for(i = 1; i < rowLen - 1; ++i)
		for(int j = 1; j < colLen - 1; ++j)
		{
			this->result += this->totalWater[i][j];
		}
	this->hasSolved = true;
}

BOOL CJishuiView::removeWater(int r, int c)
{
	CJishuiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int dir[4][2] = {{-1,0},{0,-1},{1,0}, {0,1}};
	BOOL ret = FALSE;
	for(int i = 0; i < 4; ++i)
	{
		int r1 = r + dir[i][0];
		int c1 = c + dir[i][1];
		int goalHeight = totalWater[r1][c1] + pDoc->getElement(r1, c1);
		int myHeight = totalWater[r][c] + pDoc->getElement(r, c);
		if(goalHeight < myHeight && this->totalWater[r][c] > 0)
		{
			ret = TRUE;
			if(this->totalWater[r][c] > myHeight - goalHeight)
			{
				this->totalWater[r][c] -= (myHeight - goalHeight);
			}
			else
			{
				this->totalWater[r][c] = 0;
			}
		}
	}
	return ret;
}

/////////////////////////////////////////////////////////////////////////////
// CJishuiView drawing

void CJishuiView::OnDraw(CDC* pDC)
{
	CJishuiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	int startx = 100;
	int starty = 140;
	pDC->TextOut(100,100, pDoc->GetPathName());
	int rowLen = pDoc->getRowLen();
	int colLen = pDoc->getColLen();
	int h = 40;
	int w = 20;
	char buf[20];
	memset(buf, 0, 20);
	for(int i = 0; i < rowLen; ++i)
	{
		for(int j = 0; j < colLen; ++j)
		{
			sprintf(buf, "%d", pDoc->getElement(i, j));
			pDC->TextOut(startx + w*j, starty + i*h, buf);
		}
	}
	if(this->hasSolved)
	{
		sprintf(buf, "result is:%d", this->result);
		pDC->TextOut(startx, starty + rowLen * h, buf);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CJishuiView printing

BOOL CJishuiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJishuiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJishuiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CJishuiView diagnostics

#ifdef _DEBUG
void CJishuiView::AssertValid() const
{
	CView::AssertValid();
}

void CJishuiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJishuiDoc* CJishuiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJishuiDoc)));
	return (CJishuiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CJishuiView message handlers

void CJishuiView::OnSolve() 
{
	// TODO: Add your command handler code here
	this->solve();
}
