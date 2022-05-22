// RegDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "RegDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define MASTER_VERSION

/////////////////////////////////////////////////////////////////////////////
// CRegDlg dialog


CRegDlg::CRegDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CRegDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegDlg, CDialog)
	//{{AFX_MSG_MAP(CRegDlg)
	ON_BN_CLICKED(IDC_MAKE_NR, OnMakeNr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegDlg message handlers

BOOL CRegDlg::OnInitDialog() 
{
	char buffer[100];

	CDialog::OnInitDialog();
	
	((CEdit *)GetDlgItem(IDC_REG_EDIT))->LimitText(40);
	GetPrivateProfileString(    
		"Registration",	// points to section name 
		"Number",		// points to key name 
		"",				// points to default string 
		buffer,			// points to destination buffer 
		sizeof(buffer),	// size of destination buffer 
		"TimeLog.ini" 	// points to initialization filename 
    );
	buffer[40] = 0;
	SetDlgItemText(IDC_REG_EDIT, buffer);

#ifndef MASTER_VERSION
	((CEdit *)GetDlgItem(IDC_MAKE_NR))->ShowWindow(SW_HIDE);
#endif
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRegDlg::OnOK() 
{
	extern BOOL CheckReg(char *);
	char buffer[100];

	GetDlgItemText(IDC_REG_EDIT, buffer, sizeof(buffer));

	if (CheckReg(buffer))
	{
		WritePrivateProfileString(
			"Registration",	// pointer to section name 
			"Number",		// pointer to key name 
			buffer,			// pointer to string to add 
			"TimeLog.ini" 	// pointer to initialization filename 
		);	
		MessageBox("Registrierung ist erfolgt.", "Info", MB_ICONINFORMATION|MB_OK);

		CDialog::OnOK();
	}
	else
		MessageBox("Registrier-Nr. ist unrichtig.", "Fehler", MB_ICONSTOP|MB_OK);
}

static char key[] = "34095861351326501665808473561843560561125678113487618376284719023560138471287463083176180763856461026";
static char keyindex[] = {
	98, 99, 91, 90, 96, 93, 94, 97, 92, 95, 
	38, 39, 31, 30, 36, 33, 34, 37, 32, 35, 
	18, 19, 11, 10, 16, 13, 14, 17, 12, 15, 
	28, 29, 21, 20, 26, 23, 24, 27, 22, 25, 
	68, 69, 61, 60, 66, 63, 64, 67, 62, 65, 
	 8,  9,  1,  0,  6,  3,  4,  7,  2,  5, 
	88, 89, 81, 80, 86, 83, 84, 87, 82, 85, 
	78, 79, 71, 70, 76, 73, 74, 77, 72, 75, 
	48, 49, 41, 40, 46, 43, 44, 47, 42, 45, 
	58, 59, 51, 50, 56, 53, 54, 57, 52, 55, 
};

void Decrypt(char *into, char *s)
{
	int i;
//strcpy(into, s); return;
	for (i = 0; i < (int)strlen(s); i++)
	{
		into[i] = (((s[i] - '0') + (key[keyindex[i]] - '0')) % 10) + '0';
	}
	into[i]=0;
}

#ifdef MASTER_VERSION
void Crypt(char *into, char *s)
{
	int i;
//strcpy(into, s); return;
	for (i = 0; i < (int)strlen(s); i++)
	{
		into[i] = ((s[i] - '0') - (key[keyindex[i]] - '0') % 10);
		if (into[i] < 0)
			into[i] += 10;
		into[i] += '0';
	}
	into[i] = 0;
}
#endif

// Registriernummern müssen durch 3 teilbar sein
BOOL CheckReg(char *s)
{
	char buffer[100];
	int i;

	if (strlen(s) >= sizeof(buffer)) return FALSE;
	if (strlen(s) != 36) return FALSE;

	Decrypt(buffer, s);

	for (i = 0; i < (int)strlen(s); i+=3)
	{
		if (((buffer[i] - '0') - (buffer[i + 1] - '0')) % 10 != buffer[i + 2] - '0'
		 && ((buffer[i] - '0') - (buffer[i + 1] - '0') + 10) % 10 != buffer[i + 2] - '0')
			return FALSE;
	}

	return TRUE;
}

void GetRegName(char *into, char *s)
{
	int i;
	char buffer[100];

	if (!CheckReg(s))
	{
		*into = 0;
		return;
	}

	Decrypt(buffer, s);
	
	for (i = 0; i < (int)strlen(buffer); i+=3)
		into[i/3] = (buffer[i] - '0') * 10 + buffer[i+1] - '0' + ' ';
	into[i/3] = 0;
}

#ifdef MASTER_VERSION
void RegName2Nr(char *into, char *s)
{
	int i;
	int t;
	char buffer[100];

	if (strlen(s) > 12)
	{
		*into = 0;
		return;
	}

	for (i = 0; i < (int)strlen(s) * 3; i+=3)
	{
		t = s[i/3] - ' ';
		into[i]   = (t / 10) % 10 + '0';
		into[i+1] = t % 10 + '0';
		into[i+2] = ((into[i] - '0') - (into[i+1] - '0'));
		if (into[i+2] < 0)
			into[i+2] += 10;
		into[i+2] += '0';
	}
	into[i] = 0;
	Crypt(buffer, into);
	strcpy(into, buffer);
}
#endif

void CRegDlg::OnMakeNr() 
{
#ifdef MASTER_VERSION
	char buffer[100];
	char buffer1[100];
	char buffer2[100];

	GetDlgItemText(IDC_REG_EDIT, buffer, sizeof(buffer));
	if (strlen(buffer) > 12)
		return;
	sprintf(buffer1, "%-12.12s", buffer);
	RegName2Nr(buffer2, buffer1);
	SetDlgItemText(IDC_REG_EDIT, buffer2);	
#endif
	;
}
