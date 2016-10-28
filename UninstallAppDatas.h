// UninstallAppDatas.h: CUninstallAppDatas クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNINSTALLAPPDATAS_H__B9850DAF_9374_49B2_8AA1_BAAF493BC1B9__INCLUDED_)
#define AFX_UNINSTALLAPPDATAS_H__B9850DAF_9374_49B2_8AA1_BAAF493BC1B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUninstallAppDatas  
{
protected:
	CString m_AppDataDir;

public:
	CUninstallAppDatas( CString AppDataDir );
	virtual ~CUninstallAppDatas();

};

#endif // !defined(AFX_UNINSTALLAPPDATAS_H__B9850DAF_9374_49B2_8AA1_BAAF493BC1B9__INCLUDED_)
