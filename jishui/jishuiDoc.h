// jishuiDoc.h : interface of the CJishuiDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_JISHUIDOC_H__CF1ED23C_84EA_47CC_8802_4B02E7C210D9__INCLUDED_)
#define AFX_JISHUIDOC_H__CF1ED23C_84EA_47CC_8802_4B02E7C210D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CJishuiDoc : public CDocument
{
protected: // create from serialization only
	CJishuiDoc();
	DECLARE_DYNCREATE(CJishuiDoc)

// Attributes
protected:
	int dataBuf[1024];
	int rowLen;
	int colLen;
public:
	int getElement(int r, int c);
	int getRowLen();
	int getColLen();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJishuiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CJishuiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CJishuiDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JISHUIDOC_H__CF1ED23C_84EA_47CC_8802_4B02E7C210D9__INCLUDED_)
