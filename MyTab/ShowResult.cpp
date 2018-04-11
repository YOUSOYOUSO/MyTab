// ShowResult.cpp : 实现文件
//

#include "stdafx.h"
#include "ChartCtrl\ChartScrollBar.h"
#include "ChartCtrl\ChartCtrl.h"  
#include "ChartCtrl\ChartTitle.h"  
#include "ChartCtrl\ChartAxisLabel.h"  
#include "ChartCtrl\ChartBarSerie.h"  
#include "MyTab.h"
#include "ShowResult.h"
#include "afxdialogex.h"
#include "ChartCtrl\ChartLineSerie.h"
#include<fstream>
#include<iostream>
#include<iomanip>
#include <fstream>//fstream供给了三个类，用来实现c++对文件的操纵


using namespace std;
// ShowResult 对话框

extern int getFrameCount();
extern int getFps();
bool flagzz = 1;
bool flagzx = 1;
ShowResult * RDlg;
IMPLEMENT_DYNAMIC(ShowResult, CDialogEx)

ShowResult::ShowResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(ShowResult::IDD, pParent)
{

}

ShowResult::~ShowResult()
{

}

void ShowResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
	DDX_Control(pDX, IDC_CHARTCTRL, m_ChartCtrl2);
}


BEGIN_MESSAGE_MAP(ShowResult, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ZX, &ShowResult::OnBnClickedButtonZx)
	ON_BN_CLICKED(IDC_CHECK_ZX, &ShowResult::OnBnClickedCheckZx)
	ON_BN_CLICKED(IDC_CHECK_ZZ, &ShowResult::OnBnClickedCheckZz)
END_MESSAGE_MAP()


// ShowResult 消息处理程序


BOOL ShowResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CChartAxis *pAxis = NULL;

	pAxis = m_ChartCtrl2.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl2.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

	((CButton*)GetDlgItem(IDC_CHECK_ZZ))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_ZX))->SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

int atoi(char s[])
{
	int i;
	int n = 0;
	for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
	{
		n = 10 * n + (s[i] - '0');
	}
	return n;
}





void ShowResult::OnBnClickedButtonZx()
{
	// TODO: 在此添加控件通知处理程序代码





	///////////////////////////////////////////////////取数据

	int couuu = getFrameCount();
	int fps = getFps();

	double x[2000], y[2000];
	int count = 0;
	ifstream fin("test.xls");
	const int LINE_LENGTH = 100;
	char str[LINE_LENGTH];
	while ((fin.getline(str, LINE_LENGTH)) && (count<couuu))
	{
		y[count] = (float)atoi(str) / 60000;
		count++;
	}

	/////////////////////////////////////////////////初始化
	srand((unsigned int)time(NULL));
	// Disable the refresh  
	m_ChartCtrl2.EnableRefresh(false);
 
	m_ChartCtrl2.RemoveAllSeries();//先清空  
	
	/////////////////////////////////////////////////表格坐标轴初始化
	CChartStandardAxis* pLeftAxis =
		m_ChartCtrl2.CreateStandardAxis(CChartCtrl::LeftAxis);
	pLeftAxis->SetMinMax(0, 1);
	pLeftAxis->GetLabel()->SetText(_T("前景像素占比"));
	// Create the right axis and configure it properly  

	CChartStandardAxis* pRightAxis =
		m_ChartCtrl2.CreateStandardAxis(CChartCtrl::RightAxis);
	pRightAxis->SetVisible(false);
	pRightAxis->SetMinMax(0, 2000);

	//////////////////////////////////////////////////

	// Configure the legend  
	m_ChartCtrl2.GetLegend()->SetVisible(true);
	m_ChartCtrl2.GetLegend()->SetHorizontalMode(true);
	m_ChartCtrl2.GetLegend()->UndockLegend(80, 50);
	// Add text to the title and set the font & color  

	CChartFont titleFont;
	titleFont.SetFont(_T("Arial Black"), 120, true, false, true);
	m_ChartCtrl2.GetTitle()->SetFont(titleFont);
	m_ChartCtrl2.GetTitle()->SetColor(RGB(0, 0, 128));
	// Sets a gradient background  
	m_ChartCtrl2.SetBackGradient(RGB(255, 255, 255), RGB(150, 150, 255), gtVertical);

	// Create two bar series and a line series and populate them with data  
	CChartBarSerie* pBarSeries1 = m_ChartCtrl2.CreateBarSerie();
	CChartBarSerie* pBarSeries2 = m_ChartCtrl2.CreateBarSerie();
	CChartLineSerie* pLineSeries = m_ChartCtrl2.CreateLineSerie();
	int lowIndex = -1;
	int lowVal = 999;






	for (int i = 0; i<couuu/fps; i++)
	{	
		float avgtotal = 0.0;
		for (int j = 0; j < fps; j++) {
			
			avgtotal = avgtotal+y[i * fps + j];
		}
		avgtotal = avgtotal / fps;

	

		if (flagzz == 1) {
			if (avgtotal < 0.2) {
				pBarSeries1->AddPoint(i, avgtotal);
			}else{
				pBarSeries2->AddPoint(i, avgtotal);
			}
		}
		if (flagzx == 1) {
			pLineSeries->AddPoint(i, avgtotal);
		}

		
	}
	// 左上角图表介绍
	pBarSeries1->SetColor(RGB(255, 0, 0));
	pBarSeries1->SetName(_T("低密度像素"));
	pBarSeries1->SetBorderColor(RGB(255, 0,0));
	pBarSeries2->SetColor(RGB(68, 68, 255));
	pBarSeries2->SetGradient(RGB(200, 200, 255), gtVerticalDouble);
	pBarSeries2->SetName(_T("中高密度像素"));
	pBarSeries2->SetBorderColor(RGB(0, 0, 255));
	pBarSeries2->SetBorderWidth(3);
	pLineSeries->SetColor(RGB(0, 180, 0));
	pLineSeries->SetName(_T("前景像素占比"));
	pLineSeries->SetWidth(2);
	pLineSeries->EnableShadow(true);



	CChartAxis* pAxis = m_ChartCtrl2.GetBottomAxis();
	pAxis->EnableScrollBar(true);


	// Re enable the refresh  
	m_ChartCtrl2.EnableRefresh(true);

}


void ShowResult::OnBnClickedCheckZx()
{
	// TODO: 在此添加控件通知处理程序代码


	if (((CButton*)GetDlgItem(IDC_CHECK_ZX))->GetCheck() == 1)
		flagzx = 1;
	else
		flagzx = 0;
	OnBnClickedButtonZx();
}


void ShowResult::OnBnClickedCheckZz()
{
	// TODO: 在此添加控件通知处理程序代码	
	if (((CButton*)GetDlgItem(IDC_CHECK_ZZ))->GetCheck() == 1)
		flagzz = 1;
	else
		flagzz = 0;

	OnBnClickedButtonZx();
}


