// TabPage2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyTab.h"
#include "TabPage2.h"
#include "afxdialogex.h"
#include "CString1.h"
#include <stdlib.h>

// CTabPage2 �Ի���
float hang = 300, lie = 200;
float alpha = 0.99, beta = 0.01, gamma = 0.0;

IMPLEMENT_DYNAMIC(CTabPage2, CDialogEx)

extern char* CStringToChar(CString str)
{
	const size_t strsize = (str.GetLength() + 1) * 2;
	char * pstr = new char[strsize];
	size_t sz = 0;
	wcstombs_s(&sz, pstr, strsize, str, _TRUNCATE);
	return pstr;
}

CTabPage2::CTabPage2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CTabPage2::~CTabPage2()
{
}

void CTabPage2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabPage2, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Com, &CTabPage2::OnBnClickedButtonCom)
	//ON_EN_CHANGE(IDC_EDIT1, &CTabPage2::OnEnChangeEdit1)
	//ON_EN_CHANGE(IDC_EDIT6, &CTabPage2::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON_Con, &CTabPage2::OnBnClickedButtonCon)
	//ON_BN_CLICKED(IDC_BUTTON_Cop, &CTabPage2::OnBnClickedButtonCop)
END_MESSAGE_MAP()


// CTabPage2 ��Ϣ�������


void CTabPage2::OnBnClickedButtonCom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString jrs, prs;
	GetDlgItemText(IDC_EDIT1, jrs);
	char* njrs = CStringToChar(jrs);
	hang = atof(njrs);
	GetDlgItemText(IDC_EDIT2, prs);
	char* nprs = CStringToChar(prs);
	lie = atof(nprs);
}


void CTabPage2::OnBnClickedButtonCon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString alpha1, beta1, gamma1;
	GetDlgItemText(IDC_EDIT4, alpha1);
	char* nalpha1 = CStringToChar(alpha1);
	alpha = atof(nalpha1);
	GetDlgItemText(IDC_EDIT5, beta1);
	char* nbeta1 = CStringToChar(beta1);
	beta = atof(nbeta1);
	GetDlgItemText(IDC_EDIT6, gamma1);
	char* ngamma1 = CStringToChar(gamma1);
	gamma = atof(ngamma1);
}



/*void CTabPage2::OnBnClickedButtonCop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString boundary1;
	GetDlgItemText(IDC_EDIT7, boundary1);
	char* nboundary1 = CStringToChar(boundary1);
	boundary = atof(nboundary1);
}*/
