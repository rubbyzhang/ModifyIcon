
// ModifyIcon.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CModifyIconApp:
// �йش����ʵ�֣������ ModifyIcon.cpp
//

class CModifyIconApp : public CWinApp
{
public:
	CModifyIconApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CModifyIconApp theApp;