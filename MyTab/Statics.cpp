// Statics.cpp : 实现文件
//

#include "stdafx.h"
#include "MyTab.h"
#include "Statics.h"
#include "afxdialogex.h"


// CStatics 对话框

IMPLEMENT_DYNAMIC(CStatics, CDialogEx)

CStatics::CStatics(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CStatics::~CStatics()
{
}

void CStatics::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStatics, CDialogEx)
	
END_MESSAGE_MAP()


// CStatics 消息处理程序


