// VersionInfoDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "picstand.h"
#include "VersionInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVersionInfoDlg ダイアログ


CVersionInfoDlg::CVersionInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVersionInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVersionInfoDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CVersionInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVersionInfoDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVersionInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CVersionInfoDlg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVersionInfoDlg メッセージ ハンドラ
