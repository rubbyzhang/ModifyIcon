#pragma once
#include <iostream>
#include <stdio.h>
#include <shlobj.h>
using namespace std;
/*
	�޸Ŀ�ݷ�ʽͼ��
	strLnkName -- ��ݷ�ʽͼ��λ��
	strIconPath-- Ҫ�޸ĵ�ͼ����Դλ�ã�����ΪICON��ʽ
*/
class CModifyLinkICon
{
public:
	CModifyLinkICon(void);
	CModifyLinkICon(const string& strLnkName,const string& strIconPath);

	~CModifyLinkICon(void);

	bool ChangeLinkIcon() ;
	static bool ChangeLinkIcon(const string& strLnkName,const string& strIconPath) ;
private:
	string m_strLinkName;
	string m_strIconPath ;
};

