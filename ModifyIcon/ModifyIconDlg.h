
// ModifyIconDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "IconOperate.h"

// CModifyIconDlg �Ի���
class CModifyIconDlg : public CDialogEx
{
// ����
public:
	CModifyIconDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MODIFYICON_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CIconOperate test ;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
