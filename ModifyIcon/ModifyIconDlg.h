
// ModifyIconDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "IconOperate.h"

// CModifyIconDlg 对话框
class CModifyIconDlg : public CDialogEx
{
// 构造
public:
	CModifyIconDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MODIFYICON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CIconOperate test ;
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();


	CString m_IConPos;
	CString m_LinkPos ;
	CString m_SearchName;
	CComboBox m_findlist;
	afx_msg void OnBnClickedBntRead();
	afx_msg void OnBnClickedBtnTest();
};
