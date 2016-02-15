// MainWindowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddinDemo.h"
#include "MainWindowDlg.h"
#include "math.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define MAX_LENGTH 20
#define TIMER_ID_PROTECT_SYSTEM 1  
//#define TIMER_TIME_PROTECT_SYSTEM  1000*60*60  
#define TIMER_TIME_PROTECT_SYSTEM  500  
/////////////////////////////////////////////////////////////////////////////
// CMainWindowDlg dialog


CMainWindowDlg::CMainWindowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMainWindowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMainWindowDlg)
	m_iDirection = 0;
	m_iOffSet = 0;
	m_iVolume = 1;
	m_fPrice = 56320;
	m_iPriceType = 0;
	m_bHedge = FALSE;
	m_strInstrumentID = _T("SQCU01");
	m_iOrderActionID = 0;
	//}}AFX_DATA_INIT
	m_bInit = TRUE;

	for(int i=0;i<21;i++)
	{
		m_oldValS[i]=0;
		m_oldVal[i]="";
	}

	GetPrivateProfileString("AddinDemo","SELF1","",m_oldVal[0].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","SELF2","",m_oldVal[1].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","SELF3","",m_oldVal[2].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	
	GetPrivateProfileString("AddinDemo","G1GOU","",m_oldVal[3].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G1GU","",m_oldVal[4].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G1QI","",m_oldVal[5].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	
	GetPrivateProfileString("AddinDemo","G2GOU","",m_oldVal[6].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G2GU","",m_oldVal[7].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G2QI","",m_oldVal[8].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	
	GetPrivateProfileString("AddinDemo","G3GOU","",m_oldVal[9].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G3GU","",m_oldVal[10].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G3QI","",m_oldVal[11].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	
	GetPrivateProfileString("AddinDemo","G4GOU","",m_oldVal[12].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G4GU","",m_oldVal[13].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G4QI","",m_oldVal[14].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	
	GetPrivateProfileString("AddinDemo","G5GOU","",m_oldVal[15].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G5GU","",m_oldVal[16].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G5QI","",m_oldVal[17].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	
	GetPrivateProfileString("AddinDemo","G6GOU","",m_oldVal[18].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G6GU","",m_oldVal[19].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	GetPrivateProfileString("AddinDemo","G6QI","",m_oldVal[20].GetBuffer(MAX_LENGTH),MAX_LENGTH,"C:\\StockCfg.ini"); 
	
}


void CMainWindowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainWindowDlg)
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMainWindowDlg, CDialog)
	//{{AFX_MSG_MAP(CMainWindowDlg)
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_NOTIFY_UPDATE, OnNotifyUpdate)
	ON_EN_KILLFOCUS(IDC_EDIT_SELF1, &CMainWindowDlg::OnEnKillfocusEditSelf1)
	ON_EN_KILLFOCUS(IDC_EDIT_SELF2, &CMainWindowDlg::OnEnKillfocusEditSelf2)
	ON_EN_KILLFOCUS(IDC_EDIT_SELF3, &CMainWindowDlg::OnEnKillfocusEditSelf3)

	ON_EN_KILLFOCUS(IDC_EDIT_G1_GOU, &CMainWindowDlg::OnEnKillfocusEditG1Gou)
	ON_EN_KILLFOCUS(IDC_EDIT_G1_GU, &CMainWindowDlg::OnEnKillfocusEditG1Gu)
	ON_EN_KILLFOCUS(IDC_EDIT_G1_QI, &CMainWindowDlg::OnEnKillfocusEditG1Qi)

	ON_EN_KILLFOCUS(IDC_EDIT_G2_GOU, &CMainWindowDlg::OnEnKillfocusEditG2Gou)
	ON_EN_KILLFOCUS(IDC_EDIT_G2_GU, &CMainWindowDlg::OnEnKillfocusEditG2Gu)
	ON_EN_KILLFOCUS(IDC_EDIT_G2_QI, &CMainWindowDlg::OnEnKillfocusEditG2Qi)

	ON_EN_KILLFOCUS(IDC_EDIT_G3_GOU, &CMainWindowDlg::OnEnKillfocusEditG3Gou)
	ON_EN_KILLFOCUS(IDC_EDIT_G3_GU, &CMainWindowDlg::OnEnKillfocusEditG3Gu)
	ON_EN_KILLFOCUS(IDC_EDIT_G3_QI, &CMainWindowDlg::OnEnKillfocusEditG3Qi)

	ON_EN_KILLFOCUS(IDC_EDIT_G4_GOU, &CMainWindowDlg::OnEnKillfocusEditG4Gou)
	ON_EN_KILLFOCUS(IDC_EDIT_G4_GU, &CMainWindowDlg::OnEnKillfocusEditG4Gu)
	ON_EN_KILLFOCUS(IDC_EDIT_G4_QI, &CMainWindowDlg::OnEnKillfocusEditG4Qi)

	ON_EN_KILLFOCUS(IDC_EDIT_G5_GOU, &CMainWindowDlg::OnEnKillfocusEditG5Gou)
	ON_EN_KILLFOCUS(IDC_EDIT_G5_GU, &CMainWindowDlg::OnEnKillfocusEditG5Gu)
	ON_EN_KILLFOCUS(IDC_EDIT_G5_QI, &CMainWindowDlg::OnEnKillfocusEditG5Qi)

	ON_EN_KILLFOCUS(IDC_EDIT_G6_GOU, &CMainWindowDlg::OnEnKillfocusEditG6Gou)
	ON_EN_KILLFOCUS(IDC_EDIT_G6_GU, &CMainWindowDlg::OnEnKillfocusEditG6Gu)
	ON_EN_KILLFOCUS(IDC_EDIT_G6_QI, &CMainWindowDlg::OnEnKillfocusEditG6Qi)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainWindowDlg message handlers

BOOL CMainWindowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//去除任务栏窗口对应按钮
	ModifyStyleEx (WS_EX_APPWINDOW,WS_EX_TOOLWINDOW );
	
	//记录状态
	WritePrivateProfileInt("AddinDemo","AutoShow",   
		1,"C:\\StockCfg.ini");  

	//注册沪铜行情数据
	//g_pMainFormework->RegReportNotify("IH03",'JZ');
	//g_pMainFormework->RegReportNotify("IH02",'JZ');

	//注册上证指数行情数据
	//g_pMainFormework->RegReportNotify("000001",'HS');
	
	//注册期权行情数据
	/*g_pMainFormework->RegReportNotify("10000522",'QQ');
	g_pMainFormework->RegReportNotify("10000520",'QQ');
	g_pMainFormework->RegReportNotify("10000527",'QQ');
	g_pMainFormework->RegReportNotify("10000528",'QQ');
*/
	GetDlgItem(IDC_EDIT_SELF1)->SetWindowText(m_oldVal[0]);
	GetDlgItem(IDC_EDIT_SELF2)->SetWindowText(m_oldVal[1]);
	GetDlgItem(IDC_EDIT_SELF3)->SetWindowText(m_oldVal[2]);

	GetDlgItem(IDC_EDIT_G1_GOU)->SetWindowText(m_oldVal[3]);
	GetDlgItem(IDC_EDIT_G1_GU)->SetWindowText(m_oldVal[4]);
	GetDlgItem(IDC_EDIT_G1_QI)->SetWindowText(m_oldVal[5]);
	
	GetDlgItem(IDC_EDIT_G2_GOU)->SetWindowText(m_oldVal[6]);
	GetDlgItem(IDC_EDIT_G2_GU)->SetWindowText(m_oldVal[7]);
	GetDlgItem(IDC_EDIT_G2_QI)->SetWindowText(m_oldVal[8]);
	
	GetDlgItem(IDC_EDIT_G3_GOU)->SetWindowText(m_oldVal[9]);
	GetDlgItem(IDC_EDIT_G3_GU)->SetWindowText(m_oldVal[10]);
	GetDlgItem(IDC_EDIT_G3_QI)->SetWindowText(m_oldVal[11]);
	
	GetDlgItem(IDC_EDIT_G4_GOU)->SetWindowText(m_oldVal[12]);
	GetDlgItem(IDC_EDIT_G4_GU)->SetWindowText(m_oldVal[13]);
	GetDlgItem(IDC_EDIT_G4_QI)->SetWindowText(m_oldVal[14]);
	
	GetDlgItem(IDC_EDIT_G5_GOU)->SetWindowText(m_oldVal[15]);
	GetDlgItem(IDC_EDIT_G5_GU)->SetWindowText(m_oldVal[16]);
	GetDlgItem(IDC_EDIT_G5_QI)->SetWindowText(m_oldVal[17]);
	
	GetDlgItem(IDC_EDIT_G6_GOU)->SetWindowText(m_oldVal[18]);
	GetDlgItem(IDC_EDIT_G6_GU)->SetWindowText(m_oldVal[19]);
	GetDlgItem(IDC_EDIT_G6_QI)->SetWindowText(m_oldVal[20]);
//////////////////////////////////////////////////////////
	GetDlgItem(IDC_EDIT_SELF1)->SetFocus();
	GetDlgItem(IDC_EDIT_SELF2)->SetFocus();
	GetDlgItem(IDC_EDIT_SELF3)->SetFocus();

	GetDlgItem(IDC_EDIT_G1_GOU)->SetFocus();
	GetDlgItem(IDC_EDIT_G1_GU)->SetFocus();
	GetDlgItem(IDC_EDIT_G1_QI)->SetFocus();
	
	GetDlgItem(IDC_EDIT_G2_GOU)->SetFocus();
	GetDlgItem(IDC_EDIT_G2_GU)->SetFocus();
	GetDlgItem(IDC_EDIT_G2_QI)->SetFocus();
	
	GetDlgItem(IDC_EDIT_G3_GOU)->SetFocus();
	GetDlgItem(IDC_EDIT_G3_GU)->SetFocus();
	GetDlgItem(IDC_EDIT_G3_QI)->SetFocus();
	
	GetDlgItem(IDC_EDIT_G4_GOU)->SetFocus();
	GetDlgItem(IDC_EDIT_G4_GU)->SetFocus();
	GetDlgItem(IDC_EDIT_G4_QI)->SetFocus();
	
	GetDlgItem(IDC_EDIT_G5_GOU)->SetFocus();
	GetDlgItem(IDC_EDIT_G5_GU)->SetFocus();
	GetDlgItem(IDC_EDIT_G5_QI)->SetFocus();
	
	GetDlgItem(IDC_EDIT_G6_GOU)->SetFocus();
	GetDlgItem(IDC_EDIT_G6_GU)->SetFocus();
	GetDlgItem(IDC_EDIT_G6_QI)->SetFocus();
	GetDlgItem(IDC_EDIT_G6_GU)->SetFocus();

	SetTimer(TIMER_ID_PROTECT_SYSTEM,TIMER_TIME_PROTECT_SYSTEM,NULL);  


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMainWindowDlg::PostNcDestroy() 
{
	CDialog::PostNcDestroy();
	g_pdlgMainWindow = NULL;
	delete this;
}

void CMainWindowDlg::OnMove(int x, int y) 
{
	CDialog::OnMove(x, y);
	
	//防止调用MoveWindow函数时系统发送此消息
	if(m_bInit)
		return;
	
	CRect rc;
	GetWindowRect(rc);
				
	WritePrivateProfileInt("AddinDemo","X",   
		rc.left,"C:\\StockCfg.ini");  
	WritePrivateProfileInt("AddinDemo","Y",   
		rc.top,"C:\\StockCfg.ini");  
}

void CMainWindowDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting


	
}

void CMainWindowDlg::OnCancel() 
{	
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[0],'HS');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[1],'HS');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[2],'HS');
	
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[3],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[4],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[5],'JZ');

	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[6],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[7],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[8],'JZ');

	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[9],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[10],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[11],'JZ');

    g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[12],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[13],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[14],'JZ');

    g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[15],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[16],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[17],'JZ');

	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[18],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[19],'QQ');
	g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)m_oldVal[20],'JZ');

	DestroyWindow();
}

