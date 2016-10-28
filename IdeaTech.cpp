#include "stdafx.h"
#include "IdeaTech.h"

// ���W���[���t�@�C�����̎擾
CString ITech_GetModuleFileName()
{
	CString	ModuleFileString;
	::GetModuleFileName( AfxGetApp()->m_hInstance, ModuleFileString.GetBuffer( _MAX_PATH ), _MAX_PATH );
	ModuleFileString.ReleaseBuffer();

	return ModuleFileString;
}

// ���W���[���̃J�����g�t�H���_���擾
CString ITech_GetCurrentDir()
{
	// �J�����g�t�H���_���擾
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

// �X�^�[�g�A�b�v�p�t�H���_���擾
CString ITech_GetStartupDir()
{
	CString StartupPath;
	SHGetSpecialFolderPath(NULL, StartupPath.GetBuffer( MAX_PATH + 1 ), CSIDL_STARTUP, FALSE);
	StartupPath.ReleaseBuffer();

	return ( StartupPath + _T( "\\" ) );
}

// �A�v���P�[�V�����f�[�^�p�t�H���_���擾
// �Ȃ���ΐ�������
CString ITech_GetAppDataDir()
{
	CString	AppDataPath;
	SHGetSpecialFolderPath(NULL, AppDataPath.GetBuffer( MAX_PATH + 1 ), CSIDL_APPDATA, TRUE);
	AppDataPath.ReleaseBuffer();

	AppDataPath += ( CString(_T( "\\" )) + CString( ITECH_APPDATA_FOLDER ) );

	ITech_MakeAndGetDir( AppDataPath );

	return AppDataPath;
}

// �t�@�C�������邩�ǂ����̊m�F
BOOL ITech_IsTheFileExist( CString FileName )
{
	CFileStatus	FileStatus;
	return CFile::GetStatus( FileName, FileStatus );
}

// �w��p�X���m�F���āA�Ȃ���΃t�H���_�𐶐����A
// �Ō�� "\\" ������ retun ����B
// �w��t�H���_������:FALSE
// �w��t�H���_���Ȃ������̂Ńt�H���_�𐶐��FTRUE
BOOL ITech_MakeAndGetDir( CString& PathName )
{
	BOOL	bReturn = FALSE;

	if( !ITech_IsTheFileExist( PathName ) ){

		// �Ȃ��ꍇ�̓e���v���[�g���R�s�[
		CreateDirectory( PathName, NULL );
		bReturn = TRUE;

	}
	PathName += _T( "\\" );

	return bReturn;
}

// �t�H���_�P�ʂŃR�s�[����
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

// �t�H���_���ɂ���S�Ẵt�@�C�����폜�B�t�H���_���폜�B
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

// AppData �t�H���_��V�K�ɍ쐬�����ۂɁATempFile �ɕۑ�
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

// Uninstalle ���ɁATempFile �̓��e����AAppData ��̃t�@�C�����폜
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

// "IdeaTechMessage" Message ID �̎擾
UINT ITech_GetIdeaTechMessage()
{
	return ::RegisterWindowMessage( ITECH_MES_STRING );
}

// �V���[�g�J�b�g�t�@�C���̍쐬
BOOL ITech_CreateShorcut( const CString& DstShorcutPath,
	const CString& ModuleFileName, const CString& CurrentFolder, const CString& Title )
{
	IPersistFile*	pPersistFile = NULL;
	IShellLink*		pShellLink = NULL;
	HRESULT			hRes;	//�e����

	//�@�n�k�d���g�����߂̏�����
	hRes = ::CoInitialize( NULL );

	if( hRes == E_OUTOFMEMORY )
		return FALSE;
	if( hRes == E_INVALIDARG )
		return FALSE;
	if( hRes == E_UNEXPECTED )
		return FALSE;

	//�@��̃C���^�[�t�F�C�X���쐬
	hRes = ::CoCreateInstance( CLSID_ShellLink, NULL,
				CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *)&pShellLink );

	if( hRes == CLASS_E_NOAGGREGATION )
		return FALSE;

	if( hRes == REGDB_E_CLASSNOTREG )
		return FALSE;

	
	//�@IPersistFile�ւ̃|�C���^���擾
	hRes = pShellLink->QueryInterface( IID_IPersistFile, (LPVOID *)&pPersistFile );

	if( hRes != S_OK ){
		::CoUninitialize();
		return FALSE;
	}

	hRes = pShellLink->SetPath( ModuleFileName );			//�����N��p�X
	hRes = pShellLink->SetShowCmd( SW_SHOW );				//�W���̕\��
	hRes = pShellLink->SetWorkingDirectory( CurrentFolder );	//�J�����g�t�H���_
	hRes = pShellLink->SetIconLocation( NULL, 0 );			//����ŁA�t�c�[�̃A�C�R�����\�������
	hRes = pShellLink->SetHotkey( 0 );						//�z�b�g�L�[�i�V
	hRes = pShellLink->SetDescription( Title );	//�^�C�g��

	//�@���j�R�[�h�ɕϊ�
	OLECHAR	ochLinkFile[_MAX_PATH];
	::MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, DstShorcutPath, -1,
                        ochLinkFile, _MAX_PATH );

	//�@�V���[�g�J�b�g��������
	hRes = pPersistFile->Save( ochLinkFile, TRUE );
	
	pPersistFile->Release();
	pShellLink->Release();

	::CoUninitialize();

	return TRUE;
}

