
// SexyBeach3FixDlg.h: 头文件
//

#pragma once


// CSexyBeach3FixDlg 对话框
class CSexyBeach3FixDlg : public CDialogEx
{
// 构造
public:
	CSexyBeach3FixDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SEXYBEACH3FIX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedExecuteAll();
private:
	int m_currentFunctionIndex;
	void ExecuteAllFunctions();
	void Reg1();
	void Reg2();
	void AppendToEditCtrl(const CString& strText);
	void RequestAdminPrivileges();
	void CleantheFolder();
	void CleanBat();
	void CleanQudong();

private:
	CEdit m_EditResult; // Edit control for displaying button execution results
};