void CMainWindowDlg::WriteCfg()
{
	WritePrivateProfileInt("AddinDemo","AutoShow",0,"C:\\StockCfg.ini"); 

	WritePrivateProfileString("AddinDemo","SELF1",m_oldVal[0],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","SELF2",m_oldVal[1],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","SELF3",m_oldVal[2],"C:\\StockCfg.ini"); 
	
	WritePrivateProfileString("AddinDemo","G1GOU",m_oldVal[3],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G1GU",m_oldVal[4],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G1QI",m_oldVal[5],"C:\\StockCfg.ini"); 
	
	WritePrivateProfileString("AddinDemo","G2GOU",m_oldVal[6],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G2GU",m_oldVal[7],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G2QI",m_oldVal[8],"C:\\StockCfg.ini"); 
	
	WritePrivateProfileString("AddinDemo","G3GOU",m_oldVal[9],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G3GU",m_oldVal[10],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G3QI",m_oldVal[11],"C:\\StockCfg.ini"); 
	
	WritePrivateProfileString("AddinDemo","G4GOU",m_oldVal[12],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G4GU",m_oldVal[13],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G4QI",m_oldVal[14],"C:\\StockCfg.ini"); 
	
	WritePrivateProfileString("AddinDemo","G5GOU",m_oldVal[15],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G5GU",m_oldVal[16],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G5QI",m_oldVal[17],"C:\\StockCfg.ini"); 
	
	WritePrivateProfileString("AddinDemo","G6GOU",m_oldVal[18],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G6GU",m_oldVal[19],"C:\\StockCfg.ini"); 
	WritePrivateProfileString("AddinDemo","G6QI",m_oldVal[20],"C:\\StockCfg.ini"); 
}

void CMainWindowDlg::OnClose() 
{
	WriteCfg();
	KillTimer(TIMER_ID_PROTECT_SYSTEM); 
	OnCancel();
}
//接收通知消息
LRESULT CMainWindowDlg::OnNotifyUpdate(WPARAM w,LPARAM l)
{
	if(w == 2)
	{
		ReportUpdate(l);
	}
	else if(w == 3)
	{
		BARGAIN_NOTIFY_KSI * pKsi = (BARGAIN_NOTIFY_KSI*)l;
		//OrderStatus(pKsi);
	}
	else if(w == 4)
	{
		BARGAIN_NOTIFY_KSI * pKsi = (BARGAIN_NOTIFY_KSI*)l;
		if(strcmp(pKsi->m_szStatus,"Connected") == 0)
		{
			//账户已经连接
		}
		else if(strcmp(pKsi->m_szStatus,"Disconnected") == 0)
		{
			//账户断开连接
		}
	}
	return 0;
}


void CMainWindowDlg::WriteLog(CString strLog)
{
	COleDateTime timeNow = COleDateTime::GetCurrentTime();
	m_strInfo += timeNow.Format("%Y.%m.%d %H:%M:%S") + " ";
	m_strInfo += strLog;
	m_strInfo += "\r\n";
	
	m_editMsg.SetWindowText(m_strInfo);
	m_editMsg.SetSel(m_strInfo.GetLength(),m_strInfo.GetLength());
}

BOOL CMainWindowDlg::ChangeNotify(CString oldVal, CString newVal,WORD macket)
{
	if(oldVal != "")
	{
		 g_pMainFormework->UnRegReportNotify((LPSTR)(LPCTSTR)oldVal,macket);
	}

	if(newVal!="")
	{
		if (g_pMainFormework->RegReportNotify((LPSTR)(LPCTSTR)newVal,macket))
		{
			return true;

		}else
		{
			return false;
		}
	}
	return false;	
}

void CMainWindowDlg::SetInfomation(REPORT_STRUCT * pData,int infoid,int resultid,int groupid)
{
	CString strText;
	strText.Format("注册品种: %s |申买价 %.4f |买量 %.4f |申卖价 %.4f |卖量 %.4f |", pData->m_szName, pData->m_fBuyPrice[0],pData->m_fBuyVolume[0],pData->m_fSellPrice[0],pData->m_fSellVolume[0]);
	GetDlgItem(infoid)->SetWindowText(strText);
	if(groupid > -1)
	{
		strText.Format("多头   %.4f \n空头 - %.4f\n----------------\n       %.4f",m_qiVal[groupid], (m_quanVal[groupid]-1000*m_guVal[groupid]+1000*m_gouVal[groupid]),m_qiVal[groupid]-(m_quanVal[groupid]-1000*m_guVal[groupid]+1000*m_gouVal[groupid]));
		GetDlgItem(resultid)->SetWindowText(strText);
	}
}
float CMainWindowDlg::FindQiQuanVal(char *szName)
{
	CString str(szName);
	float val = atof(str.Right(4));
	return val;
}
void CMainWindowDlg::ReportUpdate(LPARAM l)
{
	REPORT_STRUCT * pData = (REPORT_STRUCT*)l;
	ReportInfoUpdate(pData);
}
void CMainWindowDlg::ReportInfoUpdate(REPORT_STRUCT* pData)
{
	//显示处理报表 pData->m_fNewPrice ....
	CString strTextName;
	CString strText,str;
	strTextName.Format("%s",pData->m_szLabel);

	GetDlgItemText(IDC_EDIT_SELF1, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		SetInfomation(pData,IDC_STATIC_TEXT_SELF1,0,-1);
	}

	GetDlgItemText(IDC_EDIT_SELF2, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		SetInfomation(pData,IDC_STATIC_TEXT_SELF2,0,-1);
	}

	GetDlgItemText(IDC_EDIT_SELF3, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		SetInfomation(pData,IDC_STATIC_TEXT_SELF3,0,-1);
	}
	//Goup1
	GetDlgItemText(IDC_EDIT_G1_GOU, str);
	CString tmstr(pData->m_szName);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("购")>0)
	{
		m_gouVal[0] = pData->m_fSellPrice[0];
		m_quanVal[0] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G1_GOU,IDC_STATIC_TEXT_RESULT1,0);
	}

	GetDlgItemText(IDC_EDIT_G1_GU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("沽")>0)
	{
		m_guVal[0] = pData->m_fBuyPrice[0];
		m_quanVal[0] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G1_GU,IDC_STATIC_TEXT_RESULT1,0);
	}

	GetDlgItemText(IDC_EDIT_G1_QI, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		m_qiVal[0] = pData->m_fBuyPrice[0];
		SetInfomation(pData,IDC_STATIC_TEXT_G1_QI,IDC_STATIC_TEXT_RESULT1,0);
	}
	//Goup2
	GetDlgItemText(IDC_EDIT_G2_GOU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("购")>0)
	{
		m_gouVal[1] = pData->m_fSellPrice[0];
		m_quanVal[1] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G2_GOU,IDC_STATIC_TEXT_RESULT2,1);
	}
	
	GetDlgItemText(IDC_EDIT_G2_GU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("沽")>0)
	{
		m_guVal[1] = pData->m_fBuyPrice[0];
		m_quanVal[1] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G2_GU,IDC_STATIC_TEXT_RESULT2,1);
	}

	GetDlgItemText(IDC_EDIT_G2_QI, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		m_qiVal[1] = pData->m_fBuyPrice[0];
		SetInfomation(pData,IDC_STATIC_TEXT_G2_QI,IDC_STATIC_TEXT_RESULT2,1);
	}
	//Goup3
	GetDlgItemText(IDC_EDIT_G3_GOU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("购")>0)
	{
		m_gouVal[2] = pData->m_fSellPrice[0];
		m_quanVal[2] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G3_GOU,IDC_STATIC_TEXT_RESULT3,2);
	}

	GetDlgItemText(IDC_EDIT_G3_GU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("沽")>0)
	{
		m_guVal[2] = pData->m_fBuyPrice[0];
		m_quanVal[2] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G3_GU,IDC_STATIC_TEXT_RESULT3,2);
	}

	GetDlgItemText(IDC_EDIT_G3_QI, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		m_qiVal[2] = pData->m_fBuyPrice[0];
		SetInfomation(pData,IDC_STATIC_TEXT_G3_QI,IDC_STATIC_TEXT_RESULT3,2);
	}
	//Goup4
	GetDlgItemText(IDC_EDIT_G4_GOU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("购")>0)
	{
		m_gouVal[3] = pData->m_fSellPrice[0];
		m_quanVal[3] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G4_GOU,IDC_STATIC_TEXT_RESULT4,3);
	}

	GetDlgItemText(IDC_EDIT_G4_GU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("沽")>0)
	{
		m_guVal[3] = pData->m_fBuyPrice[0];
		m_quanVal[3] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G4_GU,IDC_STATIC_TEXT_RESULT4,3);
	}

	GetDlgItemText(IDC_EDIT_G4_QI, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		m_qiVal[3] = pData->m_fBuyPrice[0];
		SetInfomation(pData,IDC_STATIC_TEXT_G4_QI,IDC_STATIC_TEXT_RESULT4,3);
	}
	//Goup5
	GetDlgItemText(IDC_EDIT_G5_GOU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("购")>0)
	{
		m_gouVal[4] = pData->m_fSellPrice[0];
		m_quanVal[4] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G5_GOU,IDC_STATIC_TEXT_RESULT5,4);
	}

	GetDlgItemText(IDC_EDIT_G5_GU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("沽")>0)
	{
		m_guVal[4] = pData->m_fBuyPrice[0];
		m_quanVal[4] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G5_GU,IDC_STATIC_TEXT_RESULT5,4);
	}

	GetDlgItemText(IDC_EDIT_G5_QI, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		m_qiVal[4] = pData->m_fBuyPrice[0];
		SetInfomation(pData,IDC_STATIC_TEXT_G5_QI,IDC_STATIC_TEXT_RESULT5,4);
	}
	//Goup6
	GetDlgItemText(IDC_EDIT_G6_GOU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("购")>0)
	{
		m_gouVal[5] = pData->m_fSellPrice[0];
		m_quanVal[5] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G6_GOU,IDC_STATIC_TEXT_RESULT6,5);
	}

	GetDlgItemText(IDC_EDIT_G6_GU, str);
	if(strTextName.CompareNoCase(str)==0 && tmstr.Find("沽")>0)
	{
		m_guVal[5] = pData->m_fBuyPrice[0];
		m_quanVal[5] = FindQiQuanVal(pData->m_szName);
		SetInfomation(pData,IDC_STATIC_TEXT_G6_GU,IDC_STATIC_TEXT_RESULT6,5);
	}

	GetDlgItemText(IDC_EDIT_G6_QI, str);
	if(strTextName.CompareNoCase(str)==0)
	{
		m_qiVal[5] = pData->m_fBuyPrice[0];
		SetInfomation(pData,IDC_STATIC_TEXT_G6_QI,IDC_STATIC_TEXT_RESULT6,5);
	}

	
	
}

