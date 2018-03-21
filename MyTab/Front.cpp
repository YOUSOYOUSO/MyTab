// Front.cpp : 实现文件
//

#include "stdafx.h"
#include "MyTab.h"
#include "MyTabDlg.h"
#include "TabPage1.h"
#include "resource.h"
#include "Statics.h"
#include "Front.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"
#include <opencv2\core\core.hpp>

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>
#include "CvvImage.h"

using namespace std;
using namespace cv;

CEvent start_event1;
int terminate_flag1;
// CFront 对话框

IMPLEMENT_DYNAMIC(CFront, CDialogEx)

CFront::CFront(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CFront::~CFront()
{
}

void CFront::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLUSE_VIDEO0, PluseButton1);
}


BEGIN_MESSAGE_MAP(CFront, CDialogEx)
	ON_BN_CLICKED(IDC_START_VIDEO0, &CFront::OnBnClickedStartVideo0)
	ON_BN_CLICKED(IDC_PLUSE_VIDEO0, &CFront::OnBnClickedPluseVideo0)
	ON_BN_CLICKED(IDC_END_VIDEO1, &CFront::OnBnClickedEndVideo1)
END_MESSAGE_MAP()


// CFront 消息处理程序
void CFront::Display(IplImage * img, UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();  //CDC是一个类  
										 //GetDlgItem(ID)获取控件窗口对象,GetDC()由窗口对象得到DC,然后可以用来在控件中画图  
										 //上一句等价于CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  

	HDC hDC = pDC->GetSafeHdc();//HDC是一个句柄     
	CRect rect;
	CWnd  *pWnd;

	int picWidth;
	int picHeight;

	pWnd = GetDlgItem(ID);
	pWnd->GetClientRect(&rect);

	//求图片控件的宽和高  
	picWidth = rect.Width();
	picHeight = rect.Height();

	IplImage*dst = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);
	cvResize(img, dst, CV_INTER_LINEAR);

	//  cvFlip(dst,NULL,0);       
	//在控件里显示图片  
	CvvImage cimg;
	cimg.CopyOf(dst);
	cimg.DrawToHDC(hDC, &rect);
	cvReleaseImage(&dst);
	ReleaseDC(pDC);
}

DWORD WINAPI PlayVideo1(LPVOID lpParam) {
	//这个函数负责前景视频的播放
	CFront* pThis = (CFront*)lpParam;
	CvCapture* pCapture;
	IplImage* pFrame;

	pCapture = cvCreateFileCapture("QJ.avi");

	if (pCapture == NULL)
	{
		return -1;
	}

	pFrame = cvQueryFrame(pCapture);
	while (pFrame)
	{
		WaitForSingleObject(start_event1, INFINITE);
		start_event1.SetEvent();
		if (terminate_flag1 == -1)
		{
			terminate_flag1 = 0;
			_endthreadex(0);
		};
		pThis->Display(pFrame, IDC_STATIC1);
		Sleep(33);
		pFrame = cvQueryFrame(pCapture);
	}

	cvReleaseCapture(&pCapture);

}

void CFront::OnBnClickedStartVideo0()
{
	// TODO: 在此添加控件通知处理程序代码
	HANDLE hThreadSend;         //创建独立线程发送数据  
	DWORD ThreadSendID;

	start_event1.SetEvent();

	hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayVideo1, (LPVOID)this, 0, &ThreadSendID);
	CloseHandle(hThreadSend);
}


void CFront::OnBnClickedPluseVideo0()
{
	// TODO: 在此添加控件通知处理程序代码
	CString buttonText;
	PluseButton1.GetWindowText(buttonText);

	if (buttonText.Compare(_T("暂停")) == 0)
	{
		start_event1.ResetEvent();
		PluseButton1.SetWindowText(_T("继续"));

	}
	else
	{
		start_event1.SetEvent();
		PluseButton1.SetWindowText(_T("暂停"));
	}
}


void CFront::OnBnClickedEndVideo1()
{
	// TODO: 在此添加控件通知处理程序代码
	terminate_flag1 = -1;
}



