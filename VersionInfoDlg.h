#if !defined(AFX_VERSIONINFODLG_H__D0D5016A_0B27_4CD5_A5EE_53D964595530__INCLUDED_)
#define AFX_VERSIONINFODLG_H__D0D5016A_0B27_4CD5_A5EE_53D964595530__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VersionInfoDlg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CVersionInfoDlg ダイアログ

class CVersionInfoDlg : public CDialog
{
// コンストラクション
public:
	CVersionInfoDlg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CVersionInfoDlg)
	enum { IDD = IDD_VERSION_INFO };
		// メモ: ClassWizard はこの位置にデータ メンバを追加します。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CVersionInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CVersionInfoDlg)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VERSIONINFODLG_H__D0D5016A_0B27_4CD5_A5EE_53D964595530__INCLUDED_)