/*****************************************************
 *Gu Piao-------------0
 *****************************************************/
void CMainWindowDlg::OnEnKillfocusEditSelf1()
{	
	CString oldVal = m_oldVal[0],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_SELF1, str);
	newVal = str.Trim();
	m_oldVal[0] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'HS'))
		{
			GetDlgItem(IDC_STATIC_TEXT_SELF1)->SetWindowText("注册成功！");
			m_oldVal[0] = newVal;
			m_oldValS[0] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'HS');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[0] = newVal;
			m_oldValS[0] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_SELF1)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditSelf2()
{	
	CString oldVal = m_oldVal[1],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_SELF2, str);
	newVal = str.Trim();
	m_oldVal[1] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'HS'))
		{
			GetDlgItem(IDC_STATIC_TEXT_SELF2)->SetWindowText("注册成功！");
			m_oldVal[1] = newVal;
			m_oldValS[1] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'HS');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[1] = newVal;
			m_oldValS[1] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_SELF2)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditSelf3()
{	
	CString oldVal = m_oldVal[2],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_SELF3, str);
	newVal = str.Trim();
	m_oldVal[2] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'HS'))
		{
			GetDlgItem(IDC_STATIC_TEXT_SELF3)->SetWindowText("注册成功！");
			m_oldVal[2] = newVal;
			m_oldValS[2] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'HS');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[2] = newVal;
			m_oldValS[2] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_SELF3)->SetWindowText("注册失败！");
		}
	}	
}

