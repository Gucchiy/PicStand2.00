#if !defined(AFX_STATUSWND_H__66C8FE83_609E_4B70_8D20_BB696BB2BFCD__INCLUDED_)
#define AFX_STATUSWND_H__66C8FE83_609E_4B70_8D20_BB696BB2BFCD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatusWnd.h : ヘッダー ファイル
//

#include "Canvas.h"
#include "CanvasItem.h"
#include "IdeaTech.h"

/////////////////////////////////////////////////////////////////////////////
// CStatusWnd ウィンドウ
enum enumSWState {
	SWST_NUTORAL = 0,
	SWST_HIGHLIGHT
};

class CStatusWnd : public CWnd
{
// コンストラクション
public:
	CStatusWnd( UINT uCanvasBmpID, UINT uHighlightBmpID );

// アトリビュート
public:

protected:
	UINT			m_uCanvasBmpID;
	CCanvas*		m_pCanvas;
	
	UINT			m_uHighlightBmpID;
	CCanvasItem*	m_pHighlightItem;

	enumSWState		m_State;

	UINT			m_uMessage;
	WPARAM			m_wParam;
	LPARAM			m_lParam;

	CWnd*			m_pParentWnd;

	CFont*			m_pFont;

	CString			m_DispString;

// オペレーション
public:
	BOOL Create( CWnd* pParent, int nPosX, int nPosY, WPARAM wParam = NULL, LPARAM lParam = NULL );
	void SetDispString( const CString& DispString );

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CStatusWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CStatusWnd();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CStatusWnd)
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

#endif // !defined(AFX_STATUSWND_H__66C8FE83_609E_4B70_8D20_BB696BB2BFCD__INCLUDED_)
