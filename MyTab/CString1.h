#pragma once


// CString1 对话框

class CString1 : public CDialogEx
{
	DECLARE_DYNAMIC(CString1)

public:
	CString1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CString1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
