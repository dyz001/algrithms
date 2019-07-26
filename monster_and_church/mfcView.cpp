// mfcView.cpp : implementation of the CMfcView class
//

#include "stdafx.h"
#include "mfc.h"

#include "mfcDoc.h"
#include "mfcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfcView

IMPLEMENT_DYNCREATE(CMfcView, CView)

BEGIN_MESSAGE_MAP(CMfcView, CView)
	//{{AFX_MSG_MAP(CMfcView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcView construction/destruction

CMfcView::CMfcView()
{
	// TODO: add construction code here
	this->isComputeFinished = false;
	this->maxM = 3;
	this->maxC = 3;
	this->resultPtr = 0;
	this->qPathHead = this->qPathTail = 0;
	this->stackBottom = this->stackTop = 0;
	this->qPathLen = 1024;
	this->visitedIdx = 0;
	this->curIdx = 0;
	memset(this->curPath, 0, sizeof(StatePtr));
	this->assignState(this->statePlace[0], -1, -1, 1);
	this->assignState(this->statePlace[1], -2, 0, 1);
	this->assignState(this->statePlace[2], 0, -2, 1);
	this->assignState(this->statePlace[3], -1, 0, 1);
	this->assignState(this->statePlace[4], 0, -1, 1);
	this->assignState(this->statePlace[5], 1, 1, 0);
	this->assignState(this->statePlace[6], 2, 0, 0);
	this->assignState(this->statePlace[7], 0, 2, 0);
	this->assignState(this->statePlace[8], 1, 0, 0);
	this->assignState(this->statePlace[9], 0, 1, 0);
	this->assignState(this->initState, this->maxM, this->maxC, 0);
	this->assignState(this->curState, this->maxM, this->maxC, 0);
	this->beginSolve();
}

void CMfcView::assignState(State &state, int m, int c, int b){
	state.b = b;
	state.c = c;
	state.m = m;
	state.parent = 0;
}

bool CMfcView::isValid(State &state){
	State tmp;
	tmp.m = this->curState.m + state.m;
	tmp.b = state.b;
	tmp.c = this->curState.c + state.c;
	if((tmp.m > tmp.c && tmp.c > 0) || 
		tmp.m < 0 || 
		tmp.c < 0 || 
		((this->maxM - tmp.m) > (this->maxC - tmp.c) && this->maxC - tmp.c > 0) || 
		tmp.m > this->maxM || 
		tmp.c > this->maxC || 
		this->curState.b == state.b)return false;
	return true;
}

