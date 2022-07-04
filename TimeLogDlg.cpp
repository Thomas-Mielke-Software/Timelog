// TimeLogdlg.cpp : implementation file
//

#include "stdafx.h"
#include "TimeLog.h"
#include "TimeLogdlg.h"
#include <afx.h>

#include "SmFormat.h"
#include "StatAuswahl.h"
#include "Statistik.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()		

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg message handlers
			  

#include "getprogramversion.h"

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CenterWindow();

	char version_string[100];
	{
		HMODULE hExe = GetModuleHandle("TIMELOG.EXE");
		VS_FIXEDFILEINFO vs_ffi;
		if (hExe) 
		{
			GetProgramVersion(hExe, &vs_ffi);	// version_string := "v2.0" oder so ähnlich
			sprintf(version_string, "v%0lu.%0lu", vs_ffi.dwProductVersionMS >> 16, vs_ffi.dwProductVersionMS & 0xffff);
		}
		else 
			*version_string = '\0';
	}
	SetDlgItemText(IDC_VERSION, version_string);	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


///////////////////
// CTimeLogDlg dialog

CTimeLogDlg::CTimeLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeLogDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	liste = NULL;
	liste_gefiltert = NULL;
	size_of_liste = 0;
	timer = 0;
}

CTimeLogDlg::~CTimeLogDlg()
{
	if (liste) delete liste;
}

void CTimeLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeLogDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTimeLogDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeLogDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDABOUT, OnAbout)
	ON_EN_SETFOCUS(IDC_BESCHREIBUNG, OnFocusBeschreibung)
	ON_BN_CLICKED(IDDELETE, OnDelete)
	ON_BN_CLICKED(IDBISZEIT, OnBiszeit)
	ON_EN_ERRSPACE(IDC_LISTE, OnErrspaceListe)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDSTATISTIKEN, OnStatistiken)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_VON, OnKillfocusVon)
	ON_EN_KILLFOCUS(IDC_BESCHREIBUNG, OnKillfocusBeschreibung)
	ON_EN_CHANGE(IDC_KUERZEL, OnChangeKuerzel)
	ON_EN_CHANGE(IDC_KUERZEL2, OnChangeKuerzel2)
	ON_BN_CLICKED(IDVONZEIT, OnVonzeit)
	ON_BN_CLICKED(IDVONDATUM, OnVondatum)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_FILTERN, &CTimeLogDlg::OnBnClickedFiltern)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeLogDlg message handlers

