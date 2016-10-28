#include "stdafx.h"
#include "Global.h"
#include "IdeaTech.h"

CString	g_CurrentDirString;
CString	g_StartupShortcutPath;
CString	g_ApplicationDataPath;
CString	g_PictureFolderPath;

int	CX_FRAME = 32;

BOOL Global_Initialize()
{
	// �J�����g�t�H���_���擾
	g_CurrentDirString = ITech_GetCurrentDir();

	// �X�^�[�g�A�b�v�V���[�g�J�b�g�p�X�����擾
	g_StartupShortcutPath = ITech_GetStartupDir() + STARTUP_SHORTCUT;

	// �A�v���P�[�V�����f�[�^�p�X�����擾
	g_ApplicationDataPath = ITech_GetAppDataDir();

	g_ApplicationDataPath = g_ApplicationDataPath + PICSTAND_APPDATA_FOLDER;
	
	// �ʐ^���ėp�t�H���_���m�F
	ITech_MakeAndGetDir( g_ApplicationDataPath );

	// Picture �t�H���_���擾
	g_PictureFolderPath = g_ApplicationDataPath + PICTURE_FOLDER;
	if( ITech_MakeAndGetDir( g_PictureFolderPath ) ){

		ITech_CopyFiles( g_CurrentDirString + PICTURE_FOLDER, g_PictureFolderPath );
		ITech_AddAppPathToTempFile( g_ApplicationDataPath );

	}

	return TRUE;
}

void Global_Finalize()
{
}

CString Global_GetCurrentDir()
{
	return g_CurrentDirString;
}

CString Global_GetStartupShorcutPath()
{
	return g_StartupShortcutPath;
}

CString Global_GetAppDataDir()
{
	return g_ApplicationDataPath;
}

CString Global_GetPictureDataDir()
{
	return g_PictureFolderPath;
}
