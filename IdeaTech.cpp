#include "stdafx.h"
#include "IdeaTech.h"

// モジュールファイル名の取得
CString ITech_GetModuleFileName()
{
	CString	ModuleFileString;
	::GetModuleFileName( AfxGetApp()->m_hInstance, ModuleFileString.GetBuffer( _MAX_PATH ), _MAX_PATH );
	ModuleFileString.ReleaseBuffer();

	return ModuleFileString;
}

// モジュールのカレントフォルダを取得
CString ITech_GetCurrentDir()
{
	// カレントフォルダを取得
	CString	ModuleFileString;
	::GetModuleFileName( AfxGetApp()->m_hInstance, ModuleFileString.GetBuffer( _MAX_PATH ), _MAX_PATH );
	ModuleFileString.ReleaseBuffer();

	CString	CurrentDirString;
	CString	DriveString;
	_splitpath( (LPCSTR)ModuleFileString, DriveString.GetBuffer( _MAX_DRIVE ), CurrentDirString.GetBuffer( _MAX_PATH ), NULL, NULL );
	CurrentDirString.ReleaseBuffer();
	DriveString.ReleaseBuffer();

	return ( DriveString + CurrentDirString );

}

// スタートアップ用フォルダを取得
CString ITech_GetStartupDir()
{
	CString StartupPath;
	SHGetSpecialFolderPath(NULL, StartupPath.GetBuffer( MAX_PATH + 1 ), CSIDL_STARTUP, FALSE);
	StartupPath.ReleaseBuffer();

	return ( StartupPath + _T( "\\" ) );
}

// アプリケーションデータ用フォルダを取得
// なければ生成する
CString ITech_GetAppDataDir()
{
	CString	AppDataPath;
	SHGetSpecialFolderPath(NULL, AppDataPath.GetBuffer( MAX_PATH + 1 ), CSIDL_APPDATA, TRUE);
	AppDataPath.ReleaseBuffer();

	AppDataPath += ( CString(_T( "\\" )) + CString( ITECH_APPDATA_FOLDER ) );

	ITech_MakeAndGetDir( AppDataPath );

	return AppDataPath;
}

// ファイルがあるかどうかの確認
BOOL ITech_IsTheFileExist( CString FileName )
{
	CFileStatus	FileStatus;
	return CFile::GetStatus( FileName, FileStatus );
}

// 指定パスを確認して、なければフォルダを生成し、
// 最後に "\\" をつけて retun する。
// 指定フォルダが存在:FALSE
// 指定フォルダがなかったのでフォルダを生成：TRUE
BOOL ITech_MakeAndGetDir( CString& PathName )
{
	BOOL	bReturn = FALSE;

	if( !ITech_IsTheFileExist( PathName ) ){

		// ない場合はテンプレートをコピー
		CreateDirectory( PathName, NULL );
		bReturn = TRUE;

	}
	PathName += _T( "\\" );

	return bReturn;
}

// フォルダ単位でコピーする
BOOL ITech_CopyFiles( CString SrcFolder, CString DstFolder )
{
	if( SrcFolder.Right(1) == _T( "\\" ) ){
		SrcFolder = SrcFolder.Left( SrcFolder.GetLength() - 1 );
	}

	if( DstFolder.Right(1) == _T( "\\" ) ){
		DstFolder = DstFolder.Left( DstFolder.GetLength() - 1 );
	}
		
	if( !ITech_IsTheFileExist( DstFolder ) ){

		CreateDirectory( DstFolder, NULL );

	}
	
	CFileStatus	FileStatus;
	CFile::GetStatus( DstFolder, FileStatus );
	if( !( FileStatus.m_attribute & 0x10 ) ){

		return FALSE;
	}

	DstFolder += _T( "\\" );

	CFileFind	FileFind;
	CString	TemplatePath = SrcFolder + _T( "\\*.*" );

	CString	SrcFilePath;
	CString	DstFilePath;
	CString	FileName;
	BOOL	bReturn = TRUE;
	BOOL	bWorking = FileFind.FindFile( TemplatePath );
	while( bWorking ){

		bWorking = FileFind.FindNextFile();

		SrcFilePath = FileFind.GetFilePath();
		DstFilePath = DstFolder + FileFind.GetFileName();
		FileName = FileFind.GetFileName();
		
		CopyFile( SrcFilePath, DstFilePath, TRUE );

		CFile::GetStatus( SrcFilePath, FileStatus );

		if( FileStatus.m_attribute & 0x10 ){

			if( ( FileName != "." ) && ( FileName != ".." ) ){
				bReturn = ITech_CopyFiles( SrcFilePath, DstFilePath );
			}

		}
	}

	return bReturn;
}

