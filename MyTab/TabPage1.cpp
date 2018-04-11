// TabPage1.cpp : ʵ���ļ�
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
// CTabPage1 �Ի���
CString file_address;  //#�ļ���ַ����#
int flag_1 = 0;//#�ж��Ƿ��Ѿ�����ļ�#

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


// CTabPage1 ��Ϣ�������


void CTabPage1::OnBnClickedButtonRead()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("mp4(*.mp4)|*.mp4|jpg(*.jpg)|*.jpg|bmp(*.bmp)|*.bmp|All files(*.*)|*.*||"); //�ɹ�ѡ��ĺ�׺
																									  // ���챣���ļ��Ի���   

	CFileDialog fileDlg(TRUE, 0, 0, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	CString strFilePath;   //�ļ�·��

						   // ��ʾ���ļ��Ի���   
	if (IDOK == fileDlg.DoModal())
	{
		// ���������ļ��Ի����ϵġ����桱��ť����ѡ����ļ�·����ʾ���༭����   
		strFilePath = fileDlg.GetFileName();
		SetDlgItemText(IDC_EDIT1, strFilePath);
		//���ļ���ַ����ȫ�ֱ���
		file_address = strFilePath;
		flag_1 = 1;//��ʾ�Ѿ�����ļ�
	}
}


void CTabPage1::OnBnClickedButtonReset()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT1)->SetWindowText(_T(""));
	flag_1 = 0; //����������ɾ���Ѿ�ѡ����ļ�����flag_1��ֵΪ1
}


void CTabPage1::OnBnClickedButtonPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
	if (flag_1 == 0) {
		AfxMessageBox(_T("û��ѡ���κ��ļ���"));
		CTabPage1 dlg;
		dlg.DoModal();
		//û������ļ��򷵻�ԭ������
	}
	else {
		CStatics dlg;
		dlg.DoModal();
		//�Ѿ�����ļ�����ת����Ƶ���Ž���
	}
}


void CTabPage1::OnBnClickedButtonCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

DWORD WINAPI PlayVideo(LPVOID lpParam) {

	CTabPage1* pThis = (CTabPage1*)lpParam;
	CvCapture* pCapture;
	IplImage* pFrame;
	//const char* ABC;
	//ABC = "233.mp4";//������

	const wchar_t* wstr = (LPCTSTR)file_address;     //һ������unicode��������仰����
	char str[20] = { 0 };
	wcstombs(str, wstr, wcslen(wstr));
	//����������˴�CString �� char* ��ת������file_address��ֵ����str

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


void CTabPage1::OnBnClickedStarttVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	HANDLE hThreadSend;         //���������̷߳�������  
	DWORD ThreadSendID;

	start_event.SetEvent();

	hThreadSend = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PlayVideo, (LPVOID)this, 0, &ThreadSendID);
	CloseHandle(hThreadSend);
}



void CTabPage1::OnBnClickedPluseVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString buttonText;
	PluseButton.GetWindowText(buttonText);

	if (buttonText.Compare(_T("��ͣ")) == 0)
	{
		start_event.ResetEvent();
		PluseButton.SetWindowTextW(_T("����"));

	}
	else
	{
		start_event.SetEvent();
		PluseButton.SetWindowText(_T("��ͣ"));
	}
}


void CTabPage1::OnBnClickedEndVideo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	terminate_flag = -1;
}




void CTabPage1::OnBnClickedConvert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AfxMessageBox(_T("����ת�������һ��ʱ�䣡"));
	totalframe=testBJC();
	AfxMessageBox(_T("ת����ɣ�"));
}


void CTabPage1::OnBnClickedButtonTofront()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pTipDlg == NULL)
	{
		m_pTipDlg = new CFront;
		m_pTipDlg->Create(IDD_DIALOG3, this);
	}

	m_pTipDlg->ShowWindow(SW_SHOW);//��һ������
}

void CTabPage1::OnBnClickedButtonResult() {
	//AfxMessageBox(_T("CNM����"));
	RDlg = new ShowResult;
	RDlg->Create(IDD_DIALOG4, this);
	RDlg->ShowWindow(SW_SHOW);//��һ������
}

CTabPage1::~CTabPage1()
{
	if (m_pTipDlg != NULL)
	{
		delete m_pTipDlg;
		m_pTipDlg = NULL;
	}
}