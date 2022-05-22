// StatAuswahl.cpp : implementation file
//

#include "stdafx.h"
#include "TimeLog.h"
#include "StatAuswahl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatAuswahl dialog


CStatAuswahl::CStatAuswahl(CWnd* pParent /*=NULL*/)
	: CDialog(CStatAuswahl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatAuswahl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatAuswahl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatAuswahl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatAuswahl, CDialog)
	//{{AFX_MSG_MAP(CStatAuswahl)
	ON_BN_CLICKED(IDC_JAHRESSTATISTIK, OnJahresstatistik)
	ON_BN_CLICKED(IDC_MONATSSTATISTIK, OnMonatsstatistik)
	ON_BN_CLICKED(IDC_WOCHENSTATISTIK, OnWochenstatistik)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatAuswahl message handlers

void CStatAuswahl::OnJahresstatistik() 
{
	CDialog::EndDialog(ID_RETURN_JAHRESSTATISTIK);
}

void CStatAuswahl::OnMonatsstatistik() 
{
	CDialog::EndDialog(ID_RETURN_MONATSSTATISTIK);
}

void CStatAuswahl::OnCancel() 
{
	CDialog::EndDialog(ID_RETURN_ABBRUCH);
}

void CStatAuswahl::OnWochenstatistik() 
{
	CDialog::EndDialog(ID_RETURN_WOCHENSTATISTIK);
}
