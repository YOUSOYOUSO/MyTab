// Front.cpp : ʵ���ļ�
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
// CFront �Ի���

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


// CFront ��Ϣ�������
void CFront::Display(IplImage * img, UINT ID)
{
	CDC* pDC = GetDlgItem(ID)->GetDC();  //CDC��һ����  
										 //GetDlgItem(ID)��ȡ�ؼ����ڶ���,GetDC()�ɴ��ڶ���õ�DC,Ȼ����������ڿؼ��л�ͼ  
										 //��һ��ȼ���CWnd* pWin=GetDlgItem(ID);  CDC* pDC=pWin->GetDC();  

	HDC hDC = pDC->GetSafeHdc();//HDC��һ�����     
	CRect rect;
	CWnd  *pWnd;

	int picWidth;
	int picHeight;

	pWnd = GetDlgItem(ID);
	pWnd->GetClientRect(&rect);

	//��ͼƬ�ؼ��Ŀ�͸�  
	picWidth = rect.Width();
	picHeight = rect.Height();

	IplImage*dst = cvCreateImage(cvSize(picWidth, picHeight), img->depth, img->nChannels);
	cvResize(img, dst, CV_INTER_LINEAR);

	//  cvFlip(dst,NULL,0);       
	//�ڿؼ�����ʾͼƬ  
	CvvImage cimg;
	cimg.CopyOf(dst);
	cimg.DrawToHDC(hDC, &rect);
	cvReleaseImage(&dst);
	ReleaseDC(pDC);
}

DWORD WINAPI PlayVideo1(LPVOID lpParam) {
	//�����������ǰ����Ƶ�Ĳ���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HANDLE hThreadSend;         //���������̷߳�������  
	DWORD ThreadSendID;

	start_event1.SetEvent();

	hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayVideo1, (LPVOID)this, 0, &ThreadSendID);
	CloseHandle(hThreadSend);
}


void CFront::OnBnClickedPluseVideo0()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buttonText;
	PluseButton1.GetWindowText(buttonText);

	if (buttonText.Compare(_T("��ͣ")) == 0)
	{
		start_event1.ResetEvent();
		PluseButton1.SetWindowText(_T("����"));

	}
	else
	{
		start_event1.SetEvent();
		PluseButton1.SetWindowText(_T("��ͣ"));
	}
}


void CFront::OnBnClickedEndVideo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	terminate_flag1 = -1;
}



