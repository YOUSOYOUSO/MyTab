// TabPage2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyTab.h"
#include "TabPage2.h"
#include "afxdialogex.h"


// CTabPage2 �Ի���

IMPLEMENT_DYNAMIC(CTabPage2, CDialogEx)

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
END_MESSAGE_MAP()


// CTabPage2 ��Ϣ�������
