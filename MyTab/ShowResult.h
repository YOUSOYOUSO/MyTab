#pragma once
#include "ChartCtrl\ChartCtrl.h"


// ShowResult 对话框

class ShowResult : public CDialogEx
{
	DECLARE_DYNAMIC(ShowResult)

public:
	ShowResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ShowResult();

// 对话框数据
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CChartCtrl m_ChartCtrl2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonZx();
	afx_msg void OnBnClickedCheckZx();
	afx_msg void OnBnClickedCheckZz();
};
