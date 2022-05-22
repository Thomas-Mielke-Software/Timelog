// Statistik.cpp : implementation file
//

#include "stdafx.h"
#include <afxcmn.h>
#include "Test.h"
#include "smformat.h"
#include "StatAuswahl.h"
#include "Statistik.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatistik dialog


CStatistik::CStatistik(CWnd* pParent, int art, StreamFormat *sf)
	: CDialog(CStatistik::IDD, pParent)
{
	StatistikArt = art;
	sfDaten = sf;

	//{{AFX_DATA_INIT(CStatistik)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CStatistik::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatistik)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStatistik, CDialog)
	//{{AFX_MSG_MAP(CStatistik)
	ON_WM_PAINT()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_JAHR, OnDeltaposSpinJahr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatistik message handlers

BOOL CStatistik::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CTime now = now.GetCurrentTime();                           
	char buf[20];
	int jahr = now.GetYear();

	sprintf(buf, "%d", jahr);

	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_JAHR))->SetRange(1990, 2037);
	((CSpinButtonCtrl *)GetDlgItem(IDC_SPIN_JAHR))->SetPos(jahr);
	
	return TRUE;  
}

void CStatistik::OnPaint() 
{	
	int h, i, k;
	char buf[50];
	RECT rVSkala;
	RECT rHSkala;
	RECT rDisplay;
	int hStart, hStep, hCount;
	int vStart, vStep, vCount;

	CDialog::OnPaint();

	CPaintDC dcVSkala(GetDlgItem(IDC_VSKALA));
	CPaintDC dcHSkala(GetDlgItem(IDC_HSKALA));
	CPaintDC dcDisplay(GetDlgItem(IDC_DISPLAY));
		
	dcVSkala.SetBkMode(TRANSPARENT);
	dcHSkala.SetBkMode(TRANSPARENT);
	dcDisplay.SetBkMode(TRANSPARENT);

	GetDlgItem(IDC_VSKALA)->GetClientRect(&rVSkala);
	GetDlgItem(IDC_HSKALA)->GetClientRect(&rHSkala);
	GetDlgItem(IDC_DISPLAY)->GetClientRect(&rDisplay);

	int widthVSkala  = rVSkala.right  - rVSkala.left;
	int widthHSkala  = rHSkala.right  - rHSkala.left;
	int widthDisplay = rDisplay.right - rDisplay.left;

	int heightVSkala  = rVSkala.bottom  - rVSkala.top;
	int heightHSkala  = rHSkala.bottom  - rHSkala.top;
	int heightDisplay = rDisplay.bottom - rDisplay.top;

	switch (StatistikArt)
	{
		case ID_RETURN_WOCHENSTATISTIK:
			SetDlgItemText(IDC_HSKALA_TEXT, "Woche");
			hStart = 1; hStep = 3; hCount = 52;
			vStart = 0; vStep = 5; vCount = 80;
			break;
		case ID_RETURN_MONATSSTATISTIK:
			SetDlgItemText(IDC_HSKALA_TEXT, "Monat");
			hStart = 1; hStep = 1;  hCount = 12;
			vStart = 0; vStep = 20; vCount = 320;
			break;
		case ID_RETURN_JAHRESSTATISTIK:
			return;
			break;
	}
			
	// Skala der Zeitachse
	for (i = hStart; i < hCount + hStart; i += hStep)
	{
		sprintf(buf, "%d", i);
		int x = widthHSkala * (i - hStart) / hCount;
		dcHSkala.TextOut(x, 5, buf, strlen(buf));
		dcHSkala.MoveTo(x, heightHSkala - 1);
		dcHSkala.LineTo(x, heightHSkala - 5);
	}

	// Wochen-/Monatsstundenskala
	dcVSkala.SetTextAlign(TA_BASELINE);
	for (i = vStart; i < vCount + vStart; i += vStep)
	{
		sprintf(buf, "%d", i);
		int y = heightVSkala - (heightVSkala * (i - vStart) / vCount);
		dcVSkala.TextOut(5, y, buf, strlen(buf));
		dcVSkala.MoveTo(widthVSkala - 1, y);
		dcVSkala.LineTo(widthVSkala - 8, y);
	}

	// eigentliche Statistik-Grafik
	{
		static struct {
			char kuerzel;
			DWORD farbe;
		} kuerzeltab[] = {
			0,		0x00000000,
			'A',	0x00ff0000,
			'B',	0x0000ff00,
			'C',	0x000000ff,
			'D',	0x00ffff00,
			'E',	0x00ff00ff,
			'F',	0x0000ffff,
			'G',	0x00ff8000,
			'H',	0x0080ff00,
			'I',	0x0000ff80,
			'J',	0x000080ff,
			'K',	0x008000ff,
			'L',	0x00ff0080,
			'M',	0x00ffff80,
			'N',	0x00ff80ff,
			'O',	0x0080ffff,
			'P',	0x00800000,
			'Q',	0x00008000,
			'R',	0x00000080,
			'S',	0x008080ff,
			'T',	0x0080ff80,
			'U',	0x00ff8080,
			'V',	0x00808080,
			'W',	0x00404080,
			'X',	0x00804040,
			'Y',	0x00408040,
			'Z',	0x004040ff
		};

		CBrush br0;
		CPen pen1, *ppen2, *pen1Old, *pen2Old;
		br0.CreateSolidBrush(0x00ffffff);			// sattes weiß für Hintergrund
		pen1.CreatePen(PS_SOLID, 1, 0x00d04010);	// nettes blau

		// Hintergrund
		dcDisplay.FillRect(&rDisplay, &br0);

		// Rahmen
		dcDisplay.MoveTo(0, 0);
		dcDisplay.LineTo(widthDisplay, 0);
		dcDisplay.LineTo(widthDisplay, heightDisplay);
		dcDisplay.LineTo(0, heightDisplay);
		dcDisplay.LineTo(0, 0);

		// Mittellinie
		VERIFY(pen1Old = dcDisplay.SelectObject(&pen1));	
		dcDisplay.MoveTo(0, heightDisplay/2+1);
		dcDisplay.LineTo(widthDisplay, heightDisplay/2+1);
		VERIFY(pen1Old->DeleteObject());

		// Werte berechnen
		int *wert = new int[hCount];
		for (h = 0, k = 0; h < sizeof(kuerzeltab)/sizeof(kuerzeltab[0]); h++)
		{
			BOOL bDrawIt = FALSE;

			for (i = hStart; i < hCount + hStart; i += 1/*hStep*/)
			{
				long hours, minutes;
				char buffer[30], von_datum[10], bis_datum[10];

				// je nach Statistik-Art die Stunden pro Zeitraum errechnen:
				switch (StatistikArt)
				{
					case ID_RETURN_WOCHENSTATISTIK:
						{
							GetDlgItemText(IDC_JAHR, buffer, sizeof(buffer));
							CTime theYear(atol(buffer),1,1,0,0,0);
							CTimeSpan sevenDays(7, 0, 0, 0);	
							CTimeSpan sixDays(6, 0, 0, 0);	
							int j;

							for (j = hStart; j < i; j++)
								theYear += sevenDays;
							
							strcpy(von_datum, theYear.Format("%d.%m.%y"));
							theYear += sixDays;
							strcpy(bis_datum, theYear.Format("%d.%m.%y"));

							hours   = sfDaten->ColSum(21, 23, von_datum, bis_datum, kuerzeltab[h].kuerzel);
							minutes = sfDaten->ColSum(24, 26, von_datum, bis_datum, kuerzeltab[h].kuerzel);

							hours   += minutes / 60;
							minutes	 = minutes % 60;

							if (minutes >= 30) hours++;	// evtl. aufrunden!
							wert[i - hStart] = hours;
							if (hours) bDrawIt = TRUE;
						}
						break;
					case ID_RETURN_MONATSSTATISTIK:
						GetDlgItemText(IDC_JAHR, buffer, sizeof(buffer));
						sprintf(von_datum, "01.%02d.%-2.2s", i, buffer + 2);
						sprintf(bis_datum, "31.%02d.%-2.2s", i, buffer + 2);

						hours   = sfDaten->ColSum(21, 23, von_datum, bis_datum, kuerzeltab[h].kuerzel);
						minutes = sfDaten->ColSum(24, 26, von_datum, bis_datum, kuerzeltab[h].kuerzel);

						hours   += minutes / 60;
						minutes	 = minutes % 60;

						if (minutes >= 30) hours++;	// evtl. aufrunden!
						wert[i - hStart] = hours;
						if (hours) bDrawIt = TRUE;

						break;
				}
			}

			// Kurve zeichnen
			if (bDrawIt)
			{
				ppen2 = new CPen;
				ppen2->CreatePen(PS_SOLID, 3, kuerzeltab[h].farbe);	// schönes grün
				VERIFY(pen2Old = dcDisplay.SelectObject(ppen2));	
				for (i = hStart; i < hCount + hStart; i += 1/*hStep*/)
				{
					int x = widthHSkala * (i - hStart) / hCount;
					int y = heightVSkala - (heightVSkala * (wert[i - hStart] - vStart) / vCount);
			
					if (i == hStart) 
						dcDisplay.MoveTo(x, y);
					dcDisplay.LineTo(x, y);
				}
				dcDisplay.TextOut(425, k*11-25, (kuerzeltab[h].kuerzel ? &kuerzeltab[h].kuerzel : "+"), (kuerzeltab[h].kuerzel ? 1 : 1));
				dcDisplay.MoveTo(445, k*11-17);
				dcDisplay.LineTo(475, k*11-17);
				VERIFY(pen2Old->DeleteObject());
				delete ppen2;
			}
			if (bDrawIt) k++;
		}
		delete wert;
	}
}


void CStatistik::OnDeltaposSpinJahr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	InvalidateRect(NULL, FALSE);
	PostMessage(WM_PAINT);
	
	*pResult = 0;
}
