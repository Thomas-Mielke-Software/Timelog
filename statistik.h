// Statistik.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStatistik dialog

class CStatistik : public CDialog
{
// Construction
public:
	CStatistik(CWnd* pParent, int art, StreamFormat *sf);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CStatistik)
	enum { IDD = IDD_STATISKTIK };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatistik)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	int StatistikArt;
	StreamFormat *sfDaten;

	// Generated message map functions
	//{{AFX_MSG(CStatistik)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDeltaposSpinJahr(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
