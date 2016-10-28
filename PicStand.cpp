// PicStand.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
//

#include "stdafx.h"
#include "PicStand.h"
#include "PicStandWnd.h"

#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPicStandApp

BEGIN_MESSAGE_MAP(CPicStandApp, CWinApp)
	//{{AFX_MSG_MAP(CPicStandApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicStandApp �N���X�̍\�z

CPicStandApp::CPicStandApp()
{
	m_bSharedFileExist = FALSE;
	m_pSharedData = NULL;
	m_hMap = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CPicStandApp �I�u�W�F�N�g

CPicStandApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPicStandApp �N���X�̏�����
BOOL CPicStandApp::InitInstance()
{
	CString	CommandString( m_lpCmdLine );

	CommandString.MakeUpper();

	// �A���C���X�g�[������
	if( CommandString == "REMOVE" ){

		Global_Initialize();

		CString	PicturePath = Global_GetCurrentDir();
		PicturePath = PicturePath + PICTURE_FOLDER;

		ITech_RemoveFiles( PicturePath );
		ITech_RemoveAllUserAppPathOnTempFile();

		HANDLE	hMap = OpenFileMapping( FILE_MAP_READ, TRUE, MAPPED_FILE_NAME );

		if( hMap ){

			SharedData*	pSharedData = (SharedData*)MapViewOfFile(
					hMap, FILE_MAP_READ, 0, 0, sizeof(SharedData) );

			if( pSharedData ){

				::SendMessage( pSharedData->hWnd, WM_CLOSE, NULL, NULL );
			}

			UnmapViewOfFile( pSharedData );
			CloseHandle( hMap );
		}

		return FALSE;
	}

	// Shared File Mapping �̐���
	m_hMap = CreateFileMapping(
		(HANDLE)0xffffffff,
		NULL,
		PAGE_READWRITE | SEC_COMMIT,
		0, sizeof( SharedData ), 
		MAPPED_FILE_NAME );

	if( GetLastError() == ERROR_ALREADY_EXISTS ){

		m_bSharedFileExist = TRUE;
	}

	if( !m_hMap ){

		return FALSE;
	}

	m_pSharedData = (SharedData*)MapViewOfFile(
		m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedData) );

	// ���ɗ����オ���Ă���ꍇ�̏���
	if( m_bSharedFileExist ){

		if( IsWindow( m_pSharedData->hWnd ) ){
			SetForegroundWindow( m_pSharedData->hWnd );
		}
		UnmapViewOfFile( m_pSharedData );
		m_pSharedData = NULL;
		CloseHandle( m_hMap );
		m_hMap = NULL;
		return FALSE;
	}

	// RegistryKey�̃��[�g�ݒ�
	SetRegistryKey( _T( "IdeaTech" ) );

	// Global �f�[�^�̏�����
	Global_Initialize();

	// Window �̐���
	CPicStandWnd*	pPicStandWnd = new CPicStandWnd;

	m_pMainWnd = pPicStandWnd;

	if( !pPicStandWnd->Create() ){ return FALSE; }

	pPicStandWnd->ShowWindow(SW_SHOW);
	pPicStandWnd->UpdateWindow();

	return TRUE;
}

int CPicStandApp::ExitInstance() 
{
	if( !m_bSharedFileExist ){

		// �t�@�C���}�b�s���O�̍폜
		if( m_pSharedData ){
			UnmapViewOfFile( m_pSharedData );
			m_pSharedData = NULL;
		}
		if( m_hMap ){
			CloseHandle( m_hMap );
			m_hMap = NULL;
		}

		// Global �f�[�^�I������
		Global_Finalize();
	}

	return CWinApp::ExitInstance();
}

void CPicStandApp::SetHandleToSharedData(HWND hWnd)
{
	if( !m_bSharedFileExist ){

		m_pSharedData->hWnd = hWnd;

	}
}