BOOL CTimeLogDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	ShowWindow(SW_HIDE);

	//CenterWindow();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Set the icon in the status area of the taskbar
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = STATUS_ICON_ID;
	nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nid.uCallbackMessage = MYWM_NOTIFYICON;
	nid.hIcon = m_hIcon;
	strcpy(nid.szTip, "TimeLog öffnen mit Doppelklick");
	Shell_NotifyIcon(NIM_ADD, &nid); 
	
	int TabStopArray[2] = { 110, 150 };
	((CEdit *)GetDlgItem(IDC_LISTE))->SetTabStops(1, TabStopArray);	


	{
		CFile pFile;
		
	
		if (pFile.Open(GetFilename(), CFile::modeRead))
		{
			liste = new char[(size_of_liste = pFile.GetLength() + 20000)]; 
			
			memset(liste, '\0', size_of_liste);
			
			pFile.Seek(0, CFile::begin);
			pFile.Read(liste, size_of_liste);

			SetDlgItemText(IDC_LISTE, liste);

			pFile.Close();
		}
		else
		{
			liste = new char[(size_of_liste = 20000)];
			memset(liste, '\0', size_of_liste);
		}

	}

	// Datum + Uhrzeit
	{
		char buffer[20], buffer2[200];
		CTime now = now.GetCurrentTime();                           
		StreamFormat *sf = new StreamFormat(liste);
		//ostrstream datebuf(buffer,20);	  						

		GetPrivateProfileString(
			"SafeIt",		// pointer to section name 
			"Kuerzelzwang",	// pointer to key name 
			"0",			// points to default string 
			buffer2,		// points to destination buffer 
			sizeof(buffer2),// size of destination buffer 
			GetIniPath() 	// pointer to initialization filename 
		);	
		if (*buffer2 != '0') 
			((CButton *)GetDlgItem(IDC_CHECK))->SetCheck(1);
		else
			((CButton *)GetDlgItem(IDC_CHECK))->SetCheck(0);

		//datebuf << now.GetDay() << now.GetMonth() << now.GetYear();	
		
		sprintf(buffer, "%02d.%02d.%02d", now.GetDay(), now.GetMonth(), now.GetYear() % 100);
		SetDlgItemText(IDC_DATUM, buffer);

		// Checken, ob es von heute schon eine Sicherheitskopie gibt:
		GetPrivateProfileString(
			"SafeIt",		// pointer to section name 
			"Date",			// pointer to key name 
			"",				// points to default string 
			buffer2,		// points to destination buffer 
			sizeof(buffer2),// size of destination buffer 
			GetIniPath() 	// pointer to initialization filename 
		);	
		if (!strcmp(buffer, buffer2))
		{
			GetPrivateProfileString(
				"SafeIt",		// pointer to section name 
				"StartTime",	// pointer to key name 
				"",				// points to default string 
				buffer2,		// points to destination buffer 
				sizeof(buffer2),// size of destination buffer 
				GetIniPath() 	// pointer to initialization filename 
			);	
			SetDlgItemText(IDC_VON, buffer2);
			GetPrivateProfileString(
				"SafeIt",		// pointer to section name 
				"Description",	// pointer to key name 
				"",				// points to default string 
				buffer2,		// points to destination buffer 
				sizeof(buffer2),// size of destination buffer 
				GetIniPath() 	// pointer to initialization filename 
			);	
			SetDlgItemText(IDC_BESCHREIBUNG, buffer2);
		}
		else		
		{	
			if (sf->GetRows() && !strcmp(sf->GetText(sf->GetRows() - 1, 0, 8), buffer))
			{
				SetDlgItemText(IDC_VON, sf->GetText(sf->GetRows() - 1, 15, 20));
			}
			else
			{
				sprintf(buffer, "%02d:%02d", now.GetHour(), now.GetMinute());
				SetDlgItemText(IDC_VON, buffer);
			}
		}
		delete sf;

		UpdateSelektiertSumme();
	}		

	((CEdit *)GetDlgItem(IDC_BESCHREIBUNG))->LimitText(40);
	((CEdit *)GetDlgItem(IDC_DATUM))->LimitText(8);
	((CEdit *)GetDlgItem(IDC_VON))->LimitText(5);
	((CEdit *)GetDlgItem(IDC_BIS))->LimitText(5);
	((CEdit *)GetDlgItem(IDC_KUERZEL))->LimitText(1);

	UpdateGesamtsumme();

	//Reg();
	
	SetTimer(99, 1, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTimeLogDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE)
	{
		ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimeLogDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimeLogDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTimeLogDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();

	//Reg();
}

void CTimeLogDlg::OnFocusBeschreibung() 
{
	// TODO: Add your control notification handler code here
	
}

