#if !defined(AFX_PICTUREFILEDLG_H__34140F08_9EF5_4AC5_AFC1_BAABEEEDDBF3__INCLUDED_)
#define AFX_PICTUREFILEDLG_H__34140F08_9EF5_4AC5_AFC1_BAABEEEDDBF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PictureFileDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CPictureFileDlg ダイアログ

class CPictureFileDlg : public CFileDialog
{
	DECLARE_DYNAMIC(CPictureFileDlg)

public:
	CPictureFileDlg(BOOL bOpenFileDialog, // TRUE ならば FileOpen、 FALSE ならば FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);

	CPictureFileDlg( LPCTSTR lpszFileName, CWnd* pParentWnd );

protected:

protected:
	//{{AFX_MSG(CPictureFileDlg)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PICTUREFILEDLG_H__34140F08_9EF5_4AC5_AFC1_BAABEEEDDBF3__INCLUDED_)
