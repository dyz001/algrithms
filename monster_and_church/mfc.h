// mfc.h : main header file for the MFC application
//

#if !defined(AFX_MFC_H__CBEA1E06_E46A_4C43_9B61_F39F49493619__INCLUDED_)
#define AFX_MFC_H__CBEA1E06_E46A_4C43_9B61_F39F49493619__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfcApp:
// See mfc.cpp for the implementation of this class
//

class CMfcApp : public CWinApp
{
public:
	CMfcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMfcApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC_H__CBEA1E06_E46A_4C43_9B61_F39F49493619__INCLUDED_)
