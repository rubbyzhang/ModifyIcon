#pragma once
#include <iostream>
#include <stdio.h>
#include <shlobj.h>
using namespace std;
/*
	修改快捷方式图标
	strLnkName -- 快捷方式图标位置
	strIconPath-- 要修改的图标资源位置，必须为ICON格式
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

