// PicStand.h : PICSTAND �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_PICSTAND_H__F3F485E9_8836_4AC0_90AD_CAC345ABBF92__INCLUDED_)
#define AFX_PICSTAND_H__F3F485E9_8836_4AC0_90AD_CAC345ABBF92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CPicStandApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� PicStand.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

#define	MAPPED_FILE_NAME	_T( "PicStandMappedFile" )

typedef struct {
	HWND	hWnd;
}SharedData;

class CPicStandApp : public CWinApp
{
protected:
	BOOL		m_bSharedFileExist;
	SharedData*	m_pSharedData;
	HANDLE		m_hMap;

public:
	void SetHandleToSharedData( HWND hWnd );
	CPicStandApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CPicStandApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CPicStandApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PICSTAND_H__F3F485E9_8836_4AC0_90AD_CAC345ABBF92__INCLUDED_)
