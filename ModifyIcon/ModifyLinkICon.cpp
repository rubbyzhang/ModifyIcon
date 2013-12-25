#include "StdAfx.h"
#include "ModifyLinkICon.h"


CModifyLinkICon::CModifyLinkICon(void):
m_strIconPath("")
,m_strLinkName("")
{

}

CModifyLinkICon::CModifyLinkICon(const string& strLnkName,const string& strIconPath):
m_strIconPath(strIconPath)
,m_strLinkName(strLnkName)
{

}

CModifyLinkICon::~CModifyLinkICon(void)
{

}

bool CModifyLinkICon::ChangeLinkIcon() 
{
	if (m_strLinkName.empty() || m_strIconPath.empty())
	{
		return false;
	}

	HRESULT hres;
	IShellLink *psl = NULL;
	IPersistFile *pPf = NULL;
	int id;
	LPITEMIDLIST pidl;
	bool bRet = false;

	do
	{
		hres = CoInitialize(NULL);
		if (FAILED(hres))
		{
			break;
		}

		hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
		if (FAILED(hres))
		{
			break;
		}

		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&pPf);
		if (FAILED(hres))
		{
			break;
		}

		wchar_t wsz[256];
		MultiByteToWideChar(CP_ACP, 0, m_strLinkName.c_str(), -1, wsz, MAX_PATH);

		hres = pPf->Load(wsz, STGM_READWRITE);    
		if (FAILED(hres))
		{
			break;
		}

		hres = psl->SetIconLocation(m_strIconPath.c_str(), 0);
		if (FAILED(hres))
		{
			break;
		}

		pPf->Save(wsz, TRUE);
		if (FAILED(hres))
		{
			break;
		}

		bRet = true;

	} while (0);

	if (pPf != NULL)
	{
		pPf->Release();
	}

	if (psl != NULL)
	{
		psl->Release();
	}

	CoUninitialize();

	AfxMessageBox("替换完成");

	return bRet;
}

 bool CModifyLinkICon::ChangeLinkIcon(const string& strLnkName,const string& strIconPath)
{
	if (strLnkName.empty() || strIconPath.empty())
	{
		return false;
	}

	HRESULT hres;
	IShellLink *psl = NULL;
	IPersistFile *pPf = NULL;
	int id;
	LPITEMIDLIST pidl;
	bool bRet = false;

	do
	{
		hres = CoInitialize(NULL);
		if (FAILED(hres))
		{
			break;
		}

		hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
		if (FAILED(hres))
		{
			break;
		}

		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&pPf);
		if (FAILED(hres))
		{
			break;
		}

		wchar_t wsz[256];
		MultiByteToWideChar(CP_ACP, 0, strLnkName.c_str(), -1, wsz, MAX_PATH);

		hres = pPf->Load(wsz, STGM_READWRITE);    
		if (FAILED(hres))
		{
			break;
		}

		hres = psl->SetIconLocation(strIconPath.c_str(), 0);
		if (FAILED(hres))
		{
			break;
		}

		pPf->Save(wsz, TRUE);
		if (FAILED(hres))
		{
			break;
		}

		bRet = true;

	} while (0);

	if (pPf != NULL)
	{
		pPf->Release();
	}

	if (psl != NULL)
	{
		psl->Release();
	}

	CoUninitialize();

	AfxMessageBox("替换完成");

	return bRet;
}
