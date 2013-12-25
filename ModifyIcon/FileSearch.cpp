#include "StdAfx.h"
#include "FileSearch.h"

FILE *fp ;
CFileSearch::CFileSearch(void)
{
	m_pIShellFolder = NULL ;
	m_mode = 0 ;
	fp = fopen("search.txt","w+");
}


CFileSearch::~CFileSearch(void)
{
	fclose(fp);
}

vector<string>* CFileSearch::SearchLinkByName(const CString& _str) 
{
	m_FindList.clear();
	m_strFind = _str ;

	GetPath(m_strDeskTopPath,m_strQuickLanchPath);   
	if(GetDesktopIShellFolder())   
	{   
		GetIEunmIDList(m_pIShellFolder,FALSE,m_mode);   
	} 


	fprintf(fp,"\n\n\n\n");
	for (int i = 0 ; i < m_FindList.size() ; i++)
	{
		fprintf(fp,"%s\n",m_FindList[i].c_str());
	}
	return &m_FindList ;
}

//获取桌面文件夹和快速启动文件夹的路径    
int CFileSearch::GetPath(char *DeskTop, char* AppData)   
{   
	CRegKey m_reg;   
	if(ERROR_SUCCESS==m_reg.Open(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Shell Folders",KEY_READ))   
	{   
		ULONG m_ulsize1=1000;   
		ULONG m_ulsize2=1000;   
		m_reg.QueryStringValue("Desktop",DeskTop,&m_ulsize1); 
		m_reg.QueryStringValue("AppData",AppData,&m_ulsize2);   
		lstrcat(AppData,"\\Microsoft\\Internet Explorer\\Quick Launch"); 

	}   
	return 0;   
}   

//获取桌面文件夹的IShellFolder接口指针    
BOOL CFileSearch::GetDesktopIShellFolder()   
{   
	m_pIShellFolder=GetIShellFolderByPath(m_strDeskTopPath);   
	//m_pAppData=GetIShellFolderByPath(m_strQuickLanchPath);   
	return TRUE;   
}   

//获取桌面文件夹的IEnumIDList接口    
//isQuickLanch---是否搜索第二层文件夹
//isRecur---是否是文件夹
BOOL CFileSearch::GetIEunmIDList(IShellFolder * pShellFolder,BOOL isRecur,BOOL isQuickLanch)   
{   
	IEnumIDList *pIEnumFile     = NULL ;
	IEnumIDList *pIEnumFolder = NULL ;

	if(!pShellFolder) 
		return FALSE;   

	HRESULT hr=pShellFolder->EnumObjects(0,SHCONTF_NONFOLDERS,&pIEnumFile);        //不是文件夹
	if(FAILED(hr))   
	{   
		return FALSE;   
	}   
	if(!isRecur)   
	{   
		m_pFirstLayerFile = pIEnumFile;            
	}   
	EnumAllItems(pIEnumFile,FALSE,isQuickLanch);   

	if(!isQuickLanch)                             
	{   
		HRESULT hr=pShellFolder->EnumObjects(0,SHCONTF_FOLDERS,&pIEnumFolder);      //文件夹
		if(FAILED(hr))   
		{   
			return FALSE;   
		}   

		if(!isRecur)   
		{   
			m_pFirstLayerFolder = pIEnumFolder;  
		}   

		EnumAllItems(pIEnumFolder,TRUE,isQuickLanch);   
	}   
	return TRUE;   
}   
 
BOOL CFileSearch::EnumAllItems(IEnumIDList *m_pEnum,BOOL isFolder,BOOL isQuickLanch)   
{   
	LPITEMIDLIST m_pItem=NULL;   
	ULONG   m_ulwork= 0;     
	while(m_pEnum->Next(1,&m_pItem,&m_ulwork)==S_OK)   
	{   
		//如果是第一层，重置路径    
		if(!isQuickLanch)   
		{   
			if((m_pFirstLayerFolder==m_pEnum) && (isFolder))   
			{   
				lstrcpy(m_strParentPath,m_strDeskTopPath);   
			}   

			if((m_pFirstLayerFile==m_pEnum) && (!isFolder))   
			{   
				lstrcpy(m_strParentPath,m_strDeskTopPath);   
			}      
		}   
		else   
		{   
		//	if((m_pFirstLayerFile==m_pEnum) && (!isFolder))   
		//	{   
		//		lstrcpy(m_strParentPath,m_strQuickLanchPath);   
		//	}   
			if((m_pFirstLayerFolder==m_pEnum) && (isFolder))   
			{   
				lstrcpy(m_strParentPath,m_strDeskTopPath);   
			}   

			if((m_pFirstLayerFile==m_pEnum) && (!isFolder))   
			{   
				lstrcpy(m_strParentPath,m_strDeskTopPath);   
			}   
		}   

		WIN32_FIND_DATA ffd;   
		SHGetDataFromIDList(m_pIShellFolder,m_pItem,SHGDFIL_FINDDATA,&ffd,sizeof(WIN32_FIND_DATA));   
		if(!isFolder)   
		{   
			CString m_strTempPath=m_strParentPath;   
			m_strTempPath+="\\";   
			m_strTempPath += ffd.cFileName;   
			CString m_strCmp=".lnk";   

			fprintf(fp,"%s\n",m_strTempPath.GetBuffer());
			m_strTempPath.MakeUpper();   
			m_strCmp.MakeUpper();   

			if(m_strTempPath.Right(4)==m_strCmp)       //判断是否是链接文件 
			{   
				if (ReadShortCut(m_strTempPath.GetBuffer()))
				{
					string str = m_strTempPath.GetBuffer();
					m_FindList.push_back(str);
				} 
				m_strTempPath.ReleaseBuffer();   
			}   
		}   
		else   
		{   
			lstrcat(m_strParentPath,"\\");   
			lstrcat(m_strParentPath,ffd.cFileName);   
			IShellFolder *m_pITemp=GetIShellFolderByPath(m_strParentPath);   
			GetIEunmIDList(m_pITemp,TRUE,isQuickLanch);   
		}   
	}   
	return TRUE;   
}   



//获取指定目录的IShellFolder接口    
IShellFolder *CFileSearch::GetIShellFolderByPath(LPTSTR path)   
{   
	IShellFolder *m_ShellFolderTopMost=NULL;   
	HRESULT hr=SHGetDesktopFolder(&m_ShellFolderTopMost);   
	if(FAILED(hr))   
	{   
		return NULL;   
	}   
	IShellFolder *m_pFolder;   
	LPITEMIDLIST pidlWorkDir=NULL;     
	OLECHAR strOleFilePath[MAX_PATH];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, path, -1, strOleFilePath, MAX_PATH );
	hr = m_ShellFolderTopMost->ParseDisplayName(NULL,NULL,strOleFilePath,NULL,&pidlWorkDir,NULL);      
	if(FAILED(hr))   
	{   
		return   NULL;      
	}   
	hr=m_ShellFolderTopMost->BindToObject(pidlWorkDir,NULL,IID_IShellFolder,(LPVOID*)&m_pFolder);     
	if(m_ShellFolderTopMost)m_ShellFolderTopMost->Release();   
	return m_pFolder;   
}   

//读取快捷方式的信息    
BOOL CFileSearch::ReadShortCut(LPTSTR linkName)   
{   
	::CoInitialize(NULL);   
	IShellLink *m_pIShellLink=NULL;   
	IPersistFile *m_pIPersistFile=NULL;   
	HRESULT hr=::CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,IID_IShellLink,(LPVOID*)&m_pIShellLink);   
	if(hr==S_OK)   
	{   
		hr=m_pIShellLink->QueryInterface(IID_IPersistFile,(void **)&m_pIPersistFile); 

		if(hr==S_OK)   
		{   
			USES_CONVERSION;    
			m_pIPersistFile->Load(T2COLE(linkName),STGM_READWRITE);

			char m_strPath[MAX_PATH]={0};   
			m_pIShellLink->GetPath(m_strPath,MAX_PATH,NULL,SLGP_UNCPRIORITY); 

			CString temp = m_strPath;   
			temp.MakeUpper();   

			m_strFind.MakeUpper();

			if (strstr(temp.GetBuffer(),m_strFind.GetBuffer()))  //判断应用程序名
			{
				//AfxMessageBox(temp);

				if(m_pIShellLink) 
					m_pIShellLink->Release(); 

				if(m_pIPersistFile) 
					m_pIPersistFile->Release();  

				::CoUninitialize();   
				return TRUE;   
			}
		}   
	}   
  
	if(m_pIShellLink) 
		m_pIShellLink->Release(); 

	if(m_pIPersistFile) 
		m_pIPersistFile->Release();  

	::CoUninitialize();   
	return FALSE;   
}  