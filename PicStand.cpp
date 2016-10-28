// PicStand.cpp : アプリケーション用クラスの定義を行います。
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
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPicStandApp クラスの構築

CPicStandApp::CPicStandApp()
{
	m_bSharedFileExist = FALSE;
	m_pSharedData = NULL;
	m_hMap = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CPicStandApp オブジェクト

CPicStandApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPicStandApp クラスの初期化
BOOL CPicStandApp::InitInstance()
{
	CString	CommandString( m_lpCmdLine );

	CommandString.MakeUpper();

	// アンインストール処理
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

	// Shared File Mapping の生成
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

	// 既に立ち上がっている場合の処理
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

	// RegistryKeyのルート設定
	SetRegistryKey( _T( "IdeaTech" ) );

	// Global データの初期化
	Global_Initialize();

	// Window の生成
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

		// ファイルマッピングの削除
		if( m_pSharedData ){
			UnmapViewOfFile( m_pSharedData );
			m_pSharedData = NULL;
		}
		if( m_hMap ){
			CloseHandle( m_hMap );
			m_hMap = NULL;
		}

		// Global データ終了処理
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