/*****************************************************
 *Group-------------1
 *****************************************************/
void CMainWindowDlg::OnEnKillfocusEditG1Gou()
{
	CString oldVal = m_oldVal[3],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G1_GOU, str);
	newVal = str.Trim();
	m_oldVal[3] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G1_GOU)->SetWindowText("注册成功！");
			m_oldVal[3] = newVal;
			m_oldValS[3] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[3] = newVal;
			m_oldValS[3] = 1;
			GetDlgItem(IDC_STATIC_TEXT_G1_GOU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG1Gu()
{
	CString oldVal = m_oldVal[4],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G1_GU, str);
	newVal = str.Trim();
	m_oldVal[4] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G1_GU)->SetWindowText("注册成功！");
			m_oldVal[4] = newVal;
			m_oldValS[4] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[4] = newVal;
			m_oldValS[4] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G1_GU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG1Qi()
{
	CString oldVal = m_oldVal[5],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G1_QI, str);
	newVal = str.Trim();
	//ChangeNotify(oldVal,newVal,'JZ');	
	m_oldVal[5] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'JZ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G1_QI)->SetWindowText("注册成功！");
			m_oldVal[5] = newVal;
			m_oldValS[5] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'JZ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[5] = newVal;
			m_oldValS[5] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G1_QI)->SetWindowText("注册失败！");
		}
	}
}

