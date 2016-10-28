#if !defined(AFX_CUSTOMIZEWND_H__EF667974_C2E1_41B6_BD2B_363B13004BDA__INCLUDED_)
#define AFX_CUSTOMIZEWND_H__EF667974_C2E1_41B6_BD2B_363B13004BDA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomizeWnd.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCustomizeWnd ダイアログ

class CCustomizeWnd : public CDialog
{
// データ
	UINT	m_uRedTemp;
	UINT	m_uGreenTemp;
	UINT	m_uBlueTemp;
	UINT	m_uWidthTemp;

// コンストラクション
public:
	CCustomizeWnd(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CCustomizeWnd)
	enum { IDD = IDD_CUSTOMIZE_WND };
	CScrollBar	m_WidthScrollBar;
	CScrollBar	m_BlueScrollBar;
	CScrollBar	m_GreenScrollBar;
	CScrollBar	m_RedScrollBar;
	UINT	m_uBlueValue;
	UINT	m_uGreenValue;
	UINT	m_uRedValue;
	UINT	m_uWidthValue;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCustomizeWnd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCustomizeWnd)
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnDefault();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CUSTOMIZEWND_H__EF667974_C2E1_41B6_BD2B_363B13004BDA__INCLUDED_)
