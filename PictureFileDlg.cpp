// PictureFileDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "picstand.h"
#include "PictureFileDlg.h"
#include "Global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictureFileDlg

IMPLEMENT_DYNAMIC(CPictureFileDlg, CFileDialog)

CPictureFileDlg::CPictureFileDlg(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
}

CPictureFileDlg::CPictureFileDlg( LPCTSTR lpszFileName, CWnd* pParentWnd ):
		CFileDialog( TRUE, NULL, lpszFileName, OFN_LONGNAMES | OFN_EXPLORER | OFN_ENABLESIZING | OFN_HIDEREADONLY,
			"JPEG/BMP Files (*.jpg;*.bmp)|*.jpg;*.bmp|All Files|*.*||", pParentWnd )
{

}

BEGIN_MESSAGE_MAP(CPictureFileDlg, CFileDialog)
	//{{AFX_MSG_MAP(CPictureFileDlg)
		// メモ -  ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