/*****************************************************
 *Group-------------2
 *****************************************************/
void CMainWindowDlg::OnEnKillfocusEditG2Gou()
{
	CString oldVal = m_oldVal[6],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G2_GOU, str);
	newVal = str.Trim();
	m_oldVal[6] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G2_GOU)->SetWindowText("注册成功！");
			m_oldVal[6] = newVal;
			m_oldValS[6] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[6] = newVal;
			m_oldValS[6] = 1;

			GetDlgItem(IDC_STATIC_TEXT_G2_GOU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG2Gu()
{
	CString oldVal = m_oldVal[7],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G2_GU, str);
	newVal = str.Trim();
	m_oldVal[7] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G2_GU)->SetWindowText("注册成功！");
			m_oldVal[7] = newVal;
			m_oldValS[7] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[7] = newVal;
			m_oldValS[7] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G2_GU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG2Qi()
{
	CString oldVal = m_oldVal[8],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G2_QI, str);
	newVal = str.Trim();
	//ChangeNotify(oldVal,newVal,'JZ');	
	m_oldVal[8] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'JZ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G2_QI)->SetWindowText("注册成功！");
			m_oldVal[8] = newVal;
			m_oldValS[8] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'JZ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[8] = newVal;
			m_oldValS[8] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G2_QI)->SetWindowText("注册失败！");
		}
	}
}

