// UninstallAppDatas.cpp: CUninstallAppDatas �N���X�̃C���v�������e�[�V����
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
// �\�z/����
//////////////////////////////////////////////////////////////////////

CUninstallAppDatas::CUninstallAppDatas( CString AppDataDir )
:m_AppDataDir( AppDataDir )
{
	CString	Test;
	// �A�v���P�[�V�����f�[�^�p�X�����擾
	SHGetSpecialFolderPath(NULL, Test.GetBuffer( MAX_PATH + 1 ), CSIDL_TEMPLATES, TRUE);
	Test.ReleaseBuffer();


}

CUninstallAppDatas::~CUninstallAppDatas()
{

}
