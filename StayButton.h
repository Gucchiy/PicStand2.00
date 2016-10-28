#if !defined(AFX_STAYBUTTON_H__C062C18C_8923_404F_AF14_75510479DA3F__INCLUDED_)
#define AFX_STAYBUTTON_H__C062C18C_8923_404F_AF14_75510479DA3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StayButton.h : ヘッダー ファイル
//
#include "CanvasItem.h"
#include "IdeaTech.h"

/////////////////////////////////////////////////////////////////////////////
// CStayButton ウィンドウ

class CStayButton : public CWnd
{
// コンストラクション
public:
	CStayButton( UINT uDownBmpID, UINT uDownHighlightBmpID,
		UINT uUpBmpID, UINT uUpHighlightBmpID );

// アトリビュート
public:

protected:
	UINT			m_uDownBmpID;
	CCanvasItem*	m_pDownItem;

	UINT			m_uDownHighlightBmpID;
	CCanvasItem*	m_pDownHighlightItem;

	UINT			m_uUpBmpID;
	CCanvasItem*	m_pUpItem;

	UINT			m_uUpHighlightBmpID;
	CCanvasItem*	m_pUpHighlightItem;

	BOOL			m_bIsNowUp;
	BOOL			m_bIsNowHighlight;

	UINT			m_uMessage;
	WPARAM			m_wParam;
	LPARAM			m_lParam;

	CWnd*			m_pParentWnd;

// オペレーション
public:
	BOOL Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam = NULL, LPARAM lParam = NULL );
	BOOL IsNowUp(){ return m_bIsNowUp; }
	void SetUpState( BOOL bUp = TRUE ){ m_bIsNowUp = bUp; }
	BOOL GetUpState(){ return m_bIsNowUp; }

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CStayButton)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CStayButton();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CStayButton)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STAYBUTTON_H__C062C18C_8923_404F_AF14_75510479DA3F__INCLUDED_)
