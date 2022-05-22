// TimeLogdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeLogDlg dialog

class CTimeLogDlg : public CDialog
{
// Construction
public:
	CTimeLogDlg(CWnd* pParent = NULL);	// standard constructor
	CTimeLogDlg::~CTimeLogDlg();

	char reg[100];
	BOOL shareware;
	UINT timer;
// Dialog Data
	//{{AFX_DATA(CTimeLogDlg)
	enum { IDD = IDD_TIMELOG_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeLogDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

public:
	char *liste;
	long size_of_liste;

private:
	void CTimeLogDlg::SaveListe();
	void CTimeLogDlg::UpdateGesamtsumme();
	void CTimeLogDlg::UpdateSelektiertSumme();
	void CTimeLogDlg::Reg();
	void CTimeLogDlg::SaveIt();
	void CTimeLogDlg::On_MYWM_NOTIFYICON(WPARAM wParam, LPARAM lParam);
	char *CTimeLogDlg::GetFilename();
	char *CTimeLogDlg::GetIniPath();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTimeLogDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnFocusBeschreibung();
	virtual void OnOK();
	afx_msg void OnDelete();
	afx_msg void OnBiszeit();
	afx_msg void OnErrspaceListe();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnStatistiken();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnKillfocusVon();
	afx_msg void OnKillfocusBeschreibung();
	afx_msg void OnChangeKuerzel();
	afx_msg void OnChangeKuerzel2();
	virtual void OnCancel();
	afx_msg void OnVonzeit();
	afx_msg void OnVondatum();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define MYWM_NOTIFYICON		(WM_APP+100)
#define STATUS_ICON_ID		1