/*****************************************************
 *Group-------------3
 *****************************************************/
void CMainWindowDlg::OnEnKillfocusEditG3Gou()
{
	CString oldVal = m_oldVal[9],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G3_GOU, str);
	newVal = str.Trim();
	m_oldVal[9] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G3_GOU)->SetWindowText("注册成功！");
			m_oldVal[9]=newVal;
			m_oldValS[9]=0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[9]=newVal;
			m_oldValS[9]=1;
			
			GetDlgItem(IDC_STATIC_TEXT_G3_GOU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG3Gu()
{
	CString oldVal = m_oldVal[10],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G3_GU, str);
	newVal = str.Trim();
	m_oldVal[10] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G3_GU)->SetWindowText("注册成功！");
			m_oldVal[10] = newVal;
			m_oldValS[10] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[10] = newVal;
			m_oldValS[10] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G3_GU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG3Qi()
{
	CString oldVal = m_oldVal[11],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G3_QI, str);
	newVal = str.Trim();
	//ChangeNotify(oldVal,newVal,'JZ');	
	m_oldVal[11] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'JZ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G3_QI)->SetWindowText("注册成功！");
			m_oldVal[11] = newVal;
			m_oldValS[11] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'JZ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[11] = newVal;
			m_oldValS[11] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G3_QI)->SetWindowText("注册失败！");
		}
	}
}

