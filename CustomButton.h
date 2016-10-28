#if !defined(AFX_CUSTOMBUTTON_H__377C5073_2C4B_4109_8ACB_9B0EC382B76D__INCLUDED_)
#define AFX_CUSTOMBUTTON_H__377C5073_2C4B_4109_8ACB_9B0EC382B76D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomButton.h : ヘッダー ファイル
//
#include "Canvas.h"
#include "CanvasItem.h"
#include "IdeaTech.h"

/////////////////////////////////////////////////////////////////////////////
// CCustomButton ウィンドウ
//
// -----------------------------------------------------------------------
// ビットマップボタンを自前で行うクラス。
// 通常状態、ハイライト状態、プッシュ状態３つの Bitmap を用意し、
// コンストラクタに渡してインスタンスを生成する。
// その後、Create メンバ関数を呼び出せば生成される。
// 押下のイベントは、Create の引数として渡される値が、IdeaTechMessage として、
// 親 Window にポストされる。

enum enumState{
	CBST_NUTORAL = 0,
	CBST_HIGHLIGHT,
	CBST_PUSH
};

class CCustomButton : public CWnd
{
// コンストラクション
public:
	// -----------------------------------------------------------------------
	// コンストラクタ
	// -----------------------------------------------------------------------
	// uCanvasBmpID		通常状態 Bitmap のリソース ID
	// uHighlightBmpID	ハイライト状態 Bitmap のリソース ID
	// uPushBmpID		プッシュ状態 Bitmap のリソース ID
	// -----------------------------------------------------------------------
	CCustomButton( UINT uCanvasBmpID, UINT uHighlightBmpID, UINT uPushBmpID );

// アトリビュート
public:

protected:
	UINT			m_uCanvasBmpID;
	CCanvas*		m_pCanvas;
	
	UINT			m_uHighlightBmpID;
	CCanvasItem*	m_pHighlightItem;

	UINT			m_uPushBmpID;
	CCanvasItem*	m_pPushItem;

	enumState		m_State;

	UINT			m_uMessage;
	WPARAM			m_wParam;
	LPARAM			m_lParam;

	CWnd*			m_pParentWnd;

// オペレーション
public:
	// -----------------------------------------------------------------------
	// 生成
	// -----------------------------------------------------------------------
	// pParent	親 Window （通知 Window）
	// nPosX	初期表示位置 X
	// nPosY	初期表示位置 Y
	// wParam	押下時の通知における wParam
	// lParam	押下時の通知における lParam
	BOOL Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam = NULL, LPARAM lParam = NULL );

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CCustomButton)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CCustomButton();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CCustomButton)
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

#endif // !defined(AFX_CUSTOMBUTTON_H__377C5073_2C4B_4109_8ACB_9B0EC382B76D__INCLUDED_)