// フォルダ内にある全てのファイルを削除。フォルダも削除。
BOOL ITech_RemoveFiles( CString RemoveFolder )
{
	if( RemoveFolder.Right(1) == _T( "\\" ) ){
		RemoveFolder = RemoveFolder.Left( RemoveFolder.GetLength() - 1 );
	}

	if( !ITech_IsTheFileExist( RemoveFolder ) ){

		return FALSE;

	}
	
	CFileStatus	FileStatus;
	CFile::GetStatus( RemoveFolder, FileStatus );
	if( !( FileStatus.m_attribute & 0x10 ) ){

		return FALSE;
	}

	CFileFind	FileFind;
	CString	TemplatePath = RemoveFolder + _T( "\\*.*" );

	CString	RemoveFilePath;
	CString	FileName;
	BOOL	bReturn = TRUE;
	BOOL	bWorking = FileFind.FindFile( TemplatePath );
	while( bWorking ){

		bWorking = FileFind.FindNextFile();

		RemoveFilePath = FileFind.GetFilePath();
		FileName = FileFind.GetFileName();
		
		CFile::GetStatus( RemoveFilePath, FileStatus );

		if( FileStatus.m_attribute & 0x10 ){

			if( ( FileName != "." ) && ( FileName != ".." ) ){
				bReturn = ITech_RemoveFiles( RemoveFilePath );
			}

		}else{

			DWORD	dwAttr = GetFileAttributes( RemoveFilePath );
			dwAttr &= ~FILE_ATTRIBUTE_READONLY;
			SetFileAttributes( RemoveFilePath, dwAttr );
			DeleteFile( RemoveFilePath );
		}
	}

	FileFind.Close();

	RemoveDirectory( RemoveFolder );

	return bReturn;

}

// AppData フォルダを新規に作成した際に、TempFile に保存
BOOL ITech_AddAppPathToTempFile( CString NewAppFolder )
{
	if( NewAppFolder.Right(1) == _T( "\\" ) ){
		NewAppFolder = NewAppFolder.Left( NewAppFolder.GetLength() - 1 );
	}

	CString	TempFileName = ITech_GetCurrentDir() + ITECH_APPDATA_TMPFILE;

	CStdioFile	StdioFile( TempFileName, 
		CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite|CFile::typeText );

	NewAppFolder += _T( "\n" );
	StdioFile.SeekToEnd();
	StdioFile.WriteString( NewAppFolder );

	return TRUE;
}

// Uninstalle 時に、TempFile の内容から、AppData 上のファイルを削除
BOOL ITech_RemoveAllUserAppPathOnTempFile()
{
	CString	TempFileName = ITech_GetCurrentDir() + ITECH_APPDATA_TMPFILE;

	CStdioFile	StdioFile( TempFileName, 
		CFile::modeCreate|CFile::modeNoTruncate|CFile::modeRead|CFile::typeText );

	CString	RemoveFolder;

	BOOL bWorking = FALSE;
	do {

		bWorking = StdioFile.ReadString( RemoveFolder );
		if( bWorking ) ITech_RemoveFiles( RemoveFolder );

	} while( bWorking );

	StdioFile.Close();

	DeleteFile( TempFileName );

	return TRUE;
}

// "IdeaTechMessage" Message ID の取得
UINT ITech_GetIdeaTechMessage()
{
	return ::RegisterWindowMessage( ITECH_MES_STRING );
}

// ショートカットファイルの作成
BOOL ITech_CreateShorcut( const CString& DstShorcutPath,
	const CString& ModuleFileName, const CString& CurrentFolder, const CString& Title )
{
	IPersistFile*	pPersistFile = NULL;
	IShellLink*		pShellLink = NULL;
	HRESULT			hRes;	//各結果

	//　ＯＬＥを使うための初期化
	hRes = ::CoInitialize( NULL );

	if( hRes == E_OUTOFMEMORY )
		return FALSE;
	if( hRes == E_INVALIDARG )
		return FALSE;
	if( hRes == E_UNEXPECTED )
		return FALSE;

	//　空のインターフェイスを作成
	hRes = ::CoCreateInstance( CLSID_ShellLink, NULL,
				CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&pShellLink );

	if( hRes == CLASS_E_NOAGGREGATION )
		return FALSE;

	if( hRes == REGDB_E_CLASSNOTREG )
		return FALSE;

	
	//　IPersistFileへのポインタを取得
	hRes = pShellLink->QueryInterface( IID_IPersistFile, (LPVOID *)&pPersistFile );

	if( hRes != S_OK ){
		::CoUninitialize();
		return FALSE;
	}

	hRes = pShellLink->SetPath( ModuleFileName );			//リンク先パス
	hRes = pShellLink->SetShowCmd( SW_SHOW );				//標準の表示
	hRes = pShellLink->SetWorkingDirectory( CurrentFolder );	//カレントフォルダ
	hRes = pShellLink->SetIconLocation( NULL, 0 );			//これで、フツーのアイコンが表示される
	hRes = pShellLink->SetHotkey( 0 );						//ホットキーナシ
	hRes = pShellLink->SetDescription( Title );	//タイトル

	//　ユニコードに変換
	OLECHAR	ochLinkFile[_MAX_PATH];
	::MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, DstShorcutPath, -1,
                        ochLinkFile, _MAX_PATH );

	//　ショートカット書き込み
	hRes = pPersistFile->Save( ochLinkFile, TRUE );
	
	pPersistFile->Release();
	pShellLink->Release();

	::CoUninitialize();

	return TRUE;
}

