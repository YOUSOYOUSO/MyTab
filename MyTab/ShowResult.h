#pragma once
#include "ChartCtrl\ChartCtrl.h"


// ShowResult �Ի���

class ShowResult : public CDialogEx
{
	DECLARE_DYNAMIC(ShowResult)

public:
	ShowResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShowResult();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	CChartCtrl m_ChartCtrl2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonZx();
	afx_msg void OnBnClickedCheckZx();
	afx_msg void OnBnClickedCheckZz();
};