/*****************************************************
 *Group-------------4
 *****************************************************/
void CMainWindowDlg::OnEnKillfocusEditG4Gou()
{
	CString oldVal = m_oldVal[12],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G4_GOU, str);
	newVal = str.Trim();
	m_oldVal[12] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G4_GOU)->SetWindowText("注册成功！");
			m_oldVal[12] = newVal;
			m_oldValS[12] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[12] = newVal;
			m_oldValS[12] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G4_GOU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG4Gu()
{
	CString oldVal = m_oldVal[13],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G4_GU, str);
	newVal = str.Trim();
	m_oldVal[13] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G4_GU)->SetWindowText("注册成功！");
			m_oldVal[13] = newVal;
			m_oldValS[13] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[13] = newVal;
			m_oldValS[13] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G4_GU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG4Qi()
{
	CString oldVal = m_oldVal[14],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G4_QI, str);
	newVal = str.Trim();
	//ChangeNotify(oldVal,newVal,'JZ');	
	m_oldVal[14] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'JZ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G4_QI)->SetWindowText("注册成功！");
			m_oldVal[14] = newVal;
			m_oldValS[14] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'JZ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[14] = newVal;
			m_oldValS[14] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G4_QI)->SetWindowText("注册失败！");
		}
	}
}

/*****************************************************
 *Group-------------5
 *****************************************************/
