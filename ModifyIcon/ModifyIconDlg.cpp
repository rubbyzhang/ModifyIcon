
// ModifyIconDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModifyIcon.h"
#include "ModifyIconDlg.h"
#include "afxdialogex.h"
#include "FileSearch.h"
#include "ModifyLinkICon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CModifyIconDlg 对话框




CModifyIconDlg::CModifyIconDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModifyIconDlg::IDD, pParent)
	, m_SearchName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModifyIconDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_SearchName);
	DDX_Control(pDX, IDC_COMBO1, m_findlist);
}

BEGIN_MESSAGE_MAP(CModifyIconDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CModifyIconDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CModifyIconDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CModifyIconDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CModifyIconDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CModifyIconDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BNT_READ, &CModifyIconDlg::OnBnClickedBntRead)
	ON_BN_CLICKED(IDC_BTN_TEST, &CModifyIconDlg::OnBnClickedBtnTest)
END_MESSAGE_MAP()


// CModifyIconDlg 消息处理程序

BOOL CModifyIconDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CModifyIconDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CModifyIconDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CModifyIconDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//搜索图标
void CModifyIconDlg::OnBnClickedButton4()
{

	UpdateData(TRUE);
	CFileSearch test ;
	test.SetMode(0);

	vector<string> *findlist = test.SearchLinkByName(m_SearchName.GetBuffer());
	m_findlist.ResetContent();
	if (findlist)
	{
		vector<string>::iterator it = findlist->begin();
		for (it ; it!=findlist->end(); ++it)
		{
			string str = (*it);
			m_findlist.AddString(str.c_str());
		}

		m_findlist.SetCurSel(0);
	}

	UpdateData(false);

}

//选族要替换的图标
void CModifyIconDlg::OnBnClickedButton5()
{
	m_IConPos.Empty();
	CFileDialog   dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY,NULL, NULL);
	if (dlgFile.DoModal())
	{
		m_IConPos = dlgFile.GetPathName();
	}
}

//选择快捷方式
void CModifyIconDlg::OnBnClickedButton6()
{

	int nIndex = m_findlist.GetCurSel(); //当前选中的项
	m_findlist.GetLBText( nIndex, m_LinkPos);
}

//更改图标选项
void CModifyIconDlg::OnBnClickedButton1()
{
	UpdateData(true);

	int nIndex = m_findlist.GetCurSel(); //当前选中的项
	m_findlist.GetLBText( nIndex, m_LinkPos);


	string strIconPath;
	string strLinkPath;

	strIconPath = m_IConPos.GetBuffer();
	m_IConPos.ReleaseBuffer();

	strLinkPath = m_LinkPos.GetBuffer();
	m_LinkPos.ReleaseBuffer();

	//ChangeLinkIcon(strLinkPath,strIconPath);
	CModifyLinkICon::ChangeLinkIcon(strLinkPath,strIconPath);
}

//读图标
void CModifyIconDlg::OnBnClickedBntRead()
{
	CFileDialog   dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY,NULL, NULL);
	if (dlgFile.DoModal())
	{
		CString strPath = dlgFile.GetPathName();

		string str = strPath.GetBuffer();
		test.ReadIcon(str);
	}
}

//修改图标
void CModifyIconDlg::OnBnClickedButton2()
{
	test.Modefiy();
}

//保存图标
void CModifyIconDlg::OnBnClickedButton3()
{
	CFileDialog   dlgFile(FALSE, NULL, NULL, OFN_HIDEREADONLY,NULL, NULL);
	if (dlgFile.DoModal())
	{
		CString strPath = dlgFile.GetPathName();
		string str = strPath.GetBuffer();
		test.SaveIcon(str);
	}
}

//产生测试图标
void CModifyIconDlg::OnBnClickedBtnTest()
{
	CFileDialog   dlgFile(FALSE, NULL, NULL, OFN_HIDEREADONLY,NULL, NULL);
	if (dlgFile.DoModal())
	{
		CString strPath = dlgFile.GetPathName();
		string str = strPath.GetBuffer();
		test.GenerateTestIcon(str);
	}
}