void CMfcView::beginSolve(){
	
	this->depthFirstSolve();
}
bool CMfcView::isStateEqual(State &state1, State &state2){
	return state1.b == state2.b && state1.c == state2.c && state1.m == state2.m;
}
void CMfcView::enPathQue(StatePtr statePtr){
	this->curPath[this->qPathTail%this->qPathLen] = statePtr;
	this->qPathTail++;
}
StatePtr CMfcView::ouPathQue(){
	StatePtr ret = this->curPath[this->qPathHead%this->qPathLen];
	this->qPathHead++;
	return ret;
}
bool CMfcView::isPathQueEmpty(){
	return this->qPathHead == this->qPathTail;
}
void CMfcView::addToVisited(StatePtr statePtr){
	this->visited[this->visitedIdx] = (StatePtr)malloc(sizeof(State));
	this->visited[this->visitedIdx]->b = this->curState.b;
	this->visited[this->visitedIdx]->m = this->curState.m;
	this->visited[this->visitedIdx]->c = this->curState.c;
	this->visited[this->visitedIdx]->parent = this->curState.parent;
	this->visitedIdx++;
	this->visited[this->visitedIdx] = statePtr;
	this->visitedIdx++;
}
StatePtr CMfcView::getParentState(StatePtr statePtr){
	for(int i = 0; i < this->visitedIdx; i += 2){
		if(this->visited[i+1] == statePtr->parent){
			return this->visited[i];
		}
	}
	return 0;
}
bool CMfcView::isVisited(State &state){
	for(int i = 0; i < this->visitedIdx; i += 2){
		if(!this->visited[i] || !this->visited[i + 1])continue;
		if(this->isStateEqual(this->curState, *this->visited[i]) && this->isStateEqual(state, *this->visited[i+1]))return true;
	}
	return false;
}
bool CMfcView::expandNode(StatePtr parent){
	bool ret = false;
	for(int i = 0; i < 10; i++){
		if(this->isValid(this->statePlace[i]) && !this->isVisited(this->statePlace[i])){
			ret = true;
			StatePtr statePtr = (StatePtr)malloc(sizeof(State));
			this->assignState(*statePtr, this->statePlace[i].m, this->statePlace[i].c, this->statePlace[i].b);
			statePtr->parent = parent;
			if(statePtr->m == 2 && statePtr->c == 0 && statePtr->b == 0){
				if(this->curState.m == 2 && this->curState.c == 3 && this->curState.b == 2){
					break;
				}
			}
			this->addToVisited(statePtr);
			this->enPathQue(statePtr);
		}
	}
	return ret;
}
void CMfcView::broadFirstSolve(){
	StatePtr parent = 0;
	if(this->qPathTail > 0){
		parent = this->curPath[this->qPathTail - 1];
	}
	this->expandNode(parent);
	State tmpState = this->curState;
	while(!this->isPathQueEmpty()){
		StatePtr statePtr = this->ouPathQue();
		StatePtr parentState = this->getParentState(statePtr);
		if(parentState){
			this->curState.m = parentState->m + statePtr->parent->m;
			this->curState.c = parentState->c + statePtr->parent->c;
			this->curState.b = statePtr->parent->b;
		}else{
			this->curState = this->initState;
		}
		tmpState = this->curState;
		tmpState.m += statePtr->m;
		tmpState.c += statePtr->c;
		tmpState.b = statePtr->b;
		if(this->checkFinishSolution(tmpState)){
			this->resultPtr = statePtr;
			return;
		}
		else{
			this->curState = tmpState;
			this->expandNode(statePtr);
		}
	}
}
void CMfcView::depthFirstSolve(){
	this->expandNodeDepthFirst(0);
	State tmpState = this->curState;
	while(!this->isStackEmpty()){
		StatePtr statePtr = this->popStack();
		StatePtr parentState = this->getParentState(statePtr);
		if(parentState){
			this->curState.m = parentState->m + statePtr->parent->m;
			this->curState.c = parentState->c + statePtr->parent->c;
			this->curState.b = statePtr->parent->b;
		}else{
			this->curState = this->initState;
		}
		tmpState = this->curState;
		tmpState.m += statePtr->m;
		tmpState.c += statePtr->c;
		tmpState.b = statePtr->b;
		if(this->checkFinishSolution(tmpState)){
			this->resultPtr = statePtr;
			return;
		}
		else
		{
			this->curState = tmpState;
			this->expandNodeDepthFirst(statePtr);
		}
	}
}
bool CMfcView::isStackEmpty(){
	return this->stackBottom == this->stackTop;
}
void CMfcView::pushStack(StatePtr statePtr){
	int idx = this->stackTop % this->stackLen;
	this->curPath[idx] = statePtr;
	this->stackTop++;
}
StatePtr CMfcView::popStack(){
	int idx = (this->stackTop - 1) % this->stackLen;
	StatePtr ret = this->curPath[idx];
	this->stackTop--;
	return ret;
}
bool CMfcView::expandNodeDepthFirst(StatePtr parent){
	bool ret = false;
	for(int i = 0; i < 10; i++){
		if(this->isValid(this->statePlace[i]) && !this->isVisited(this->statePlace[i])){
			ret = true;
			StatePtr statePtr = (StatePtr)malloc(sizeof(State));
			this->assignState(*statePtr, this->statePlace[i].m, this->statePlace[i].c, this->statePlace[i].b);
			statePtr->parent = parent;
			if(statePtr->m == 2 && statePtr->c == 0 && statePtr->b == 0){
				if(this->curState.m == 2 && this->curState.c == 3 && this->curState.b == 2){
					break;
				}
			}
			this->addToVisited(statePtr);
			this->pushStack(statePtr);
		}
	}
	return ret;
}

bool CMfcView::checkFinishSolution(State &state){
	return state.b == 1 && state.m == 0 && state.c == 0;
}

CMfcView::~CMfcView()
{
}

BOOL CMfcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcView drawing

void CMfcView::OnDraw(CDC* pDC)
{
	CMfcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	StatePtr solution[100];
	StatePtr end = this->resultPtr;
	int i = 0;
	solution[i] = end;
	while(end->parent){
		end = end->parent;
		solution[++i] = end;
	}
	solution[++i] = end;
	pDC->TextOut(100,100, "m    c    b");
	int height = 40;
	State s;
	s.m = this->maxM;
	s.c = this->maxC;
	s.b = 0;
	char buf[100];
	sprintf(buf, "%d    %d    %d", s.m, s.c, s.b);
	pDC->TextOut(100,100 + height, buf);
	int maxId = i;
	for(int idx = 0; idx < maxId; ++idx){
		i--;
		s.m = s.m + solution[i]->m;
		s.c = s.c + solution[i]->c;
		s.b = solution[i]->b;
		sprintf(buf, "%d    %d    %d", s.m, s.c, s.b);
		pDC->TextOut(100,100 + (idx+2) * height, buf);
	} 
}

/////////////////////////////////////////////////////////////////////////////
// CMfcView printing

BOOL CMfcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMfcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMfcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMfcView diagnostics

#ifdef _DEBUG
void CMfcView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcDoc* CMfcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcDoc)));
	return (CMfcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcView message handlers
