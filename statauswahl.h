// StatAuswahl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatAuswahl dialog

class CStatAuswahl : public CDialog
{
// Construction
public:
	CStatAuswahl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatAuswahl)
	enum { IDD = IDD_STATISTIK_AUSWAHL };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatAuswahl)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CStatAuswahl)
	afx_msg void OnJahresstatistik();
	afx_msg void OnMonatsstatistik();
	virtual void OnCancel();
	afx_msg void OnWochenstatistik();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// Werte für Rückgabe:
#define ID_RETURN_WOCHENSTATISTIK	1
#define ID_RETURN_MONATSSTATISTIK	2
#define ID_RETURN_JAHRESSTATISTIK	3
#define ID_RETURN_ABBRUCH			0
