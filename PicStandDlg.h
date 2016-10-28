// PicStandDlg.h : ヘッダー ファイル
//

#if !defined(AFX_PICSTANDDLG_H__948FABC4_5039_45B6_B08C_66C86A8AC391__INCLUDED_)
#define AFX_PICSTANDDLG_H__948FABC4_5039_45B6_B08C_66C86A8AC391__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPicStandDlg ダイアログ

class CPicStandDlg : public CDialog
{
// 構築
public:
	CPicStandDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CPicStandDlg)
	enum { IDD = IDD_PICSTAND_DIALOG };
		// メモ: この位置に ClassWizard によってデータ メンバが追加されます。
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPicStandDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CPicStandDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PICSTANDDLG_H__948FABC4_5039_45B6_B08C_66C86A8AC391__INCLUDED_)
