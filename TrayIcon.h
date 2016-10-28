// TrayIcon.h: CTrayIcon クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAYICON_H__C23E4397_151C_48D8_83E9_AFCB5304AC6D__INCLUDED_)
#define AFX_TRAYICON_H__C23E4397_151C_48D8_83E9_AFCB5304AC6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTrayIcon
//
// -----------------------------------------------------------------------
// タスクトレイ上に Icon を表示し、Idea Tech メッセージを貰うようにする

class CTrayIcon  
{
protected:
	// Notyfy Icon Data 列
	NOTIFYICONDATA	m_NotifyIconData;

public:
	// -----------------------------------------------------------------------
	// コンストラクタ
	// -----------------------------------------------------------------------
	// hWnd			IdeaTech Message を貰う Window
	// uIconID		タスクトレイに表示する Icon へのリソース ID
	// TipString	Tip 用文字列（マウスを持っていくと表示される）
	// wParam		イベント発生時に投げられる wParam メッセージパラメータの値
	// -----------------------------------------------------------------------
	CTrayIcon( HWND hWnd, UINT uIconID, CString TipString, WPARAM wParam );
	virtual ~CTrayIcon();

	virtual void OnMessage( LPARAM lParam);

};

#endif // !defined(AFX_TRAYICON_H__C23E4397_151C_48D8_83E9_AFCB5304AC6D__INCLUDED_)
