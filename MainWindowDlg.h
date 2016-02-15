#if !defined(AFX_MAINWINDOWDLG_H__89C0900D_24C6_435C_BC1A_073CB5B95BCE__INCLUDED_)
#define AFX_MAINWINDOWDLG_H__89C0900D_24C6_435C_BC1A_073CB5B95BCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainWindowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainWindowDlg dialog
#define	 WM_NOTIFY_UPDATE	WM_APP + 1
#include "AddinInterface.h"

class CMainWindowDlg : public CDialog
{
// Construction
public:
	void WriteLog(CString strLog);
	BOOL ChangeNotify(CString oldVal, CString newVal,WORD macket);
	CMainWindowDlg(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CMainWindowDlg)
	enum { IDD = IDD_DIALOG_MAIN_WINDOW };
	CEdit	m_editMsg;
	int		m_iDirection;
	int		m_iOffSet;
	int		m_iVolume;
	float	m_fPrice;
	int		m_iPriceType;
	BOOL	m_bHedge;
	CString	m_strInstrumentID;
	int		m_iOrderActionID;
	CString	m_oldVal[21];
	int		m_oldValS[21];
	
	float	m_quanVal[6];
	float	m_gouVal[6];
	float	m_guVal[6];
	float	m_qiVal[6];
	//}}AFX_DATA

	BOOL m_bInit;

	void ReportUpdate(LPARAM l);
	void OrderStatus(BARGAIN_NOTIFY_KSI * pKsi);
	void SetInfomation(REPORT_STRUCT * pData,int infoid,int resultid,int groupid);
	void ReportInfoUpdate(REPORT_STRUCT* pData);
	float FindQiQuanVal(char *szName);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWindowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL
	
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMainWindowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	void WriteCfg();
	//}}AFX_MSG
	afx_msg LRESULT OnNotifyUpdate(WPARAM w,LPARAM l);
	DECLARE_MESSAGE_MAP()


private:
	CString m_strInfo;
public:
	afx_msg void OnEnKillfocusEditSelf1();
	afx_msg void OnEnKillfocusEditSelf2();
	afx_msg void OnEnKillfocusEditSelf3();

	afx_msg void OnEnKillfocusEditG1Gou();
	afx_msg void OnEnKillfocusEditG1Gu();
	afx_msg void OnEnKillfocusEditG1Qi();
	
	afx_msg void OnEnKillfocusEditG2Gou();
	afx_msg void OnEnKillfocusEditG2Gu();
	afx_msg void OnEnKillfocusEditG2Qi();
	
	afx_msg void OnEnKillfocusEditG3Gou();
	afx_msg void OnEnKillfocusEditG3Gu();
	afx_msg void OnEnKillfocusEditG3Qi();
	
	afx_msg void OnEnKillfocusEditG4Gou();
	afx_msg void OnEnKillfocusEditG4Gu();
	afx_msg void OnEnKillfocusEditG4Qi();
	
	afx_msg void OnEnKillfocusEditG5Gou();
	afx_msg void OnEnKillfocusEditG5Gu();
	afx_msg void OnEnKillfocusEditG5Qi();
	
	afx_msg void OnEnKillfocusEditG6Gou();
	afx_msg void OnEnKillfocusEditG6Gu();
	afx_msg void OnEnKillfocusEditG6Qi();
	
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINWINDOWDLG_H__89C0900D_24C6_435C_BC1A_073CB5B95BCE__INCLUDED_)
