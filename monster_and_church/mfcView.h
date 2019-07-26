// mfcView.h : interface of the CMfcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCVIEW_H__183174BC_A66F_4A52_9305_641C70718299__INCLUDED_)
#define AFX_MFCVIEW_H__183174BC_A66F_4A52_9305_641C70718299__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct State{
	int m; //monster
	int c; //church
	int b; //boat pos
	State* parent;
}State, *StatePtr;
//typedef StatePtr *State;

class CMfcView : public CView
{
protected: // create from serialization only
	CMfcView();
	DECLARE_DYNCREATE(CMfcView)

// Attributes
public:
	CMfcDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcView)
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
	virtual ~CMfcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	bool isComputeFinished;
	StatePtr curPath[1024];
	int qPathHead, qPathTail, qPathLen;
	int stackBottom, stackTop, stackLen;
	StatePtr visited[2048];
	StatePtr resultPtr;
	State initState;
	int visitedIdx;
	int curIdx;//cur solotion idx
	State statePlace[10];
	State curState;
	int maxM;
	int maxC;
protected:
	void assignState(State &state, int m, int c, int b);
	bool checkFinishSolution(State &state);
	void beginSolve();
	bool isValid(State &state);
	void broadFirstSolve();
	void depthFirstSolve();
	bool isVisited(State &state);
	void addToVisited(StatePtr statePtr);
	bool isStateEqual(State &state1, State &state2);
	void enPathQue(StatePtr statePtr);
	StatePtr ouPathQue();
	bool isPathQueEmpty();
	bool expandNode(StatePtr parent);
	StatePtr getParentState(StatePtr statePtr);
	void pushStack(StatePtr statePtr);
	StatePtr popStack();
	bool expandNodeDepthFirst(StatePtr parent);
	bool isStackEmpty();

// Generated message map functions
protected:
	//{{AFX_MSG(CMfcView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mfcView.cpp
inline CMfcDoc* CMfcView::GetDocument()
   { return (CMfcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCVIEW_H__183174BC_A66F_4A52_9305_641C70718299__INCLUDED_)
