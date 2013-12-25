#pragma once
#include <iostream>
#include <stdio.h>
#include <shlobj.h>
#include <vector>

using namespace std ;

class CFileSearch
{
public:
	CFileSearch(void);
	~CFileSearch(void);

	void SetMode(int _mode){ m_mode = _mode ;}
	vector<string>* SearchLinkByName(const CString& _str) ;


private:
	int  GetPath(char* DeskTop, char * AppData);   
	IShellFolder* GetIShellFolderByPath(LPTSTR path);   
	BOOL ReadShortCut(LPTSTR linkName);   
	BOOL EnumAllItems(IEnumIDList *m_pEnum,BOOL isFolder,BOOL isQuickLanch) ;
	BOOL GetIEunmIDList(IShellFolder * m_pShellFolder,BOOL isRecur,BOOL isQuickLanch);
	BOOL GetDesktopIShellFolder();
private:

	CString m_strFind ;

	IShellFolder *m_pIShellFolder;
	IEnumIDList  *m_pFirstLayerFile;
	IEnumIDList  *m_pFirstLayerFolder;

	char m_strParentPath[MAX_PATH*2] ;
	char m_strPath[MAX_PATH*2];
	char m_strDeskTopPath[MAX_PATH*2];
	char m_strQuickLanchPath[MAX_PATH*2];

	vector<string> m_FindList ;
	int  m_mode ;

};