void CMainWindowDlg::OnEnKillfocusEditG5Gou()
{
	CString oldVal = m_oldVal[15],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G5_GOU, str);
	newVal = str.Trim();
	m_oldVal[15]="";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G5_GOU)->SetWindowText("注册成功！");
			m_oldVal[15] = newVal;
			m_oldValS[15] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[15] = newVal;
			m_oldValS[15] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G5_GOU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG5Gu()
{
	CString oldVal = m_oldVal[16],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G5_GU, str);
	newVal = str.Trim();
	m_oldVal[16] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G5_GU)->SetWindowText("注册成功！");
			m_oldVal[16] = newVal;
			m_oldValS[16] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[16] = newVal;
			m_oldValS[16] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G5_GU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG5Qi()
{
	CString oldVal = m_oldVal[17],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G5_QI, str);
	newVal = str.Trim();
	//ChangeNotify(oldVal,newVal,'JZ');	
	m_oldVal[17] = "";
	//AfxMessageBox(newVal);
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'JZ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G5_QI)->SetWindowText("注册成功！");
			m_oldVal[17] = newVal;
			m_oldValS[17] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'JZ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[17] = newVal;
			m_oldValS[17] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G5_QI)->SetWindowText("注册失败！");
		}
	}
}

/*****************************************************
 *Group-------------6
 *****************************************************/
void CMainWindowDlg::OnEnKillfocusEditG6Gou()
{
	CString oldVal = m_oldVal[18],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G6_GOU, str);
	newVal = str.Trim();
	m_oldVal[18] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G6_GOU)->SetWindowText("注册成功！");
			m_oldVal[18] = newVal;
			m_oldValS[18] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[18] = newVal;
			m_oldValS[18] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G6_GOU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG6Gu()
{
	CString oldVal = m_oldVal[19],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G6_GU, str);
	newVal = str.Trim();
	m_oldVal[19] = "";
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'QQ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G6_GU)->SetWindowText("注册成功！");
			m_oldVal[19] = newVal;
			m_oldValS[19] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'QQ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[19] = newVal;
			m_oldValS[19] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G6_GU)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnEnKillfocusEditG6Qi()
{
	CString oldVal = m_oldVal[20],newVal = "",str = "";
	GetDlgItemText(IDC_EDIT_G6_QI, str);
	newVal = str.Trim();
	m_oldVal[20] = "";
	//ChangeNotify(oldVal,newVal,'JZ');	
	if(newVal!="" || oldVal !="")
	{
		if(ChangeNotify(oldVal,newVal,'JZ'))
		{
			GetDlgItem(IDC_STATIC_TEXT_G6_QI)->SetWindowText("注册成功！");
			m_oldVal[20] = newVal;
			m_oldValS[20] = 0;
			//显示出及时报价
			REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)newVal,'JZ');
			if(pReport) 
			{
				ReportInfoUpdate(pReport);
			}
		}
		else
		{
			m_oldVal[20] = newVal;
			m_oldValS[20] = 1;
			
			GetDlgItem(IDC_STATIC_TEXT_G6_QI)->SetWindowText("注册失败！");
		}
	}
}
void CMainWindowDlg::OnTimer(UINT_PTR nIDEvent)  
{  
    // TODO: 在此添加消息处理程序代码和/或调用默认值  
    CString sTimer;  
    //  AfxMessageBox("aaaaaaaaaaa");
    switch(nIDEvent)  
    {  
    case TIMER_ID_PROTECT_SYSTEM:  
        for (int i=0;i<21;i++)
		{
			if(m_oldValS[i]==1  && m_oldVal[i]!="")
			{
				//显示出及时报价
				WORD wMarket = 'QQ';
				if(i<3)
					wMarket = 'HS';
				else if(i==5 || i==8 || i==11 || i==14 || i==17 || i== 20)
					wMarket = 'JZ';
				REPORT_STRUCT * pReport = g_pMainFormework->GetReportData((LPSTR)(LPCTSTR)m_oldVal[i],wMarket);
				if(pReport) 
				{
					ReportInfoUpdate(pReport);
				}
			}
		}
        break;  
  
    default:  
        break;  
    }  
    CDialog::OnTimer(nIDEvent);  
}  
