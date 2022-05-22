// TimeLog.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TimeLog.h"
#include "TimeLogdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeLogApp

BEGIN_MESSAGE_MAP(CTimeLogApp, CWinApp)
	//{{AFX_MSG_MAP(CTimeLogApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)  

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeLogApp construction

CTimeLogApp::CTimeLogApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTimeLogApp object

CTimeLogApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTimeLogApp initialization

BOOL CTimeLogApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();										   
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	LoadIcon(IDR_MAINFRAME);

	// schon eine andere Instanz am Laufen? Dann diese hier schlieﬂen und die laufende anzeigen
	HWND hWndFind = ::FindWindow(NULL, "Time Log");
	if (hWndFind)
	{
		
		::ShowWindow(hWndFind, SW_SHOW);
		::ShowWindow(hWndFind, SW_RESTORE);
		::SetWindowPos(hWndFind, CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		::SetForegroundWindow(hWndFind);
		return TRUE;
	}

	CTimeLogDlg dlg;
	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the applica

	//m_pMainWnd = &dlg;                                     
	return FALSE;
}
