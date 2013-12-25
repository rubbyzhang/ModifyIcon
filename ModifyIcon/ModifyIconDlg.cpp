
// ModifyIconDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CModifyIconDlg �Ի���




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


// CModifyIconDlg ��Ϣ�������

BOOL CModifyIconDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CModifyIconDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CModifyIconDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����ͼ��
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

//ѡ��Ҫ�滻��ͼ��
void CModifyIconDlg::OnBnClickedButton5()
{
	m_IConPos.Empty();
	CFileDialog   dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY,NULL, NULL);
	if (dlgFile.DoModal())
	{
		m_IConPos = dlgFile.GetPathName();
	}
}

//ѡ���ݷ�ʽ
void CModifyIconDlg::OnBnClickedButton6()
{

	int nIndex = m_findlist.GetCurSel(); //��ǰѡ�е���
	m_findlist.GetLBText( nIndex, m_LinkPos);
}

//����ͼ��ѡ��
void CModifyIconDlg::OnBnClickedButton1()
{
	UpdateData(true);

	int nIndex = m_findlist.GetCurSel(); //��ǰѡ�е���
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

//��ͼ��
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

//�޸�ͼ��
void CModifyIconDlg::OnBnClickedButton2()
{
	test.Modefiy();
}

//����ͼ��
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

//��������ͼ��
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
