#pragma once


// CStatics 对话框

class CStatics : public CDialogEx
{
	DECLARE_DYNAMIC(CStatics)

public:
	CStatics(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStatics();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedResult();
	afx_msg void OnBnClickedButtonResult();
};
