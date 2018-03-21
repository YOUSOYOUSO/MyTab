#pragma once
#include "stdafx.h"
#include "MyTab.h"
#include "MyTabDlg.h"
#include "TabPage1.h"
#include "Front.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include <opencv2\core\core.hpp>

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include "CvvImage.h"
#include "afxwin.h"

using namespace std;
using namespace cv;

// CTabPage1 对话框

class CTabPage1 : public CDialogEx
{
	DECLARE_DYNAMIC(CTabPage1)

public:
	CTabPage1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTabPage1();//改之前为virtual ~CTabPage1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif
	CFront *m_pTipDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonPlay();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedStarttVideo();
	afx_msg void OnBnClickedPluseVideo();
	afx_msg void OnBnClickedEndVideo();
	afx_msg void OnBnClickedConvert();
	afx_msg void Display(IplImage * img, UINT ID);
	CButton PluseButton;
	afx_msg void OnBnClickedButtonTofront();
};