void CTimeLogDlg::OnOK() 
{
	char buffer[80];
	char buffer2[80];
	char buffer3[80];

	if (((CButton *)GetDlgItem(IDC_CHECK))->GetCheck())
	{
		char kuerzel[2];
		GetDlgItemText(IDC_KUERZEL, kuerzel, sizeof(kuerzel));
		if (!*kuerzel) 
		{
			MessageBox("Wenn die Check-Box angekreuzt ist, muss ein Kürzel angegeben werden!");			
			GetDlgItem(IDC_KUERZEL)->SetFocus();
			return;
		}
	}	

	*buffer = '\0';
	GetDlgItemText(IDC_DATUM, buffer2, sizeof(buffer2));
	strcat(buffer, buffer2); strcat(buffer, " ");
	{// Syntax-Check Datum:
		if (strlen(buffer2) != 8 ||
			!isdigit(buffer2[0]) ||
			!isdigit(buffer2[1]) ||
			buffer2[2] != '.' ||
			!isdigit(buffer2[3]) ||
			!isdigit(buffer2[4]) ||
			buffer2[5] != '.' ||
			!isdigit(buffer2[6]) ||
			!isdigit(buffer2[7]))
		{
			MessageBox("Datumsformat muss dem Schema ##.##.## entsprechen!");
			GetDlgItem(IDC_DATUM)->SetFocus();
			return;
		}
	}
	GetDlgItemText(IDC_VON, buffer3, sizeof(buffer3));
	strcat(buffer, buffer3); strcat(buffer, " ");
	{// Syntax-Check Zeit:
		if (strlen(buffer3) != 5 ||
			!isdigit(buffer3[0]) ||
			!isdigit(buffer3[1]) ||
			buffer3[2] != ':' ||
			!isdigit(buffer3[3]) ||
			!isdigit(buffer3[4]))
		{
			MessageBox("Zeitformat muss dem Schema ##:## entsprechen!");
			GetDlgItem(IDC_VON)->SetFocus();
			return;
		}
	}
	// spezialbehandlung für Bis-Zeit:
	{
		GetDlgItemText(IDC_BIS, buffer2, sizeof(buffer2));
		if (!*buffer2)
		{	
			CTime now = now.GetCurrentTime();                           
		
			sprintf(buffer2, "%02d:%02d", now.GetHour(), now.GetMinute());
			SetDlgItemText(IDC_BIS, buffer2);
		}		
		strcat(buffer, buffer2); strcat(buffer, " ");
	}
	{// Syntax-Check Zeit:
		if (strlen(buffer2) != 5 ||
			!isdigit(buffer2[0]) ||
			!isdigit(buffer2[1]) ||
			buffer2[2] != ':' ||
			!isdigit(buffer2[3]) ||
			!isdigit(buffer2[4]))
		{
			MessageBox("Zeitformat muss dem Schema ##:## entsprechen!");
			GetDlgItem(IDC_BIS)->SetFocus();
			return;
		}
	}
	
	// Berechnung der Einzelzeit
	{
		buffer2[2] = '\0';
		buffer3[2] = '\0';
		int von, bis;

		von = atol(buffer3) * 60 + atol(buffer3+3);
		bis = atol(buffer2) * 60 + atol(buffer2+3);

		if (von >= bis)
		{	
			MessageBox("Von-Zeit muss vor der Bis-Zeit liegen!", "Fehler", MB_ICONEXCLAMATION | MB_OK);
			return;
		}
		else
		{
			sprintf(buffer2, "%2d:%02d", (bis - von) / 60, (bis - von) % 60);
			strcat(buffer, buffer2); strcat(buffer, " ");
		}
	}
	GetDlgItemText(IDC_KUERZEL, buffer2, sizeof(buffer2));
	strcat(buffer, buffer2); strcat(buffer, "   \t");
	GetDlgItemText(IDC_BESCHREIBUNG, buffer2, sizeof(buffer2));
	strcat(buffer, buffer2); strcat(buffer, "\r\n");
	{// Syntax-Check BESCHREIBUNG:
		if (strlen(buffer2) == 0)
		{
			MessageBox("Beschreibung wurde nicht eingegeben!");
			GetDlgItem(IDC_BESCHREIBUNG)->SetFocus();
			return;
		}
	}
	
	if (strlen(liste) < size_of_liste - sizeof(buffer))
		strcat(liste, buffer);
	else
		OnErrspaceListe();
	
	OnBnClickedFiltern();
											  
	SaveListe();

	SetDlgItemText(IDC_BESCHREIBUNG, "");
	GetDlgItemText(IDC_BIS, buffer2, sizeof(buffer2));
	SetDlgItemText(IDC_VON, buffer2);
	SetDlgItemText(IDC_BIS, "");
	GetDlgItem(IDC_BESCHREIBUNG)->SetFocus();

	UpdateGesamtsumme();
}

void CTimeLogDlg::UpdateGesamtsumme()
{// Gesamt-Summe updaten...
	char buffer[30];
	long hours, minutes;
	StreamFormat *sf = new StreamFormat(liste);

	hours   = sf->ColSum(21, 23, NULL, NULL, 0);
	minutes = sf->ColSum(24, 26, NULL, NULL, 0);

	hours   += minutes / 60;
	minutes	 = minutes % 60;

	sprintf(buffer, "%2ld:%02ld", hours, minutes);

	SetDlgItemText(IDC_GESAMT, buffer);
	GetDlgItem(IDC_LISTE)->SendMessage(
		EM_LINESCROLL, (WPARAM) 0, sf->GetRows() - 8L);

	delete sf;
}


