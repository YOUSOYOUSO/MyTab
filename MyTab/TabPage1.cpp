// TabPage1.cpp : 实现文件
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

CEvent start_event;
int terminate_flag;
int totalframe;

extern int testBJC();
// CTabPage1 对话框
CString file_address;  //#文件地址变量#
int flag_1 = 0;//#判断是否已经添加文件#

IMPLEMENT_DYNAMIC(CTabPage1, CDialogEx)

CTabPage1::CTabPage1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_pTipDlg = NULL;
}


void CTabPage1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PLUSE_VIDEO, PluseButton);
}


BEGIN_MESSAGE_MAP(CTabPage1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CTabPage1::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CTabPage1::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CTabPage1::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CTabPage1::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_STARTT_VIDEO, &CTabPage1::OnBnClickedStarttVideo)
	ON_BN_CLICKED(IDC_PLUSE_VIDEO, &CTabPage1::OnBnClickedPluseVideo)
	ON_BN_CLICKED(IDC_END_VIDEO, &CTabPage1::OnBnClickedEndVideo)
	ON_BN_CLICKED(IDC_CONVERT, &CTabPage1::OnBnClickedConvert)
	ON_BN_CLICKED(IDC_BUTTON_TOFRONT, &CTabPage1::OnBnClickedButtonTofront)
	ON_BN_CLICKED(IDC_BUTTON_RESULT, &CTabPage1::OnBnClickedButtonResult)
END_MESSAGE_MAP()


// CTabPage1 消息处理程序


void CTabPage1::OnBnClickedButtonRead()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szFilter[] = _T("mp4(*.mp4)|*.mp4|jpg(*.jpg)|*.jpg|bmp(*.bmp)|*.bmp|All files(*.*)|*.*||"); //可供选择的后缀
																									  // 构造保存文件对话框   

	CFileDialog fileDlg(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	CString strFilePath;   //文件路径

						   // 显示打开文件对话框   
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“保存”按钮，则将选择的文件路径显示到编辑框里   
		strFilePath = fileDlg.GetFileName();
		SetDlgItemText(IDC_EDIT1, strFilePath);
		//将文件地址传给全局变量
		file_address = strFilePath;
		flag_1 = 1;//表示已经添加文件
	}
}


void CTabPage1::OnBnClickedButtonReset()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	flag_1 = 0; //撤销操作会删除已经选择的文件，将flag_1赋值为1
}


void CTabPage1::OnBnClickedButtonPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
	if (flag_1 == 0) {
		AfxMessageBox(_T("没有选择任何文件！"));
		CTabPage1 dlg;
		dlg.DoModal();
		//没有添加文件则返回原来界面
	}
	else {
		CStatics dlg;
		dlg.DoModal();
		//已经添加文件则跳转到视频播放界面
	}
}


void CTabPage1::OnBnClickedButtonCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

DWORD WINAPI PlayVideo(LPVOID lpParam) {

	CTabPage1* pThis = (CTabPage1*)lpParam;
	CvCapture* pCapture;
	IplImage* pFrame;
	//const char* ABC;
	//ABC = "233.mp4";//测试下

	const wchar_t* wstr = (LPCTSTR)file_address;     //一定得是unicode，否则这句话会错的
	char str[20] = { 0 };
	wcstombs(str, wstr, wcslen(wstr));
	//以上是完成了从CString 到 char* 的转换，将file_address的值传给str

	pCapture = cvCreateFileCapture(str);

	if (pCapture == NULL)
	{
		return -1;
	}

	pFrame = cvQueryFrame(pCapture);
	while (pFrame)
	{
		WaitForSingleObject(start_event, INFINITE);
		start_event.SetEvent();
		if (terminate_flag == -1)
		{
			terminate_flag = 0;
			_endthreadex(0);
		};
		pThis->Display(pFrame, IDC_STATIC);
		Sleep(33);
		pFrame = cvQueryFrame(pCapture);
	}

	cvReleaseCapture(&pCapture);

}

void CTabPage1::Display(IplImage * img, UINT ID) {

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


void CTabPage1::OnBnClickedStarttVideo()
{
	// TODO: 在此添加控件通知处理程序代码
	HANDLE hThreadSend;         //创建独立线程发送数据  
	DWORD ThreadSendID;

	start_event.SetEvent();

	hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayVideo, (LPVOID)this, 0, &ThreadSendID);
	CloseHandle(hThreadSend);
}



void CTabPage1::OnBnClickedPluseVideo()
{
	// TODO: 在此添加控件通知处理程序代码
	CString buttonText;
	PluseButton.GetWindowText(buttonText);

	if (buttonText.Compare(_T("暂停")) == 0)
	{
		start_event.ResetEvent();
		PluseButton.SetWindowTextW(_T("继续"));

	}
	else
	{
		start_event.SetEvent();
		PluseButton.SetWindowText(_T("暂停"));
	}
}


void CTabPage1::OnBnClickedEndVideo()
{
	// TODO: 在此添加控件通知处理程序代码
	terminate_flag = -1;
}




void CTabPage1::OnBnClickedConvert()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(_T("正在转换，请等一段时间！"));
	totalframe=testBJC();
	AfxMessageBox(_T("转换完成！"));
}


void CTabPage1::OnBnClickedButtonTofront()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pTipDlg == NULL)
	{
		m_pTipDlg = new CFront;
		m_pTipDlg->Create(IDD_DIALOG3, this);
	}

	m_pTipDlg->ShowWindow(SW_SHOW);//换一个函数
}

void CTabPage1::OnBnClickedButtonResult() {
	//AfxMessageBox(_T("CNM！！"));
	RDlg = new ShowResult;
	RDlg->Create(IDD_DIALOG4, this);
	RDlg->ShowWindow(SW_SHOW);//换一个函数
}

CTabPage1::~CTabPage1()
{
	if (m_pTipDlg != NULL)
	{
		delete m_pTipDlg;
		m_pTipDlg = NULL;
	}
}