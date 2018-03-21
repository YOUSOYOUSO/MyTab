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
// CFront 对话框

class CFront : public CDialogEx
{
	DECLARE_DYNAMIC(CFront)

public:
	CFront(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFront();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartVideo0();
	afx_msg void OnBnClickedPluseVideo0();
	afx_msg void OnBnClickedEndVideo1();
	afx_msg void Display(IplImage * img, UINT ID);
	CButton PluseButton1;
};