void CTimeLogDlg::UpdateSelektiertSumme()
{
	char buffer[30];
	long hours, minutes;
	DWORD start_pos, end_pos;
	char *cp1, *cp2;
	char save_it;
	char* welche_liste;

	if (((CButton*)GetDlgItem(IDC_FILTERN))->GetCheck())
		welche_liste = liste_gefiltert;
	else
		welche_liste = liste;

	GetDlgItem(IDC_LISTE)->SendMessage(
		EM_GETSEL, 
		(WPARAM) (LPDWORD) &start_pos, 
		(LPARAM) (LPDWORD) &end_pos	  );

	if ((!start_pos && !end_pos) || 
		start_pos >= end_pos ||
		start_pos > strlen(welche_liste) ||
		end_pos   > strlen(welche_liste))
	{
		SetDlgItemText(IDC_SELEKTIERT, "0:00");
		return;
	}

	char kuerzel[2];
	GetDlgItemText(IDC_KUERZEL2, kuerzel, sizeof(kuerzel));
	*kuerzel = toupper(*kuerzel);

	for (cp1 = welche_liste + start_pos; cp1 > welche_liste; cp1--)
		if (!strncmp("\r\n", cp1, 2))
		{
			cp1 += 2;
			break;
	}

	cp2 = welche_liste + end_pos;
	if (!(end_pos >= 2 && !strncmp("\r\n", cp2 - 2, 2)))
		for (; *cp2; cp2++)
			if (!strncmp("\r\n", cp2, 2))
			{
				break;
			}

	save_it = cp2[2];
	cp2[2] = '\0';

	StreamFormat *sf = new StreamFormat(cp1);
	
	hours   = sf->ColSum(21, 23, NULL, NULL, *kuerzel);
	minutes = sf->ColSum(24, 26, NULL, NULL, *kuerzel);

	hours   += minutes / 60;
	minutes	 = minutes % 60;

	sprintf(buffer, "%2ld:%02ld", hours, minutes);

	SetDlgItemText(IDC_SELEKTIERT, buffer);

	cp2[2] = save_it;	// wiederherstellen
	
	delete sf;
}


void CTimeLogDlg::SaveListe()
{
	CFile pFile;

	if (pFile.Open(GetFilename(), CFile::modeWrite | CFile::modeCreate))
	{
		pFile.Seek(0, CFile::begin);
		pFile.Write(liste, strlen(liste));

		pFile.Close();
	}
}


void CTimeLogDlg::OnDelete() 
{
	if (MessageBox("Liste wirklich löschen?", "Löschen", MB_ICONQUESTION | MB_YESNO) == IDYES)
	{
		memset(liste, '\0', size_of_liste);
		SetDlgItemText(IDC_LISTE, "");
	}

	SaveListe();
}

void CTimeLogDlg::OnVonzeit() 
{
	char buffer[20];
	CTime now = now.GetCurrentTime();                           
	
	sprintf(buffer, "%02d:%02d", now.GetHour(), now.GetMinute());
	SetDlgItemText(IDC_VON, buffer);

	OnVondatum();
}

void CTimeLogDlg::OnBiszeit() 
{
	char buffer[20];
	CTime now = now.GetCurrentTime();                           
	
	sprintf(buffer, "%02d:%02d", now.GetHour(), now.GetMinute());
	SetDlgItemText(IDC_BIS, buffer);

	GetDlgItem(IDC_BESCHREIBUNG)->SetFocus();
}

void CTimeLogDlg::OnVondatum() 
{
	char buffer[20];
	CTime now = now.GetCurrentTime();                           
	
	sprintf(buffer, "%02d.%02d.%02d", now.GetDay(), now.GetMonth(), now.GetYear()%100);
	SetDlgItemText(IDC_DATUM, buffer);

	GetDlgItem(IDC_BESCHREIBUNG)->SetFocus();
}


void CTimeLogDlg::OnErrspaceListe() 
{
	MessageBox("Liste hat die maximale Aufnahmekapazität für Einträge erreicht. Bitte die TimeLog.txt-Datei löschen/umbenennen, um mit einem neuer neuen Log-Datei zu beginnen");
}

void CTimeLogDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	UpdateSelektiertSumme();
	
	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CTimeLogDlg::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_MOUSEMOVE)
	{
		;
		/*&& pMsg->lParam == WM_LBUTTONUP IDC_LISTE)*/
		UpdateSelektiertSumme();
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CTimeLogDlg::OnStatistiken() 
{
	int choice;

	CStatAuswahl *dlg = new CStatAuswahl(this);
	choice = dlg->DoModal();
	delete dlg;	

	switch (choice)
	{
		case ID_RETURN_WOCHENSTATISTIK:
			break;
		case ID_RETURN_MONATSSTATISTIK:
			break;
		case ID_RETURN_JAHRESSTATISTIK:
			break;
		case ID_RETURN_ABBRUCH:
		default:
			return;
	}

	StreamFormat *sf = new StreamFormat(liste);
	CStatistik *dlg2 = new CStatistik(this, choice, sf);
	choice = dlg2->DoModal();
	delete dlg2;	
	delete sf;
}

void CTimeLogDlg::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 99)
	{
		ShowWindow(SW_HIDE);
		KillTimer(99);
	}

	UpdateSelektiertSumme();
	
	CDialog::OnTimer(nIDEvent);
}

void CTimeLogDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(nid);
	nid.hWnd = m_hWnd;
	nid.uID = STATUS_ICON_ID;
	Shell_NotifyIcon(NIM_DELETE, &nid);		
	
	if (timer) KillTimer(timer);	timer = 0;

	if (((CButton *)GetDlgItem(IDC_CHECK))->GetCheck())
		WritePrivateProfileString(
			"SafeIt",	// pointer to section name 
			"Kuerzelzwang",	// pointer to key name 
			"1",			// pointer to string to add 
			GetIniPath() 	// pointer to initialization filename 
		);	
	else
		WritePrivateProfileString(
			"SafeIt",	// pointer to section name 
			"Kuerzelzwang",	// pointer to key name 
			"0",			// pointer to string to add 
			GetIniPath() 	// pointer to initialization filename 
		);	

	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void CTimeLogDlg::OnKillfocusVon() 
{
	SaveIt();
}

void CTimeLogDlg::OnKillfocusBeschreibung() 
{
	SaveIt();
}

void CTimeLogDlg::SaveIt()
{
	char buffer[200];
	GetDlgItemText(IDC_DATUM, buffer, sizeof(buffer));
	WritePrivateProfileString(
		"SafeIt",	// pointer to section name 
		"Date",		// pointer to key name 
		buffer,			// pointer to string to add 
		GetIniPath() 	// pointer to initialization filename 
	);	
	GetDlgItemText(IDC_VON, buffer, sizeof(buffer));
	WritePrivateProfileString(
		"SafeIt",	// pointer to section name 
		"StartTime",		// pointer to key name 
		buffer,			// pointer to string to add 
		GetIniPath() 	// pointer to initialization filename 
	);	
	GetDlgItemText(IDC_BESCHREIBUNG, buffer, sizeof(buffer));
	WritePrivateProfileString(
		"SafeIt",	// pointer to section name 
		"Description",		// pointer to key name 
		buffer,			// pointer to string to add 
		GetIniPath() 	// pointer to initialization filename 
	);	
}

void CTimeLogDlg::OnChangeKuerzel() 
{
	char kuerzel[2];
	GetDlgItemText(IDC_KUERZEL, kuerzel, sizeof(kuerzel));
	if (!*kuerzel) return;
	kuerzel[1] = '\0';
	if (!isalpha(*kuerzel))
	{
		*kuerzel = '\0';
		Beep(500,50);
		SetDlgItemText(IDC_KUERZEL, kuerzel);
	}
	else
	{
		if (*kuerzel != toupper(*kuerzel))
		{
			*kuerzel = toupper(*kuerzel);
			SetDlgItemText(IDC_KUERZEL, kuerzel);
		}
	}
}

void CTimeLogDlg::OnChangeKuerzel2() 
{
	char kuerzel[2];
	GetDlgItemText(IDC_KUERZEL2, kuerzel, sizeof(kuerzel));
	if (!*kuerzel) return;
	kuerzel[1] = '\0';
	if (!isalpha(*kuerzel))
	{
		*kuerzel = '\0';
		Beep(500,50);
		SetDlgItemText(IDC_KUERZEL2, kuerzel);
	}
	else
	{
		if (*kuerzel != toupper(*kuerzel))
		{
			*kuerzel = toupper(*kuerzel);
			SetDlgItemText(IDC_KUERZEL2, kuerzel);
		}
		OnBnClickedFiltern();
	}
}

LRESULT CTimeLogDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if (message == MYWM_NOTIFYICON)
	{
		On_MYWM_NOTIFYICON(wParam, lParam);
		return TRUE;
	}
	else
	
	return CDialog::WindowProc(message, wParam, lParam);
}



