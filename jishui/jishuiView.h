// jishuiView.h : interface of the CJishuiView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JISHUIVIEW_H__4CDFD525_EC70_480C_AE5D_119CAE30A09D__INCLUDED_)
#define AFX_JISHUIVIEW_H__4CDFD525_EC70_480C_AE5D_119CAE30A09D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJishuiView : public CView
{
protected: // create from serialization only
	CJishuiView();
	DECLARE_DYNCREATE(CJishuiView)

// Attributes
protected:
	int** totalWater;
	int result;
	bool hasSolved;
public:
	CJishuiDoc* GetDocument();

// Operations
public:
	void solve();
	BOOL removeWater(int r, int c);
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJishuiView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJishuiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJishuiView)
	afx_msg void OnSolve();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in jishuiView.cpp
inline CJishuiDoc* CJishuiView::GetDocument()
   { return (CJishuiDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JISHUIVIEW_H__4CDFD525_EC70_480C_AE5D_119CAE30A09D__INCLUDED_)
