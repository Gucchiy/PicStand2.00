// UninstallAppDatas.cpp: CUninstallAppDatas クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UninstallAppDatas.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CUninstallAppDatas::CUninstallAppDatas( CString AppDataDir )
:m_AppDataDir( AppDataDir )
{
	CString	Test;
	// アプリケーションデータパス名を取得
	SHGetSpecialFolderPath(NULL, Test.GetBuffer( MAX_PATH + 1 ), CSIDL_TEMPLATES, TRUE);
	Test.ReleaseBuffer();


}

CUninstallAppDatas::~CUninstallAppDatas()
{

}
