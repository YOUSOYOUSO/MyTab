// CString1.cpp: 实现文件
//

#include "stdafx.h"
#include "MyTab.h"
#include "CString1.h"
#include "afxdialogex.h"


// CString1 对话框

IMPLEMENT_DYNAMIC(CString1, CDialogEx)

CString1::CString1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CString1::~CString1()
{
}

void CString1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CString1, CDialogEx)
END_MESSAGE_MAP()


// CString1 消息处理程序
