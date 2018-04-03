// ShowResult.cpp : 实现文件
//

#include "stdafx.h"
#include "MyTab.h"
#include "ShowResult.h"
#include "afxdialogex.h"
#include "ChartCtrl\ChartLineSerie.h"
#include<fstream>
#include<iostream>
#include<iomanip>
using namespace std;
// ShowResult 对话框

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
	DDX_Control(pDX, IDC_CUSTOM_RS, m_ChartCtrl1);	
}


BEGIN_MESSAGE_MAP(ShowResult, CDialogEx)
	ON_BN_CLICKED(IDOK, &ShowResult::OnBnClickedOk)
END_MESSAGE_MAP()


// ShowResult 消息处理程序


BOOL ShowResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	CChartAxis *pAxis = NULL;
	pAxis = m_ChartCtrl1.CreateStandardAxis(CChartCtrl::BottomAxis);
	pAxis->SetAutomatic(true);
	pAxis = m_ChartCtrl1.CreateStandardAxis(CChartCtrl::LeftAxis);
	pAxis->SetAutomatic(true);

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


void ShowResult::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	double x[1000], y[1000];
	int count = 0;
	ifstream fin("test.xls");
	const int LINE_LENGTH = 100;
	char str[LINE_LENGTH];
	while ((fin.getline(str, LINE_LENGTH))&&(count<1000))
	{
		x[count] = count;
		y[count] = (float)atoi(str) / 6000;
		count++;
	}


	//////////////////////////////////////////////////////////////////////////  
	//画图测试  
	//////////////////////////////////////////////////////////////////////////  
	

	CChartLineSerie *pLineSerie1;
	m_ChartCtrl1.RemoveAllSeries();//先清空  
	pLineSerie1 = m_ChartCtrl1.CreateLineSerie();
	pLineSerie1->SetSeriesOrdering(poNoOrdering);//设置为无序  
	pLineSerie1->AddPoints(x, y, 1000);
	pLineSerie1->SetName(_T("这是IDC_ChartCtrl1的第一条线"));//SetName的作用将在后面讲到  

	//////////////////////////////////////////////////////////////////////////  
	//时间轴画图  
	//////////////////////////////////////////////////////////////////////////  
	COleDateTime t1(COleDateTime::GetCurrentTime());
	COleDateTimeSpan tsp(1, 0, 0, 0);
	for (int i = 0; i<1000; i++)
	{
		x[i] = t1.m_dt;
		y[i] = sin(float(i));
		t1 += tsp;
	}

	m_ChartCtrl1.EnableRefresh(true);
	
}