// On_MYWM_NOTIFYICON - processes callback messages for taskbar icons  
// wParam - first message parameter of the callback message 
// lParam - second message parameter of the callback message 
void CTimeLogDlg::On_MYWM_NOTIFYICON(WPARAM wParam, LPARAM lParam) 
{ 
    UINT uID; 
    UINT uMouseMsg; 
 
    uID = (UINT) wParam; 
    uMouseMsg = (UINT) lParam; 
 
    if (uID == STATUS_ICON_ID)
	{ 
        switch (uMouseMsg) 
		{ 
            case WM_LBUTTONDBLCLK:
				ShowWindow(SW_SHOW);
				ShowWindow(SW_RESTORE);
				SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_SHOWWINDOW);					
                break; 

            default: 
                break; 
        } 
    } 
    return; 
} 

void CTimeLogDlg::OnCancel() 
{
	if (AfxMessageBox("TimeLog wirklich deaktivieren?", MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2) == IDNO) return;
	
	CDialog::OnCancel();
}

char *CTimeLogDlg::GetFilename()
{
	extern CTimeLogApp theApp;
	static char filename[1000];
	GetModuleFileName(theApp.m_hInstance, filename, sizeof(filename));
	static char defaultpath[1000];
	strcpy(defaultpath, filename);
	while (strlen(defaultpath) && defaultpath[strlen(defaultpath)-1] != '\\')
	{
		defaultpath[strlen(defaultpath)-1] = '\0';
	}
	strcat(defaultpath, "TimeLog.txt");	
	GetPrivateProfileString("TimeLog", "LogFile", defaultpath, filename, sizeof(filename), GetIniPath());
	return filename;
}

char *CTimeLogDlg::GetIniPath()
{
	extern CTimeLogApp theApp;
	static char inipath[1000];
	GetModuleFileName(theApp.m_hInstance, inipath, sizeof(inipath));
	while (strlen(inipath) && inipath[strlen(inipath)-1] != '\\')
	{
		inipath[strlen(inipath)-1] = '\0';
	}
	strcat(inipath, "TimeLog.ini");	
	return inipath;
}

void CTimeLogDlg::OnBnClickedFiltern()
{
	if (((CButton*)GetDlgItem(IDC_FILTERN))->GetCheck())
	{
		if (!liste_gefiltert)
			liste_gefiltert = new char[(size_of_liste + 20000)];

		memset(liste_gefiltert, '\0', size_of_liste + 20000);

		char kuerzel[2];
		GetDlgItemText(IDC_KUERZEL2, kuerzel, sizeof(kuerzel));
		*kuerzel = toupper(*kuerzel);

		char *cp1, *cp2, *cp3, *zeilenanfang;
		int spaltenzaehler = 0;
		BOOL bFiltern = TRUE;
		for (cp1 = liste, cp2 = zeilenanfang = liste_gefiltert; *cp2 = *cp1;)
		{
			if (!strncmp("31.08.19 13:18", cp1, 14))
			{
				cp3 = cp2;
			}

			// out of memory?
			if (cp2 - liste_gefiltert >= size_of_liste + 20000)
			{
				cp2[size_of_liste + 20000 - 1] = '\0';
				OnErrspaceListe();
				break;
			}

			// Wert in Kürzelspalte
			if (spaltenzaehler == 27)
			{
				if (*kuerzel == *cp1)
					bFiltern = FALSE;
				else
					bFiltern = TRUE;
			}

			if (!strncmp("\r\n", cp1, 2))
			{
				if (bFiltern)
				{
					if (zeilenanfang == liste_gefiltert)
						cp2 = zeilenanfang - 1;
					else
						cp2 = zeilenanfang;   // zurück auf Anfang
					cp1++;
				}
				else
				{
					*(++cp2) = *(++cp1);  // auch noch '\n' kopieren
					zeilenanfang = cp2;
				}

				bFiltern = TRUE;
				spaltenzaehler = 0;
			}
			else
				spaltenzaehler++;

			cp1++; cp2++;
		}

		SetDlgItemText(IDC_LISTE, liste_gefiltert);
		GetDlgItem(IDOK)->EnableWindow(false);  // speichern unterbinden
	}
	else
	{
		SetDlgItemText(IDC_LISTE, liste);
		GetDlgItem(IDOK)->EnableWindow();		// speichern wieder erlauben
	}
}
