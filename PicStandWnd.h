#if !defined(AFX_PICSTANDWND_H__97F10919_9B58_440A_973D_F1D60DC997FC__INCLUDED_)
#define AFX_PICSTANDWND_H__97F10919_9B58_440A_973D_F1D60DC997FC__INCLUDED_

#include "Picture.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PicStandWnd.h : ヘッダー ファイル
//
#include "CustomButton.h"
#include "StatusWnd.h"
#include "StayButton.h"
#include "TrayIcon.h"
#include "CustomizeWnd.h"

#include <afxtempl.h>

enum enumWndStyle {
	WNDSTYLE_NORMAL = 0,
	WNDSTYLE_BAR
};

enum enumZOrder {
	ZORDER_NORMAL = 0,
	ZORDER_TOPMOST,
	ZORDER_BOTTOMMOST
};

enum enumDragState {
	DRGST_NORMAL = 0,
	DRGST_DRAGGING,
	DRGST_SIZING
};	

/////////////////////////////////////////////////////////////////////////////
// CPicStandWnd ウィンドウ

class CPicStandWnd : public CWnd
{
// コンストラクション
public:
	CPicStandWnd();

// アトリビュート
public:

protected:
	// Picture 表示
	CPicture*		m_pPicture;

	// Style
	enumWndStyle	m_WndStyle;

	// Stay 状態
	BOOL			m_bStay;

	// Z Order
	enumZOrder		m_ZOrder;

	// 表示サイズ固定
	BOOL			m_bFixSize;

	// ドラッグ状態
	enumDragState	m_DragState;

	// Window 移動のための保存地
	CPoint			m_MoveStartMousePoint;
	CRect			m_MoveStartWndRect;
	
	// カーソル状態
	HCURSOR			m_hPrevCursor;

	// Button
	CCustomButton*	m_pPicMenuButton;

	// Status Window
	CStatusWnd*		m_pStatusWnd;

	// Stay Button
	CStayButton*	m_pStayButton;

	// Next Button
	CCustomButton*	m_pNextButton;
	CCustomButton*	m_pBackButton;

	// Menu
	CMenu*			m_pMenu;

	// Notyfy Icon
	CTrayIcon*		m_pTrayIcon;

	// Customize Window
	CCustomizeWnd*	m_pCustomizeWnd;

	// Cash File List
	CTypedPtrArray< CPtrArray, CString* >
							m_CashFilePathArray;

	// Colors
	UINT			m_ColorR;
	UINT			m_ColorG;
	UINT			m_ColorB;
	COLORREF		m_Color;
	COLORREF		m_DarkColor;
	COLORREF		m_LightColor;
	COLORREF		m_Light2Color;

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CPicStandWnd)
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

	LRESULT OnIdeaTechMessage( WPARAM wParam, LPARAM lParam );
	LRESULT OnCustomizeWndMessage( WPARAM wParam, LPARAM lParam );

// インプリメンテーション
public:
	BOOL Create();
	virtual ~CPicStandWnd();
	void CustomizeWndDestroyInd(){ m_pCustomizeWnd = NULL; };

	void GetColor( UINT& nRed, UINT& nGreen, UINT& nBlue ){ nRed = m_ColorR; nGreen = m_ColorG; nBlue = m_ColorB; }
	void SetColor( UINT nRed, UINT nGreen, UINT nBlue ){
		m_ColorR = nRed;
		m_ColorG = nGreen;
		m_ColorB = nBlue;
		SetColors();
	}
	void AdjustWindowSizePos();

protected:
	void SetPosition( int nPosX, int nPosY );
	void InitWindowParams();
	void AdjustWindowFromWnd();
	void ActivateMenu( int nX, int nY );
	BOOL StartupShorcutExist();
	void CreateStartupShortcut();
	void SetZOrder( enumZOrder ZOrder );
	BOOL GetPossibleWide();
	void SetNormalStyle();
	void SetBarStyle();
	void SetPictureWide( BOOL bCXFix = FALSE );
	void DeletePicture();
	void CreateCashList();
	void SetColors();
	void CheckCurrentPicture();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPicStandWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMenuClose();
	afx_msg void OnDiv2();
	afx_msg void OnMul1();
	afx_msg void OnMul2();
	afx_msg void OnTopmost();
	afx_msg void OnBottommost();
	afx_msg void OnStay();
	afx_msg void OnBarstyle();
	afx_msg void OnHelp();
	afx_msg void OnSupport();
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg void OnRegStartup();
	afx_msg void OnVersiondlg();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFixsize();
	afx_msg void OnFixsize2();
	afx_msg void OnCashDelete();
	afx_msg void OnCashNext();
	afx_msg void OnCashPrev();
	afx_msg void OnCustomizewnd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PICSTANDWND_H__97F10919_9B58_440A_973D_F1D60DC997FC__INCLUDED_)
